# This code is a modification of https://github.com/stemnic/pyAVRdbg/blob/master/main.py

import socket
import debugBridge
import signal
import sys
import select
import argparse

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 3333         # Port to listen on (non-privileged ports are > 1023)

lastPacket = ""

help_msg = "Supported commands:\n" \
           "reset         - Execute a soft reset of the microcontroller.\n" \
           "rest halt     - Execute a soft reset of the microcontroller and halt execution.\n" \
           "halt          - Halt execution and enter debug mode.\n" \
           "status        - Current status of the microcontroller.\n" \
           "breakpoints   - Currently active breakpoints.\n" \
           "help          - Display this.\n"

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

                if cmd == "reset":
                    dbg.reset()
                    sendPacket(socket, "OK")
                    return
                elif cmd == "halt":
                    dbg.stop()
                    sendPacket(socket, "OK")
                    return
                elif cmd == "reset halt":
                    dbg.reset_and_halt()
                    sendPacket(socket, "OK")
                    return
                elif cmd == "status":
                    string, _ = dbg.monitor_status()
                    sendPacket(socket, string.encode("ascii").hex())
                    return
                elif cmd == "breakpoints":
                    string = dbg.monitor_breakpoints()
                    sendPacket(socket, string.encode("ascii").hex())
                    return
                elif cmd == "help":
                    sendPacket(socket, help_msg.encode("ascii").hex())
                    return
                
                sendPacket(socket, "E01")
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

        print(f"M Command received: {addrSizeData}\naddr: {addr}, size: {size}, data: {data}")

        if dbg.writeMem(int(addr, 16), data, int(size, 16)):
            sendPacket(socket, "OK")
        else:
            sendPacket(socket, "E01")
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
    if data.decode("ascii").count("$") > 0:
        for n in range(data.decode("ascii").count("$")):
            validData = True
            data = data.decode("ascii")
            checksum = (data.split("#")[1])[:2]
            packet_data = (data.split("$")[1]).split("#")[0]
            if int(checksum, 16) != sum(packet_data.encode("ascii")) % 256:
                print("Checksum Wrong!")
                validData = False
            commands = []
            if validData:
                socket.sendall(b"+")
            else:
                socket.sendall(b"-")
            handleCommand(socket, packet_data)
    elif data == b"\x03":
        print("GDB pressed Ctrl-C")
        dbg.stop()
        socket.sendall(b"+")
        sendPacket(socket, SIGTRAP)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Pearl gdb-server:")

    # Arguments
    parser.add_argument('--device', help="Device ID", type=str, default="prvx3imc48sh")
    parser.add_argument('-p', '--port', help="Serial port to debugger", type=str, default="/dev/cu.usbserial-0078EE22")
    parser.add_argument('-s', '--speed', help="Serial communication speed", type=int, default=115200)
    parser.add_argument('--dtot', help="Debug timeout timer in seconds (must be in integer and value >= 1)", type=int, default=3)
    parser.add_argument('--xml', help="Device xml file containing information of registers", type=str)

    args = parser.parse_args()

    device_id = args.device.upper()
    port = args.port
    speed = args.speed
    dtot = args.dtot
    device_xml = args.xml

    read_timeout = dtot + 0.5  # Transport layer read timeout is

    if dtot < 1:
        parser.print_help()
        exit()
    else:
        ## e.g. "1387f9ff" -> 5000 * 1 ms : "f9ff" represents the prescale value that sets the timer to 1 ms. 5000 - 1 = 1387 in hex
        dtot_to_hex = "0x" + f"{(dtot*1000 - 1):04x}"[-4:] + "f9ff"

    print("Device: ", device_id)
    print("Port: ", port)
    print("Speed: ", speed)
    print("dtot: ", dtot)
    print("Device xml: ", device_xml)

    dbg = debugBridge.DebugBridge(device_id=device_id,
                                comm_port=port,
                                speed=speed,
                                dtot=dtot_to_hex,
                                read_timeout=read_timeout)
    dbg.stop()
    dbg.breakpointHWClear()

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
                    data = conn.recv(1024)
                    if len(data) > 0:
                        handleData(conn, data)