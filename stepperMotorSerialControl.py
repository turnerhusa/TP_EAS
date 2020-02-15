import serial
import time
import struct

serialData = serial.Serial('/dev/tty.usbmodem1421', baudrate=9600)
time.sleep(2) # wait for intialize

serialData.write(struct.pack(">BB",0, 100));
time.sleep(2);

serialData.write(struct.pack(">BB",1,255));
time.sleep(2);

serialData.write(struct.pack(">BB",0, 100));
time.sleep(2);

serialData.write(struct.pack(">BB",1,255));
time.sleep(2);

serialData.write(struct.pack(">BB",0, 100));
time.sleep(2);

serialData.write(struct.pack(">BB",1,255));
time.sleep(2);