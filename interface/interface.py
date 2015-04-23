#!/usr/bin/python
from __future__ import print_function
from gevent import socket

from multiprocessing import Process, Queue
from threading import Thread

from Tkinter import *
from ttk import Frame, Button, Style
from PIL import Image, ImageTk
from truck import Truck

queue = Queue() # internal queue
can_queue = Queue() # messages from can (server to client)


class CANClient(Process):

    def __init__(self, ip, port):
        Process.__init__(self)
        self.ip = ip
        self.port = port

    def send(self, type, data):
        try:
            self.client.send(type + "=" + str(data) + "\n")
        except:
            # We seem to have lost connection - let us try to reconnect
            print ("Connection lost. Reconnecting...")
            self.client = socket.create_connection((self.ip, self.port))

    def run(self):
        try:
            self.client = socket.create_connection((self.ip, self.port))
        except:
            print("Could not connect. Is the server alive?")
        while True:
            try:
                item = queue.get_nowait()
            except:
                item = ""

            if item and '=' in item:
                args = item.split('=')
                if len(args) == 2:
                    try:
                        self.send(args[0], args[1])
                    except:
                        print("Could not send. Is the server alive?")

            # Receive from socket (server)
            try:
                item = self.client.recv(43, 0x40)
                if item:
                    item = item.split('\n')[0].split() # Remove newline and split by whitespace
                    # 0 => can0, 1 => 666, 2 => [X] (X = 1-8), 3..(3 + X) => data bytes
                    if item[1] == "666": # DEBUG CHANNEL
                        can_length = int(item[2].replace("[", "").replace("]", ""))
                        if can_length == 8: # We expect nothing else
                            # Parse indicator data from first byte
                            if int(item[3]) & 0x01:
                                can_queue.put("INDICATOR_LEFT=1")
                                can_queue.put("INDICATOR_RIGHT=0")
                                # Turn left indicator on
                                # Turn right indicator off
                            elif int(item[3]) & 0x02:
                                can_queue.put("INDICATOR_LEFT=0")
                                can_queue.put("INDICATOR_RIGHT=1")
                                # Turn right indicator on
                                # Turn left indicator off
                            else:
                                can_queue.put("INDICATOR_LEFT=0")
                                can_queue.put("INDICATOR_RIGHT=0")
                    elif item[1] == "21B": # Data from MCU / ICH
                        override   = (int(item[8], 16) & 0x04) >> 2
                        diliftup   = (int(item[7], 16) & 0x02) >> 1
                        diliftdown = (int(item[7], 16) & 0x01)
                        can_queue.put("OVERRIDE="    + str(override)) # Override
                        can_queue.put("DILIFT1UP="   + str(diliftup)) # 2 upp 
                        can_queue.put("DILIFT1DOWN=" + str(diliftdown)) # 3 ner
                        
                        bflyramped = ((int(item[3], 16) & 0x7F) << 8) + int(item[4], 16)
                        if ((int(item[3], 16) & 0x80) >> 7) == 1:
                            bflyramped = bflyramped - 32508
                        can_queue.put("BFLY=" + str(bflyramped))
                    elif item[1] == "19B": # Data from OCU
                        restrict_drive = (int(item[3], 16) & 0x02) >> 1
                        restrict_hydr  = (int(item[3], 16) & 0x08) >> 3
                        restrict_steer = (int(item[3], 16) & 0x20) >> 5
                        can_queue.put("RESTRICT_DRIVE=" + str(restrict_drive))
                        can_queue.put("RESTRICT_HYDR="  + str(restrict_hydr))
                        can_queue.put("RESTRICT_STEER=" + str(restrict_steer))

                        restrict_drive_speed = (int(item[4], 16) & 0x7F)
                        if ((int(item[4], 16) & 0x80) >> 7) == 1:
                            restrict_drive_speed = restrict_drive_speed - 128
                        can_queue.put("RESTRICT_DRIVE_SPEED=" + str(restrict_drive_speed))

            except:
                pass

def main():
    client = CANClient('127.0.0.1', 1234)
    client.daemon = True
    client.start()

    root = Tk()
    root.geometry("800x400+300+300")
    app = Truck.Truck(root, queue, can_queue)
    app.mainloop()

if __name__ == '__main__':
    main()