import subprocess
import os

class CANibal:

	count = 0
	FNULL = open(os.devnull, 'w')

	''' ICH DEFINES '''
	ICH_NODE_ID = 0x17
	ICH_PDO_MISO1 = (0x200 + ICH_NODE_ID)

	''' ACT DEFINES '''
	ACT_NODE_ID = 0x0B
	ACT_PDO_MOSI1 = (0x200 + ACT_NODE_ID)
	ACT_PDO_MISO1 = (0x180 + ACT_NODE_ID)
	ACT_PDO_MISO2 = (0x280 + ACT_NODE_ID)
	ACT_PDO_MISO3 = (0x380 + ACT_NODE_ID)

	''' EPS DEFINES '''
	EPS_NODE_ID = 0x07
	EPS_PDO_MOSI1 = (0x200 + EPS_NODE_ID)

	''' OCU DEFINES '''
	OCU_NODE_ID = 0x1B
	OCU_PDOrx1  = (0x200 + OCU_NODE_ID) # Data from MCU: Bfly, AdLift, Buttons
	OCU_PDOtx1  = (0x180 + OCU_NODE_ID) # Data from OCU: Command, Speed, Steer, etc
	OCU_PDOtx2  = (0x280 + OCU_NODE_ID) # Data from OCU: Display text + LED

	''' DEBUG DEFINES '''
	DBG_PDO_1 = 0x665

	data = [0, 0, 0, 0, 0, 0, 0, 0]

	def send_packet(self, COBID):
		data = list(map(str, self.data)) # Convert int -> str
		subprocess.call(
			['./cdump', 
			 str(COBID), 
			 data[0], 
			 data[1], 
			 data[2], 
			 data[3], 
			 data[4], 
			 data[5], 
			 data[6], 
			 data[7]],
		stdout = self.FNULL)