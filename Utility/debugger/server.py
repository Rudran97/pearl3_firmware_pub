# This code is a modification of https://github.com/stemnic/pyAVRdbg/blob/master/main.py

import socket
import debugBridge
import signal
import sys
import select
import argparse
import time

class RSPParser:
    def __init__(self):
        self.buffer = ""

    def feed(self, data):
        """
        Feed arbitrary chunks received from recv() into feed().
        The parser buffers incomplete packets and returns only
        complete packets.

        data : bytes returned by socket.recv()

        Returns:
            list of (payload, checksum)
        """

        # Append newest TCP data
        self.buffer += data.decode("ascii", errors="ignore")
        packets = []

        while True:
            # Discard everything before '$'
            start = self.buffer.find("$")

            if start == -1:
                self.buffer = ""
                break

            if start > 0:
                self.buffer = self.buffer[start:]
                start = 0

            # Wait until '#' arrives
            hash_pos = self.buffer.find("#", start)

            if hash_pos == -1:
                break

            # Wait until checksum arrives
            if len(self.buffer) < hash_pos + 3:
                break

            payload = self.buffer[start + 1 : hash_pos]
            checksum = self.buffer[hash_pos + 1 : hash_pos + 3]
            packets.append((payload, checksum))

            # Remove processed packet
            self.buffer = self.buffer[hash_pos + 3:]

        return packets

class MonitorParser:
    HELP_MSG = """
            Supported commands:
            reset [halt]             - Execute a soft reset of the target [and halt execution].
            halt                     - Halt execution and enter debug mode.
            info [status]            - Current status of the target.
                 [breakpoints|break] - Active breakpoints.
                 [image]             - Information about the firmware image stored in memory.
                 [memory]            - Target memory regions.
            capture                  - Prepare to receive a firmware image from the next GDB 'load' command.
            flash [rom:ram]          - Flash the firmware image stored in memory into target [only rom or ram section].
            erase image              - Erase firmware image stored in memory.
                  target [rom:ram]   - Erase all sections of the target [only rom or ram section of the target].
            help                     - Display this.
"""
    
    def __init__(self, debugger):
        self.dbg = debugger
    
    @staticmethod
    def rsp_string(string: str):
        return string.encode("ascii").hex() 

    def execute(self, command : str = ""):
        cmd = ' '.join(command.split()).split() # remove extra spaces and trailings spaces, after that split it into sub commands

        if len(cmd) > 0:
            if cmd[0] == "reset":
                if len(cmd) > 2:
                    return self.rsp_string(f"Command '{cmd[0]}' takes only one optional parameter.\n")
                if len(cmd) > 1:
                    if cmd[1] == "halt":
                        self.dbg.reset_and_halt()
                        return "OK"
                    else:
                        return self.rsp_string(f"Invalid parameter '{cmd[1]}' after '{cmd[0]}'.\n")
                else:
                    self.dbg.reset()
                    return "OK"
            elif cmd[0] == "halt":
                self.dbg.stop()
                return "OK"
            elif cmd[0] == "info":
                if  len(cmd) == 1:
                    string, _ = self.dbg.monitor_status()
                    return string.encode("ascii").hex()
                elif len(cmd) == 2:
                    if cmd[1] in ["breakpoints", "break"]:
                        string = self.dbg.monitor_breakpoints()
                        return string.encode("ascii").hex()
                    elif cmd[1] == "status":
                        string, _ = self.dbg.monitor_status()
                        return string.encode("ascii").hex()
                    elif cmd[1] == "image":
                        string = self.dbg.inspect_image()
                        return string.encode("ascii").hex()
                    elif cmd[1] == "memory":
                        string = self.dbg.memory_region()
                        return string.encode("ascii").hex()

                return self.rsp_string(f"Invalid parameter '{cmd[1]}' after '{cmd[0]}'.\n")
            elif cmd[0] == "capture":
                # Loading firmware with binary write is not supported instead this command would initialize the firmware image.
                self.dbg.begin_image()
                return self.rsp_string("Ready to receive firmware.\n")
            elif cmd[0] == "flash":
                if len(cmd) > 2:
                    return self.rsp_string(f"Command '{cmd[0]}' takes only one optional parameter.\n")
                if len(cmd) > 1:
                    if cmd[1] == "rom":
                        if self.dbg.download_image("rom"): return self.rsp_string("Done downloading rom image into target.\n")
                        else: return self.rsp_string("Error while trying to rom download image into target.\n")
                    elif cmd[1] == "ram":
                        if self.dbg.download_image("ram"): return self.rsp_string("Done downloading ram image into target.\n")
                        else: return self.rsp_string("Error while trying to ram download image into target.\n")
                    else:
                        return self.rsp_string(f"Invalid parameter '{cmd[1]}' after '{cmd[0]}'.\n")
                else:
                    if self.dbg.download_image("all"): return self.rsp_string("Done downloading image into target.\n")
                    else: return self.rsp_string("Error while trying to download image into target.\n")
            elif cmd[0] == "erase":
                if len(cmd) == 3:
                    # 3 parameters passed
                    if cmd[1] == "target":
                        if cmd[2] == "rom":
                            self.dbg.erase_target_firmware("rom")
                            return self.rsp_string("Erased rom image from target.\n")
                        elif cmd[2] == "ram":
                            self.dbg.erase_target_firmware("ram")
                            return self.rsp_string("Erased ram image from target.\n")
                        else:
                            return self.rsp_string(f"Invalid parameter '{cmd[2]}' after '{cmd[1]}'.\n")
                    else:
                        return self.rsp_string(f"Invalid parameter '{cmd[1]}' after '{cmd[0]}'.\n")
                elif len(cmd) == 2:
                    # 2 parameters passed
                    if cmd[1] == "image":
                        self.dbg.erase_firmware()
                        return self.rsp_string("Erased firmware image from host.\n")
                    elif cmd[1] == "target":
                        self.dbg.erase_target_firmware("all")
                        return self.rsp_string("Erased firmware image from target.\n")
                    else:
                        return self.rsp_string(f"Invalid parameter '{cmd[1]}' after '{cmd[0]}'.\n")

                return self.rsp_string(f"Passed too less or too many parameters for command {cmd[0]}.\n")

        return self.rsp_string(self.HELP_MSG)


HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 3333         # Port to listen on (non-privileged ports are > 1023)

lastPacket = ""

SIGTRAP = "S05"
last_SIGVAL = "S00" 

def signal_handler(sig, frame):
    print('You pressed Ctrl-C!')
    dbg.cleanup()
    sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)

def sendPacket(socket, packetData):
    lastPacket = packetData
    checksum = sum(packetData.encode("ascii")) % 256
    message = "$" + packetData + "#" + format(checksum, '02x')
    if packetData == "":
        message = "$#00"
    socket.sendall(message.encode("ascii"))

def handleCommand(socket, command):
    # Required support g, m, c, q, p, z, and s
    dbg.finish_receive(command[0])

    global last_SIGVAL
    if "?" == command[0]:
        sendPacket(socket, last_SIGVAL)
    elif "q" == command[0]:
        # Genral query
        if len(command) > 1:
            query = command[1:]
            if query == "Attached":
                sendPacket(socket, "0")
                return
            elif "Supported" in query:
                sendPacket(socket, "PacketSize=10000000;hwbreak+;swbreak-;qXfer:features:read+")
                return
            elif "Symbol::" in query:
                sendPacket(socket, "OK")
                return
            elif "C" == query[0]:
                sendPacket(socket, "")
                return
            elif "Offsets" in query:
                sendPacket(socket, "Text=000;Data=000;Bss=000")
                return
            elif "Rcmd" in query:
                cmd = bytes.fromhex(query.split(',')[1]).decode("ascii")
                sendPacket(socket, monitor.execute(cmd))
            elif "Xfer:features:read" in query:
                xml = ""
                with open(device_xml, 'r') as f: # prvx32_target.xml
                    xml = f.read()
                sendPacket(socket, "l" + xml)
                return
        sendPacket(socket, "")
    elif "s" == command[0]:
        if len(command) > 1:
            addr = command[1:]
        dbg.step()
        sendPacket(socket, SIGTRAP)
        last_SIGVAL = SIGTRAP
    elif "c" == command[0]:
        if len(command) > 1:
            addr = command[1:]
        
        status = dbg.run()

        if status == dbg.STOPPED:
            sendPacket(socket, SIGTRAP)
            last_SIGVAL = SIGTRAP

    elif "z" == command[0]:
        breakpointType = command[1]
        addr = command.split(",")[1]

        if breakpointType in ["0", "1"]:
            # HW breakpoint
            resp = dbg.breakpointHWClear(int(addr,16))
            sendPacket(socket, resp)
        else:
            # Not Supported
            sendPacket(socket, "")
    elif "Z" == command[0]:
        breakpointType = command[1]
        addr = command.split(",")[1]

        if breakpointType in ["0", "1"]:
            # HW breakpoint
            resp = dbg.breakpointHWSet(int(addr, 16))
            sendPacket(socket, resp)
        else:
            # Not Supported
            sendPacket(socket, "")
    elif "m" == command[0]:
        addrSize = command[1:]
        addr = addrSize.split(",")[0]
        size = addrSize.split(",")[1]
        
        data = bytearray()
        data = dbg.readMem(int(addr, 16), int(size, 16))

        if data is None:
            sendPacket(socket, "E01")
        else:
            dataString = ""
            for byte in data:
                dataString = dataString + format(byte, '02x')

            sendPacket(socket, dataString)
    elif "M" == command[0]:
        """ M command received: 80000000,4:0df0adca
            addr: 80000000, size: 4, data: 0df0adc -> little endian """

        addrSizeData = command[1:]
        addr = addrSizeData.split(",")[0]
        size = (addrSizeData.split(",")[1]).split(":")[0]
        data = (addrSizeData.split(",")[1]).split(":")[1]

        if dbg.loader.active:
            if dbg.save_firmware_image(int(addr, 16), data, int(size, 16)):
                sendPacket(socket, "OK")
            else:
                sendPacket(socket, "E01")
        else:
            if dbg.writeMem(int(addr, 16), data, int(size, 16)):
                sendPacket(socket, "OK")
            else:
                sendPacket(socket, "E01")
    elif "X" == command[0]:
        # dbg.begin_image()
        sendPacket(socket, "")
    elif "g" == command:
        regs = dbg.readRegs()
        pc = dbg.readPC()
        csrs = dbg.readCSRs()

        regString = ""
        for reg in regs:
            regString = regString + format(reg, '02x')
        pcString = ""
        for reg in pc:
            pcString = pcString + format(reg, '02x')
        csrString = ""
        for reg in csrs:
            csrString = csrString + format(reg, '02x')

        sendPacket(socket, regString + pcString + csrString)
    elif "G" == command[0]:
        data = command[1:]
        success = True

        if len(data) !=  54 * 8:
            sendPacket(socket, "E01")
            return

        for r in range(0, 54):
            if not dbg.writeRegister(r, data[8*r:8*r+8]):
                success = False
                break

        sendPacket(socket, "OK" if success else "E01")
    elif "k" == command[0]:
        dbg.cleanup()
        quit()
    elif "p" == command[0]:
        # Reads register
        if len(command) > 1:
            idx = int(command[1:], 0)
            if idx < 32:
                # Core registers x0 - x31
                reg = dbg.readRegs()[4*idx:4*idx+4] # Extract the specific register from the set
                reg.reverse()
                regString = ""
                for b in reg:
                    regString = regString + format(b, '02x')
                sendPacket(socket, regString)
            elif 32 < idx < 54:
                # CSRs
                csr = dbg.readCSRs()[4*(idx - 33):4*(idx - 33)+4] # Extract the specific CSR from the set
                csr.reverse()
                csrString = ""
                for b in csr:
                    csrString = csrString + format(b, '02x')
                sendPacket(socket, csrString)
            elif command[1:] == "32":
                pc = dbg.readPC()
                pc.reverse()
                pcString = ""
                for b in pc:
                    pcString = pcString + format(b, '02x')
                sendPacket(socket, pcString)
    elif "P" == command[0]:
        """ P command received: 20=0df0adca """
        regnoData = command[1:] 
        regno = regnoData.split("=")[0]
        data = regnoData.split("=")[1]

        if dbg.writeRegister(int(regno, 16), data):
            sendPacket(socket, "OK")
        else:
            sendPacket(socket, "E01")
    else:
        sendPacket(socket, "")

def readRegs(n):
    return "0"*2*n

def handleData(socket, data):
    if data == b"\x03":
        print("GDB pressed Ctrl-C")
        dbg.stop()
        socket.sendall(b"+")
        sendPacket(socket, SIGTRAP)
        return

    # Feed TCP stream into parser
    packets = rsp.feed(data)

    for payload, checksum in packets:
        # Verify checksum
        calc = sum(payload.encode("ascii")) & 0xff

        try:
            recv = int(checksum, 16)
        except ValueError:
            socket.sendall(b"-")
            continue

        if calc != recv:
            print(f"Checksum error: received={checksum} expected={calc:02x}")
            socket.sendall(b"-")
            continue

        # ACK packet
        socket.sendall(b"+")
        # Execute command
        handleCommand(socket, payload)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Pearl gdb-server:")

    # Arguments
    parser.add_argument('--device', help="Device ID", type=str, default="prvx3imc48sh")
    parser.add_argument('-p', '--port', help="Serial port to debugger", type=str, default="/dev/cu.usbserial-0078EE22")
    parser.add_argument('-s', '--speed', help="Serial communication speed", type=int, default=115200)
    parser.add_argument('--dtot', help="Debug timeout timer in seconds (must be in integer and value >= 1)", type=int, default=3)
    parser.add_argument('--xml', help="Device xml file containing information of registers", type=str)
    parser.add_argument('--silent-all', help="Silent all terminal outputs", action='store_true')
    parser.add_argument('--silent-info', help="Silent only info terminal outputs", action='store_true')

    args = parser.parse_args()

    device_id = args.device.upper()
    port = args.port
    speed = args.speed
    dtot = args.dtot
    device_xml = args.xml

    silent = "none"
    if args.silent_all:
        silent = "all"
    elif args.silent_info:
        silent = "info"

    read_timeout = dtot + 0.5  # Transport layer read timeout is

    if dtot < 1:
        parser.print_help()
        exit()
    else:
        ## e.g. "1387f9ff" -> 5000 * 1 ms : "f9ff" represents the prescale value that sets the timer to 1 ms. 5000 - 1 = 1387 in hex
        dtot_to_hex = "0x" + f"{(dtot*1000 - 1):04x}"[-4:] + "f9ff"

    print("Device:", device_id)
    print("Port:", port)
    print("Speed:", speed)
    print("dtot:", dtot)
    print("Device xml:", device_xml)
    print("Silent debug output:", silent)

    dbg = debugBridge.DebugBridge(device_id=device_id,
                                comm_port=port,
                                speed=speed,
                                dtot=dtot_to_hex,
                                read_timeout=read_timeout,
                                silent=silent)
    dbg.stop()
    dbg.breakpointHWClear()
    monitor = MonitorParser(dbg)

    rsp = RSPParser()

    print("Waiting for GDB session " + str(HOST) + ":" + str(PORT))
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        conn.setblocking(0)
        with conn:
            print('Connected by', addr)
            while True:
                # Should iterate through buffer and take out commands/escape characters
                ready = select.select([conn], [], [], 0.5)
                if ready[0]:
                    data = conn.recv(8192)
                    if len(data) > 0:
                        handleData(conn, data)