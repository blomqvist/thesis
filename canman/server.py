#!/usr/bin/python
from __future__ import print_function
from gevent import socket
from gevent.server import StreamServer

from canibal import ACT_CANibal, CANibal

from threading import Thread
import time

# Global
act_can = ACT_CANibal.ACT_CANibal()

class ACT_worker(Thread):

	def __init__(self):
		Thread.__init__(self)

	def run(self):
		while True:
			act_can.send_packet(CANibal.CANibal.ACT_PDO_MISO2)
			time.sleep(0.02)

def handle(sock, address):
	fp = sock.makefile()
	while True:
		line = fp.readline()
		if line and "=" in line:
			params = line.split('=')
			print(params[0] + " => " + params[1])
			distribute_command(params)
		else:
			break

def distribute_command(params):
	params[1] = int(params[1])
	if params[0] == "SPEED":
		act_can.set_rpm(params[1])


if __name__ == '__main__':
	# Assign workers
	act_w  = ACT_worker()
	server = StreamServer(('0.0.0.0', 1234), handle)

	# Start workers
	act_w.start()
	server.serve_forever()
	
	# Wait for threads last
	w.join()
	
