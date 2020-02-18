import serial
import time
import struct
import warnings
import serial
import serial.tools.list_ports

#team written modules
import LineAlg as lineAlg
import resizeImage as resizeImage

currX = 0
currY = 0

test = False

if (not test):
	
	arduino_ports = [ # automate finding port name so we dont have to change it manually between users
	    p.device
	    for p in serial.tools.list_ports.comports()
	    if 'Arduino' in p.description  # may need tweaking to match new arduinos
	]
	
	if not arduino_ports:
	    raise IOError("No Arduino found")

	serialData = serial.Serial(arduino_ports[0], baudrate=9600)
	
time.sleep(2) # wait for intialize

def drawLine(nextX, nextY):
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
		print(chrPass)
		if (not test):
			serialData.write(str(chrPass).encode())
		time.sleep(0.09)
		print(chrPass)
		#serialData.write(str.encode(chrInterp))
		#serialData.write(struct.pack(">ii",instruct,1));

def testLine(x, y):
	if currY == 0 and currX == 0:
		print("---" , str(currX) + "," + str(currY))

	drawLine(x,y)
	print("---" , str(currX) + "," + str(currY))
