#!/usr/bin/python
from __future__ import print_function
from gevent import socket
import threading
import random

class CANClient:

	client = ""
	def __init__(self, ip, port):
		self.client = socket.create_connection((ip, port))

	def send(self, type, data):
		self.client.send(type + "=" + str(data))


if __name__ == "__main__":
	client = CANClient('127.0.0.1', 1234)
	client.send("SPEED", random.randint(-5000, 5000))