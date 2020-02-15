import serial
import time

aData = serial.Serial('/dev/tty.usbmodem1421', baudrate=9600)

#aData = serial.Serial('/dev/tty.usbmodem14101', baudrate=9600)


def ledOn():
    aData.write(str.encode('1'))

def ledOff():
    aData.write(str.encode('0'))


i = 0

while(i < 100):
    print(i)

    if(i % 2 == 0):
        ledOn()
    else:
        ledOff()
    time.sleep(1)
    i += 1
