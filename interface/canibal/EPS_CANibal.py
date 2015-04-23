from canibal import CANibal

class EPS_CANibal(CANibal):

	data = [0, 0, 0, 0, 0, 0, 0, 0]

	def __init__(self):
		pass

	def set_angle(self, word):
		self.data[1] = (word & 0xFF00) >> 8
		self.data[0] = word & 0x00FF

	def set_rpm(self, word):
		self.data[3] = (word & 0xFF00) >> 8
		self.data[2] = word & 0x00FF

	def set_pump_dc(self, word):
		self.data[5] = (word & 0xFF00) >> 8
		self.data[4] = word & 0x00FF

	def set_digital_input(self, word):
		self.data[7] = (word & 0xFF00) >> 8
		self.data[6] = word & 0x00FF
