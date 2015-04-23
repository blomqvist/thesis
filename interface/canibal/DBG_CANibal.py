from canibal import CANibal

class DBG_CANibal(CANibal):
	''' 
	DEBUG CAN message class to issue fork lift commands
	to OCU
	'''


	data = [0, 0, 0, 0, 0, 0, 0, 0]

	def __init__(self):
		pass

	def set_weight(self, word):
		self.data[0] = (word & 0xFF00) >> 8
		self.data[1] = word & 0x00FF

	def set_height(self, byte):
		if byte > 200:
			self.data[2] = 0x02
		elif byte > 100:
			self.data[2] = 0x01
		else:
			self.data[2] = 0x00


