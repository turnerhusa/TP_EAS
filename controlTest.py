import serial
import time

aData = serial.Serial('/dev/tty.usbmodem14201', baudrate=9600)

def ledOn():
    aData.write(str.encode('1'))

def ledOff():
    aData.write(str.encode('0'))


print("Remote Serial Connection Control:")
print("Press 1 to turn on LED")
print("Press 0 to turn off LED")


while True:

    if(input('Command:') == 1):
        ledOn()
    elif(input('Command:') == 0):
        ledOff()
