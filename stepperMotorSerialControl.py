import serial
import time
import struct

#team written module
import LineAlg as lineAlg
import resizeImage as resizeImage

currX = 0
currY = 0

# resizeImage.resize("test.jpeg")

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
		serialData.write(str(chrPass).encode())
		time.sleep(0.09)
		print(chrPass)
		#serialData.write(str.encode(chrInterp))
		#serialData.write(struct.pack(">ii",instruct,1));



serialData = serial.Serial('COM7', baudrate=9600)
time.sleep(2) # wait for intialize


def testLine(x, y):
	if currY == 0 and currX == 0:
		print("---" , str(currX) + "," + str(currY))

	drawLine(x,y)
	print("---" , str(currX) + "," + str(currY))



testLine(500,1000)
print("done")
# testLine(50,50)
# testLine(0,50)
# testLine(0,0)