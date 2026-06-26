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
    
        self.csr_addr = {
            # 32: "0x7B1", # pc = dpc
            33: 0x301, # misa     
            34: 0xF11, # mvendorid
            35: 0xF12, # marchid  
            36: 0xF13, # mimpid   
            37: 0xF14, # mhartid  
            38: 0xB02, # minstret 
            39: 0x300, # mstatus  
            40: 0x304, # mie      
            41: 0x305, # mtvec    
            42: 0x344, # mip      
            43: 0x342, # mcause   
            44: 0x341, # mepc     
            45: 0x340, # mscratch 
            46: 0x343, # mtval    
            47: 0x7A0, # tselect  
            48: 0x7A1, # tdata1   
            49: 0x7A2, # tdata2   
            50: 0x7B0, # dcsr     
            51: 0x7B1, # dpc      
            52: 0x7B2, # dscratch0
            53: 0x7B3, # dscratch1
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

            if mem is None: return None

            mem_ba = bytearray.fromhex(mem)                        # convert mem in the form of : bytearray(b'\xaa\xbb\xcc\xdd')
            mem_ba.reverse()                                       # reverse the order : bytearray(b'\xdd\xcc\xbb\xaa')
            print(f"@ {hex(align_addr + (w << 2))} : {mem}")

            data = data + mem_ba
        
        return data[offset:offset+size]
    
    def reverse_endian(self, word: str):
        return "".join(reversed([word[i:i+2] for i in range(0,8,2)]))

    def writeMem(self, address : int, value : str, size : int = 1):
        """
        write value to register memory location address.
        """

        """
        if address is not aligned:
            0. align_addr = align_address(address)
            1. aligned_word_read = read(align_addr)
            2. modified_word = modify only the portion of the aligned_word_read.
            3. write(align_addr, modified_word)
        
        for w in range(0, math.ceil(size / 4)):
            continue writing to word aligned memory from here onwards.
        
        --------------------------------------------------------------

        Scenario 1: Continuous memory writes:
        what happens when the last value to be written is not aligned?

        Example: size = 128 bytes,
                 base address = 0x1000_002a,
                 value = babaabcdf00d...0123
                 value_arr = [baba, abcdf00d, ..., 0123]

        First modification (always for the first word):
        -----------------------------------------------

        align_addr = 0x1000_0028
        align_word_read = read(align_addr) = let's say 0xcaadf00d
        
        addr     :   0x100000_28    29    2a    2b
        old data :            ca    ad    f0    0d (let's say)
        new_data :            ca    ad    ba    ba
                                         |________|
        ---

        subsequent modifications all word aligned:
        ------------------------------------------

        no read is required

        addr     :   0x100000_2c    2d    2e    2f
        old data :            ff    ee    cc    bb (let's say)
        new_data :            ab    cd    f0    0d 
                             |____________________|
        ---

        last address to be written to would be 0x1000_002a + (0x80 - 1) = 0x1000_00a9:
        ------------------------------------------------------------------------------

        align_addr = 0x1000_00a8
        align_word_read = read(align_addr) = let's say 0xaabbccdd

        addr     :   0x100000_a8    a9    aa    ab
        old data :            aa    bb    cc    dd (let's say)
        new_data :            01    23    cc    dd 
                             |________|
        ---

        --------------------------------------------------------------

        Scenario 2: Only a part of the memory is written:

        Example: size = 2 bytes,
                 base address = 0x1000_0029,
                 value = abcd
                 value_arr = [abcd]
        
        First modification (always for the first word):
        -----------------------------------------------

        align_addr = 0x1000_0028
        align_word_read = read(align_addr) = let's say 0xcaadf00d
        
        addr     :   0x100000_28    29    2a    2b
        old data :            ca    ad    f0    0d (let's say)
        new_data :            ca    ab    cd    0d
                                   |________|
        ---
        """

        addr = address & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
        align_addr = addr & ~0x3
        offset = addr - align_addr
        bytes_needed = offset + size
        end_addr = addr + size - 1
        byte_idx = 0

        self.ensure_debug_mode("write memory")

        for w in range (0, math.ceil(bytes_needed / 4)):
            new_data = ""
            if w == 0: # First modification (read-modify-write)
                # Always read the old contents and modify only the affected bytes
                old_data_le = self.dbg.getMem(hex(align_addr + (w << 2))) # returns mem value as a hex string e.g "aabbccdd" - little endian
                                                                          # i.e. "aa" sits at the lowest memory address
                if old_data_le is None:
                    print("[ERROR] Incompatible data.")
                    return False
                # Reorder bytes (little endian to big endian)
                old_data = self.reverse_endian(old_data_le)
                # Extract the bytes from value string
                bytes_value = value[byte_idx:8-(2*offset)]             # get the required number of bytes from the value string
                                                                       # that falls within the offset.
                lower_half = bytes_value + old_data[len(bytes_value)+(2*offset):]
                new_data = old_data[:8-len(lower_half)] + lower_half
                # print(f"old read data:{old_data_le}, reordered:{old_data}, modified data:{new_data}")
                byte_idx += len(bytes_value)
            elif end_addr - (align_addr + (w << 2)) > 3: # All subsequent modifications which are already word aligned (direct write)
                # Extract the bytes from value string
                bytes_value = value[byte_idx:byte_idx+8]               # get the required number of bytes from the value
                new_data = bytes_value
                byte_idx += 8
            else: # Last misaligned-address to be modified (read-modify-write)
                # Always read the old contents and modify only the affected bytes
                old_data_le = self.dbg.getMem(hex(align_addr + (w << 2))) # returns mem value as a hex string e.g "aabbccdd" - little endian
                                                                          # i.e. "aa" sits at the lowest memory address
                if old_data_le is None:
                    print("[ERROR] Incompatible data.")
                    return False
                # Reorder bytes (little endian to big endian)
                old_data = self.reverse_endian(old_data_le)
                bytes_value = value[byte_idx:]                         # get the required number of bytes from the value
                byte_idx += len(bytes_value)
                new_data = bytes_value + old_data[len(bytes_value):]

            # Reorder bytes (big endian to little endian)
            new_data_le = self.reverse_endian(new_data)
            self.dbg.setMem(hex(align_addr + (w << 2)), new_data_le)
        
        return True

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

    def writeGPR(self, regno : int, value : int):
        """
        write value to a GPR.
        """

        reg = regno & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
        reg_hex = hex(reg)                     # convert the int into hex string
        val = value & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
        val_hex = hex(val)                     # convert the int into hex string

        self.ensure_debug_mode("write register")
        self.dbg.setReg(reg_hex, val_hex)

        return True  # Right now always return True

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

    def writeCSR(self, regno : int, value : int):
        """
        write value to a CSR.
        """

        reg = self.csr_addr.get(regno)
        reg_hex = hex(reg)                     # convert the int into hex string
        val = value & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
        val_hex = hex(val)                     # convert the int into hex string

        self.ensure_debug_mode("write CSR")
        self.dbg.setReg(reg_hex, val_hex)

        return True  # Right now always return True

    def readPC(self):
        self.ensure_debug_mode("read PC")
        data = bytearray.fromhex(self.dbg.dpc)
        data.reverse()

        return data
    
    def writePC(self, value : int):
        val = value & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
        val_hex = hex(val)                     # convert the int into hex string

        self.ensure_debug_mode("write PC")
        self.dbg.setPC(val_hex)

        return True  # Right now always return True
    
    def writeRegister(self, regno : int, regval : str):
        """
        write value to register regno.
        """

        # reorder bytes from little to big endian
        value = self.reverse_endian(regval)

        if regno == 32:
            if self.writePC(int(value, 16)):
                return True
        elif regno < 32:
            # Core registers x0 - x31
            if self.writeGPR(regno, int(value, 16)):
                return True
        elif 32 < regno < 54:
            # CSRs
            if self.writeCSR(regno, int(value, 16)):
                return True
        
        return False

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