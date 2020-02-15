import serial
import time
import numpy

aData = serial.Serial('/dev/tty.usbmodem14201', baudrate=9600)

#aData = serial.Serial('/dev/tty.usbmodem14101', baudrate=9600)


def sendCoords(int x, y):
    aData.write(numpy.uint8(x))
    aData.write(numpy.uint8(y))




# start at 0,0
sendCoords(50, 0)
sendCoords(50, 50)
sendCoords(0, 50)
sendCoords(0, 0)

