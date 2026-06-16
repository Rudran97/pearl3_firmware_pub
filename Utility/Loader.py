import re
import serial as ser
import time
import argparse

START_SERIAL = True

def read_serial(ser, read_data_type="id"):
    char1 = ser.read()
    buffer_size = ser.in_waiting
    rest_char = ser.read(buffer_size)
    # st = chr(char1[0]) + rest_char.decode("utf-8")
    if read_data_type == "id":
        st = char1.decode("utf-8") + rest_char.decode("utf-8")
    elif read_data_type == "dump":
        st = char1 + rest_char
    return st


def deliver_machine_code(file, comm_port, speed, device_id, action):
    catch_error = 0
    try:
        if START_SERIAL:
            Ser = ser.Serial(comm_port, speed, timeout=3)
        if action in ["p", "ph"]: # prog, halt after prog
            print("[INFO] Uploading ...")
            with open(file, 'r') as f:
                if START_SERIAL:
                    if action == "p": Ser.write(b'\xaa')
                    else: Ser.write(b'\xad')
                    dev_id = read_serial(Ser, "id")
                    print(f"[INFO] Device ID received: {dev_id}")
                else:
                    print(b'\xab')
                    dev_id = "PRV32IMX1515.0001"
                if '.' in dev_id:
                    if dev_id[:dev_id.index('.')] == device_id:
                        HEX_CODE = f.readlines()
                        for NEW_LINE in HEX_CODE:
                            hex_line = NEW_LINE.strip()
                            hex_array = []
                            hex_to_int_array = []
                            if hex_line != '':
                                if hex_line[0] == ':':
                                    hex_array.append('3a')
                                    hex_array += re.findall('.' * 2, hex_line[1:])
                                    for x in hex_array:
                                        hex_to_int_array = [int(x, 16)]
                                        try:
                                            format_hex_bytes = bytearray(hex_to_int_array)
                                            if START_SERIAL:
                                                Ser.write(format_hex_bytes)
                                            time.sleep(0.0001)
                                        except ValueError:
                                            print("[ERROR] Operand value out of range 0 to 255")
                                            catch_error = 1
                    else:
                        if START_SERIAL:
                            Ser.close()
                        print(f"[ERROR] Device ID {dev_id[:dev_id.index('.')]} did not match with selected device {device_id}")
                        return f"Device ID {dev_id[:dev_id.index('.')]} did not match with selected device {device_id}"
                else:
                    if START_SERIAL:
                        Ser.close()
                    print(f"[ERROR] Invalid Device ID {dev_id}")
                    return f"Invalid Device ID {dev_id}"
        elif action == "r": # soft reset
            print("[INFO] Resetting target.")
            dummy_seq = "3a00000001ff" # seq = end of file
            dummy_seq_ba = bytearray.fromhex(dummy_seq)

            Ser.write(b'\xaa') # prog
            dev_id = read_serial(Ser, "id")
            print(f"[INFO] Device ID received: {dev_id}")

            for b in dummy_seq_ba:
                if START_SERIAL:
                    Ser.write(b.to_bytes())
                time.sleep(0.0001)
        elif action == "rh": # soft reset and halt
            print("[INFO] Resetting target and entering debug mode.")
            dummy_seq = "3a00000001ff" # seq = end of file
            dummy_seq_ba = bytearray.fromhex(dummy_seq)

            Ser.write(b'\xad') # debug
            dev_id = read_serial(Ser, "id")
            print(f"[INFO] Device ID received: {dev_id}")

            for b in dummy_seq_ba:
                if START_SERIAL:
                    Ser.write(b.to_bytes())
                time.sleep(0.0001)
        elif action == "rd": # rom_dump
            if START_SERIAL:
                    Ser.write(b'\xad')
                    rom_dump = read_serial(Ser, "dump")
                    print(rom_dump)

        time.sleep(0.3)
        if START_SERIAL:
            Ser.close()
        if catch_error == 0:
            print("[INFO] Done.")
    except ValueError:
        print("[ERROR] Incorrect configuration")
        return "Incorrect configuration"
    except ser.SerialException as e:
        print("[ERROR] Comm Error! ", e)
        return e
    except FileNotFoundError:
        print(f"[ERROR] Hex file {file} not found")
        return f"Hex file {file} not found"
    

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Pearl device programmer:")

    # Arguments
    parser.add_argument('-f', '--file', help="Hex file to upload", type=str)
    parser.add_argument('--device', help="Device ID", type=str)
    parser.add_argument('-p', '--port', help="Serial port to debugger", type=str, default="/dev/cu.usbserial-0078EE22")
    parser.add_argument('-s', '--speed', help="Serial communication speed", type=int, default=115200)
    parser.add_argument('-a', '--action', help="p to program, e to enter debug after program", type=str, default="p")

    args = parser.parse_args()

    file = args.file
    comm_port = args.port
    speed = args.speed
    device_id = args.device.upper()
    action = args.action

    deliver_machine_code(file=file, comm_port=comm_port, speed=speed, device_id=device_id, action=action)