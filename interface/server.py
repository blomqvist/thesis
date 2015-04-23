#!/usr/bin/python
from __future__ import print_function

import sys
import select

from gevent import socket
from gevent.server import StreamServer

from canibal import ACT_CANibal, EPS_CANibal, MCU_CANibal, DBG_CANibal, CANibal

from threading import Thread

import Queue
import time


# Global
act_can = ACT_CANibal.ACT_CANibal()
eps_can = EPS_CANibal.EPS_CANibal()
mcu_can = MCU_CANibal.MCU_CANibal()
dbg_can = DBG_CANibal.DBG_CANibal()

line_queue = Queue.Queue()

class ACT_worker(Thread):

    def __init__(self):
        Thread.__init__(self)

    def run(self):
        while True:
            act_can.send_packet(CANibal.CANibal.ACT_PDO_MISO2)
            time.sleep(0.02)

class MCU_worker(Thread):

    def __init__(self):
        Thread.__init__(self)

    def run(self):
        while True:
            mcu_can.send_packet(CANibal.CANibal.OCU_PDOrx1) # We send to OCU
            time.sleep(0.02)

class EPS_worker(Thread):

    def __init__(self):
        Thread.__init__(self)

    def run(self):
        while True:
            eps_can.send_packet(CANibal.CANibal.EPS_PDO_MOSI1)
            time.sleep(0.02)

class DBG_worker(Thread):

    def __init__(self):
        Thread.__init__(self)

    def run(self):
        while True:
            dbg_can.send_packet(CANibal.CANibal.DBG_PDO_1)
            time.sleep(0.02)

class CAN_sniffer(Thread):

    def __init__(self):
        Thread.__init__(self)

    def run(self):
        while True:
            # non blocking read from stdin
            while sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
                line = sys.stdin.readline()
                if line:
                    line = line.split('\n')[0]
                    line_queue.put(line)
                else:
                    while True:
                        print ("stdin stopped")
                        time.sleep(1)

class TinyServer:
    sock = None

    def handle(self, sock, address):
        self.sock = sock
        fp = sock.makefile()
        while True:
            # Recieve message from interface
            line = fp.readline()
            if line and "=" in line:
                line = line.split('\n')[0]
                params = line.split('=')
                print(params[0] + " => " + params[1])
                distribute_command(params)
            else:
                pass

    def send_to_client(self):
        while self.sock is None:
            time.sleep(0.5)
        while True:
            try:
                line = line_queue.get()
                self.deal_with_can_response(response = line)
                self.sock.sendall(line + '\n')
            except:
                while self.sock is None:
                    time.sleep(0.5)

    def deal_with_can_response(self, response):
        pass

def distribute_command(params):
    try:
        params[1] = int(params[1])
    except:
        return

    try:
        if params[0] == "SPEED":
            act_can.set_rpm(params[1])
        elif params[0] == "STEER_ANGLE":
            eps_can.set_angle(params[1])
        elif params[0] == "ADLIFT1":
            mcu_can.set_adlift1_byte(params[1])
        elif params[0] == "DILIFT2":
            mcu_can.set_dilift_2_bit(params[1])
        elif params[0] == "DILIFT1":
            mcu_can.set_dilift_1_bit(params[1])
        elif params[0] == "HORN":
            mcu_can.toggle_horn_bit()
        elif params[0] == "BELLY":
            mcu_can.toggle_belly_bit()
        elif params[0] == "LEFTINDICATOR":
            mcu_can.set_left_indicator_bit()
        elif params[0] == "RIGHTINDICATOR":
            mcu_can.set_right_indicator_bit()
        elif params[0] == "FORK_HEIGHT":
            dbg_can.set_height(params[1])
        elif params[0] == "FORK_WEIGHT":
            dbg_can.set_weight(params[1])
    except:
        print ("Trying to call non existing function")

if __name__ == '__main__':
    tiny_server = TinyServer()
    tiny_sender = Thread(target = tiny_server.send_to_client)

    # Assign workers
    can_w  = CAN_sniffer()
    act_w  = ACT_worker()
    #mcu_w  = MCU_worker()
    eps_w  = EPS_worker()
    dbg_w = DBG_worker()
    server = StreamServer(('0.0.0.0', 1234), tiny_server.handle)

    can_w.daemon = True
    act_w.daemon = True
    #mcu_w.daemon = True
    eps_w.daemon = True
    dbg_w.daemon = True
    tiny_sender.daemon = True

    # Start workers
    can_w.start()
    act_w.start()
    #mcu_w.start()
    eps_w.start()
    dbg_w.start()

    tiny_sender.start()
    server.serve_forever()
     
