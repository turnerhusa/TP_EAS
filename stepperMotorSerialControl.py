import serial
import time
import struct

#team written module
import LineAlg as lineAlg

currX = 0
currY = 0

def drawLine( nextX, nextY):
	global currX
	global currY
	instructions = lineAlg.drawLine(currX, currY, nextX, nextY)
	currX = nextX
	currY = nextY
	for instruct in instructions:

		#str_pass = b''
		#str_pass += struct.pack('!B',instruct)
		chrPass = ''
		if (instruct == 0):
			chrPass = '0'
		if (instruct == 1):
			chrPass = '1'
		if (instruct == 2):
			chrPass = '2'
		if (instruct == 3):
			chrPass = '3'
		serialData.write(str(chrPass).encode())
		time.sleep(.05)
		print(chrPass)
		#serialData.write(str.encode(chrInterp))
		#serialData.write(struct.pack(">ii",instruct,1));



serialData = serial.Serial('/dev/tty.usbmodem1421', baudrate=9600)
time.sleep(2) # wait for intialize


drawLine(	50,	0);
drawLine(	0,	0);


