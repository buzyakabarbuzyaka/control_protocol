import serial
import time
import numpy as np


class SerialController:
    _ser = None
    WAITING_MAXIMUM = 1000000

    def __init__(self, device='/dev/ttyUSB0', baud_rate=115200, timeout=0.5):
        self._ser = serial.Serial(device, baud_rate, timeout=timeout)
        # time.sleep(0.1)

    def _read_status(self):
        for _ in range(self.WAITING_MAXIMUM):
            if self._ser.in_waiting:
                return self._ser.readline().strip().decode("ascii")
        return None

    @staticmethod
    def __convert_number(number: int):
        return number.to_bytes(2, byteorder='little')

    @staticmethod
    def __decode_position(byte_buffer: bytes):
        a_pos = int.from_bytes(byte_buffer[0:2], byteorder='little')
        b_pos = int.from_bytes(byte_buffer[2:4], byteorder='little')
        return a_pos, b_pos

    def _read_position(self):
        for _ in range(self.WAITING_MAXIMUM):
            if self._ser.in_waiting:
                tmp = self._ser.readline().strip()
                return self.__decode_position(tmp)
        return None

    def request_position(self):
        self._ser.write(b'PP')
        return self._read_position()

    def move_motor(self, motor: str, direction: str, steps: int):
        self._ser.write(f"{motor}{direction}".encode("ascii"))
        self._ser.write(self.__convert_number(steps))
        return self._read_status()

    def return_to_origin(self, motor: str, position: str):
        self._ser.write(f"{motor}{position}".encode("ascii"))
        # self._ser.write(self.__convert_number(steps))
        return self._read_status()

if __name__ == '__main__':
    sc = SerialController()
    print(sc.request_position())
