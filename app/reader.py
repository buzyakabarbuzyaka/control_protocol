import serial
import time

path = '/dev/ttyUSB0'

print("---READER ONLINE---")
print(f"\tlistening on:{path}")
print("------")

with serial.Serial(path, 115200, timeout=0.5) as ser:
    while True:
        if ser.in_waiting:
            print(ser.readline().decode("utf-8"), end='')
            time.sleep(0.1)
