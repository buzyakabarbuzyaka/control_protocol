import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.5)
ser.write(b'R')
ser.write(b'R')
ser.write(b'R')
ser.write(b'R')
time.sleep(0.1)
ser.close()
