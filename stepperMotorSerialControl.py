import serial
import time
import struct

#team written module
import LineAlg as lineAlg

def drawLine(nextX, nextY):
	instructions = lineAlg.drawLine(currX, currY, nextX, nextY)
	for instruct in instructions:
		serialData.write(struct.pack(">B",instruct));

currX = 0;
currY = 0;

serialData = serial.Serial('/dev/tty.usbmodem1421', baudrate=9600)
time.sleep(2) # wait for intialize


drawLine(	50,	0);
drawLine(	50,	50);
drawLine(	0,	50);
drawLine(	0,	0);


