#!/usr/bin/python
from __future__ import print_function

from canibal import ACT_CANibal
from canibal import CANibal

from threading import Thread
import time

# Global
act_can = ACT_CANibal()

class ACT_worker(Thread):

	def __init__(self):
		Thread.__init__(self)

	def run(self):
		while True:
			act_can.send_packet(CANibal.ACT_PDO_MISO2)
			time.sleep(0.02)

if __name__ == "__main__":
	w = ACT_worker()

	w.start()

	w.join()
