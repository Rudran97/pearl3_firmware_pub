""" This file contains the physical transport layer implementation. """

import serial
import time

class Transport:
    def __init__(self, comm_port, speed, timeout):
        self.ser = serial.Serial(comm_port, speed, timeout=timeout, write_timeout=0.05)
    
    def write1byte(self, data):
        # Actual packet transfer takes place here
        if 0 <= int(data) <= 255:
            hex_to_int_array = [int(data)]
            format_hex_bytes = bytearray(hex_to_int_array)
            self.ser.write(format_hex_bytes)
        else:
            raise ValueError('Serial byte data must be in range 0 to 255 but got ', data)
    
    def write(self, packet):
        self.ser.reset_input_buffer() # reset the input buffer before sending any command
        for data in packet:
            self.write1byte(data)
            time.sleep(0.0001)
    
    def read(self, size=4):
        if size > 200: time.sleep(0.060)
        rec = self.ser.read(size=size)
        packet = []

        for bytes in rec:
            packet.append(format(bytes, '02x'))

        ### returns hex packet list without the prefix. For example: packets = ['aa', '0b', 'c0', '00']
        return packet, size
