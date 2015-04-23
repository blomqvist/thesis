from canibal import CANibal

class MCU_CANibal(CANibal):

	data = [0, 0, 0, 0, 0, 0, 0, 0]

	oldDiLift2Up = False
	oldDiLift1Down = True

	oldDiLift2Up = False
	oldDiLift2Down = True

	def __init__(self):
		pass

	def set_bfly_word(self, word):
		self.data[0] = (word & 0xFF00) >> 8
		self.data[1] = word & 0x00FF

	def set_adlift1_byte(self, byte):
		self.data[2] = byte & 0xFF

	def set_adlift2_byte(self, byte):
		self.data[3] = word & 0xFF

	def set_dilift_1_bit(self, bit):
		if bit: # if bit == 1, lift is requested
			set_bit = 0
			if oldDiLift1Up:
				set_bit = 1
			oldDiLift1Up = not oldDiLift1Up

			self.data[4] = set_bit << 2
		else:
			set_bit = 0
			if not oldDiLift1Down:
				set_bit = 1
			oldDiLift1Down = not oldDiLift1Down

			self.data[4] = set_bit << 3

	def set_dilift_2_bit(self, bit):
		if bit: # if bit == 1, lift is requested
			set_bit = 0
			if oldDiLift2Up:
				set_bit = 1
			oldDiLift2Up = not oldDiLift2Up

			self.data[4] = set_bit << 0
		else:
			set_bit = 0
			if not oldDiLift2Down:
				set_bit = 1
			oldDiLift2Down = not oldDiLift2Down

			self.data[4] = set_bit << 1

	def toggle_horn_bit(self):
		self.data[3] ^= 1 << 4

	def toggle_belly_bit(self):
		self.data[3] ^= 1 << 5

	def set_left_indicator_bit(self):
		self.data[5] ^= 1 << 0

	def set_right_indicator_bit(self):
		self.data[5] ^= 1 << 1

	def clear_left_indicator_bit(self):
		self.data[5] = 0 << 0

	def clear_right_indicator_bit(self):
		self.data[5] = 0 << 1

	def left_indicator_on(self):
		return self.data[5] & 0x01

	def right_indicator_on(self):
		return self.data[5] & 0x02
