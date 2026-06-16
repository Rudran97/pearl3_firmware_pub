import math
import debugger as dbg
import sys
from pathlib import Path
import time

sys.path.append(str(Path(__file__).resolve().parent.parent))

import Loader

class DebugBridge(dbg.DeviceStatus):
    def __init__(self, device_id, comm_port, speed, dtot, read_timeout):
        self.dbg = dbg.Debugger(
            device_id=device_id,
            comm_port=comm_port,
            speed=speed,
            read_timeout=read_timeout,
            test_mode=False
        )

        self.device_id = device_id
        self.comm_port = comm_port
        self.speed = speed
        self.dtot = dtot

        self.breakpoints = {
            0: None,
            1: None
        }
    
    def ensure_debug_mode(self, cmd : str):
        tries = 0

        while (self.dbg.device_status != self.STOPPED and tries < 3):
            print(f"Trying to execute '{cmd}'. Device not halted. Entering debug mode.")
            self.stop()
            self.monitor_status()

            tries += 1
            time.sleep(0.5)
        
        return self.dbg.device_status == self.STOPPED 

    def step(self):
        self.ensure_debug_mode("step")
        self.dbg.Step()
        return self.dbg.device_status

    def run(self):
        if self.dbg.device_status == self.STOPPED:
            self.dbg.Continue()
        return self.dbg.device_status
    
    def stop(self, prg_halt=False):
        self.dbg.enter_debug(self.dtot, use_dtot=True, prg_halt=prg_halt)
        return self.dbg.device_status

    def breakpointHWSet(self, address : int):
        addr = address & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
        addr_hex = hex(addr)                      # convert the int into hex string

        self.ensure_debug_mode("breakpoints set")

        for b, a in self.breakpoints.items():
            if a is None:
                # If bpt was not set earlier i.e. it is None, then set the breakpoint
                if b == 1: self.dbg.Trig1_set(addr_hex)
                else: self.dbg.Trig0_set(addr_hex)

                self.breakpoints[b] = addr
                return "OK"
        
        return "E01"

    def breakpointHWClear(self, address=None):
        self.ensure_debug_mode("breakpoints clear")

        if address is None:
            self.dbg.Trig0_remove()
            self.dbg.Trig1_remove()

            return "OK"
        else:
            for b, a in self.breakpoints.items():
                if a == address:
                    # Only remove breakpoints if the address exists in the table
                    if b == 1: self.dbg.Trig1_remove()
                    else: self.dbg.Trig0_remove()

                    self.breakpoints[b] = None
                    return "OK"
        
        return "E01"

    def readMem(self, address : int, size : int):
        """
        read memory.

        address : address offset to read from. 
        size    : number of bytes to read from address offset.
        
        return bytearry in little-endian format.
        """

        addr = address & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
        align_addr = addr & ~0x3
        offset = addr - align_addr
        bytes_needed = offset + size

        self.ensure_debug_mode("read memory")
        data = bytearray()

        print(f"Original read request {hex(addr)} onwards, size {size} bytes")
        print(f"Reading from memory address {hex(align_addr)} onwards, size {bytes_needed} bytes")

        for w in range (0, math.ceil(bytes_needed / 4)):
            mem  = self.dbg.getMem(hex(align_addr + (w << 2)))     # returns mem value as a hex string e.g "aabbccdd"

            mem_ba = bytearray.fromhex(mem)                        # convert mem in the form of : bytearray(b'\xaa\xbb\xcc\xdd')
            mem_ba.reverse()                                       # reverse the order : bytearray(b'\xdd\xcc\xbb\xaa')
            print(f"@ {hex(align_addr + (w << 2))} : {mem}")

            data = data + mem_ba
        
        return data[offset:offset+size]

    def readRegs(self):
        """
        read register x0-x31.

        return bytearry in little-endian format.
        """

        data = bytearray()
        self.ensure_debug_mode("read registers")
        gpr = self.dbg.getReg()

        for reg in gpr:
            reg_ba = bytearray.fromhex(reg)
            reg_ba.reverse()
            data = data + reg_ba
        
        return data

    def readCSRs(self):
        """
        read CSR values. 21 CSRs in total.

        return bytearray in litte-endian format.
        """

        data = bytearray()
        self.ensure_debug_mode("read CSRs")
        csr = self.dbg.getCSR()

        for reg in csr:
            reg_ba = bytearray.fromhex(reg)
            reg_ba.reverse()
            data = data + reg_ba
        
        return data

    def readPC(self):
        self.ensure_debug_mode("read PC")
        data = bytearray.fromhex(self.dbg.dpc)
        data.reverse()

        return data

    def reset(self):
        self.ensure_debug_mode("reset")
        self.cleanup()

        time.sleep(0.5)
        Loader.deliver_machine_code("", self.comm_port, self.speed, self.device_id, "r")

    def reset_and_halt(self):
        self.ensure_debug_mode("reset and halt")
        time.sleep(0.5)

        self.cleanup()

        time.sleep(0.5)
        Loader.deliver_machine_code("", self.comm_port, self.speed, self.device_id, "rh")
        self.stop(prg_halt=True)

    def monitor_status(self):
        string = "Debug error. Execute halt command to re-enter debug mode.\n"

        if self.dbg.device_status == self.STOPPED:
            string = "Device Stopped in debug mode.\n"
        elif self.dbg.device_status == self.RUNNING:
            string = "Device Running.\n"
        elif self.dbg.device_status == self.UNDEF:
            string = "Device in UNDEF state.\n"
        elif self.dbg.device_status == self.TIMEOUT:
            string = "Debug timeout. Execute halt command to re-enter debug mode.\n"

        return string, self.dbg.device_status
    
    def monitor_breakpoints(self):
        string = "Device breakpoints:\n"

        for b, a in self.breakpoints.items():
            if a is None:
                string += f"{b} : {a}\n"
            else:
                string += f"{b} : 0x{hex(a)}\n"
        
        return string

    def cleanup(self):
        self.dbg.Exit()
        return self.dbg.device_status