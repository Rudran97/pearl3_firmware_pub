import sys
import threading
import queue
import serial as ser
import time

def read_kbd_input(inputQueue):
    while (True):
        data = input("@")
        inputQueue.put(data)

def launch_terminal():
    _, comm_port, speed, data_type = sys.argv
    Ser = ser.Serial(comm_port, speed, timeout=0.5, write_timeout=0.5)
    
    EXIT_COMMAND = "exit"
    inputQueue = queue.Queue()
    inputThread = threading.Thread(target=read_kbd_input, args=(inputQueue,), daemon=True)
    inputThread.start()
    
    while (True):
        if (inputQueue.qsize() > 0):
            data = inputQueue.get()

            if (data == EXIT_COMMAND):
                print("Exiting sparrow terminal.")
                break
            
            # serial write routine
            if data_type == "i":
                if 0 <= int(data) <= 255:
                    hex_to_int_array = [int(data)]
                    format_hex_bytes = bytearray(hex_to_int_array)
                    Ser.write(format_hex_bytes)
            elif data_type == "c":
                if len(data) == 1:
                    Ser.write(data.encode())
            elif data_type == "s":
                for ch in data:
                    Ser.write(ch.encode())
                    time.sleep(0.0001)

        # serial read routine
        rd = Ser.read()
        if len(rd) > 0:
            rd = rd[0]
            print(chr(rd), end="")

        time.sleep(0.001) 

if __name__ == "__main__":
    if len(sys.argv) == 4:
        launch_terminal()
    else:
        print("Expected arguments : port_name, speed, data_type[i - integer, c - character, s - string]")
