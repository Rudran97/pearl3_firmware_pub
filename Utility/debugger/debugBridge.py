import math
import debugger as dbg
import sys
from pathlib import Path
import time

sys.path.append(str(Path(__file__).resolve().parent.parent))

import Loader

class DebugBridge(dbg.DeviceStatus):
    def __init__(self, device_id, comm_port, speed, dtot, read_timeout, silent="none"):
        self.dbg = dbg.Debugger(
            device_id=device_id,
            comm_port=comm_port,
            speed=speed,
            read_timeout=read_timeout,
            test_mode=False,
            silent=silent
        )

        self.loader = ImageLoader()

        self.device_id = device_id
        self.comm_port = comm_port
        self.speed = speed
        self.dtot = dtot
        self.silent_log = [""]

        if silent == "none":
            pass
        elif silent == "info":
            self.silent_log = ["info"]
        elif silent == "all":
            self.silent_log = ["info", "error"]

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

        self.ram_start = self.dbg.devices.get(self.device_id).get("ram")[0]
        self.ram_size_word = self.dbg.devices.get(self.device_id).get("ram")[1]
        self.rom_start = self.dbg.devices.get(self.device_id).get("rom")[0]
        self.rom_size_word = self.dbg.devices.get(self.device_id).get("rom")[1]
        self.io_start = self.dbg.devices.get(self.device_id).get("io")[0]
        self.io_size_word = self.dbg.devices.get(self.device_id).get("io")[1]
        self.clic_start = self.dbg.devices.get(self.device_id).get("clic")[0]
        self.clic_size_word = self.dbg.devices.get(self.device_id).get("clic")[1]

    def logging(self, msg, log_type):
        if log_type not in self.silent_log:
            print(msg)
    
    def ensure_debug_mode(self, cmd : str):
        tries = 0

        while (self.dbg.device_status != self.STOPPED and tries < 3):
            self.logging(f"Trying to execute '{cmd}'. Device not halted. Entering debug mode.", "info")
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

        self.logging(f"Original read request {hex(addr)} onwards, size {size} bytes", "info")
        self.logging(f"Reading from memory address {hex(align_addr)} onwards, size {bytes_needed} bytes", "info")

        for w in range (0, math.ceil(bytes_needed / 4)):
            mem  = self.dbg.getMem(hex(align_addr + (w << 2)))     # returns mem value as a hex string e.g "aabbccdd"

            if mem is None: return None

            mem_ba = bytearray.fromhex(mem)                        # convert mem in the form of : bytearray(b'\xaa\xbb\xcc\xdd')
            mem_ba.reverse()                                       # reverse the order : bytearray(b'\xdd\xcc\xbb\xaa')
            self.logging(f"@ {hex(align_addr + (w << 2))} : {mem}", "info")

            data = data + mem_ba
        
        return data[offset:offset+size]
    
    def reverse_endian(self, word: str):
        return "".join(reversed([word[i:i+2] for i in range(0,8,2)]))

    def writeMem(self, address : int, value : str, size : int = 1, ignore_value : bool = False):
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
                    self.logging("[ERROR] Incompatible data.", "error")
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
                    self.logging("[ERROR] Incompatible data.", "error")
                    return False
                # Reorder bytes (little endian to big endian)
                old_data = self.reverse_endian(old_data_le)
                bytes_value = value[byte_idx:]                         # get the required number of bytes from the value
                byte_idx += len(bytes_value)
                new_data = bytes_value + old_data[len(bytes_value):]

            # Reorder bytes (big endian to little endian)
            new_data_le = self.reverse_endian(new_data)
            self.dbg.setMem(hex(align_addr + (w << 2)), new_data_le, ignore_value)
        
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
    
    def begin_image(self):
        self.loader.begin()
    
    def save_firmware_image(self, address : int, data : str, size : int):
        if not self.loader.add_section(address, data, size):
            self.logging("[ERROR] Inactive image section cannot be modified.", "error")
            return False
        
        return True
    
    def finish_receive(self, command):
        if command == "X":
            return

        if self.loader.active and command != "M":
            self.logging(f"Freezing firmware image, {len(self.loader.image)} sections added.", "system")
            self.loader.done()

    def download_image(self, image_section : str = "all"):
        self.loader.done()

        if image_section == "all": self.logging(f"[INFO] Programming target with {len(self.loader.image)} sections ...", "system")
        for section in self.loader.image:
            if image_section == "all":
                if section.valid:
                    self.logging(f"[INFO] Programming section at address: {hex(section.address)}, size: {hex(section.size)}", "system")
                    self.writeMem(section.address, section.data, section.size)
                else:
                    self.logging("[ERROR] Image cannot be downloaded into target - Invalid section", "error")
                    return False
            else:
                region_start = int(self.dbg.devices.get(self.device_id).get(image_section)[0], 16)
                region_end = region_start + 4*self.dbg.devices.get(self.device_id).get(image_section)[1] - 1

                if section.valid and (region_start <= section.address <= region_end):
                    self.logging(f"[INFO] Programming section at address: {hex(section.address)}, size: {hex(section.size)}", "system")
                    self.writeMem(section.address, section.data, section.size)
                else:
                    self.logging(f"[INFO] Skipping section at address: {hex(section.address)}", "system")
        self.logging(f"[INFO] Done programming.", "system")
        
        return True

    def erase_firmware(self):
        self.loader.clear_image()

    def erase_target_firmware(self, image_section : str = "all"):
        self.logging(f"[INFO] Erasing {image_section} sections from target ...", "system")

        # Set value register now and ignore re-writing it again for subsequent memory addresses
        self.dbg.setVal("00"*4)
        if image_section == "ram":
            self.writeMem(int(self.ram_start, 16), "00"*self.ram_size_word*4, self.ram_size_word*4, ignore_value=True)
        elif image_section == "rom":
            self.writeMem(int(self.rom_start, 16), "00"*self.rom_size_word*4, self.rom_size_word*4, ignore_value=True)
        else:
            self.writeMem(int(self.ram_start, 16), "00"*self.ram_size_word*4, self.ram_size_word*4, ignore_value=True)
            self.writeMem(int(self.rom_start, 16), "00"*self.rom_size_word*4, self.rom_size_word*4, ignore_value=True)

        self.logging(f"[INFO] Done erasing.", "system")

        return True

    def inspect_image(self):
        string = "No firmware image found.\n" \

        if self.loader.image:
            string = "Firmware Image:\n" \
                    "---------------\n"
            string += f"Sections   : {len(self.loader.image)}\n"
            size = 0
            for section in self.loader.image:
                size += section.size
            string += f"Total Size : {size}\n"
            string += "\n"

            ram_section = "RAM\n"
            ram_start = int(self.ram_start, 16)
            ram_end = int(self.ram_start, 16) + self.ram_size_word*4 - 1
            rom_start = int(self.rom_start, 16)
            rom_section = "ROM\n"
            rom_end = int(self.rom_start, 16) + self.rom_size_word*4 - 1
            for section in self.loader.image:
                if section.valid:
                    if rom_start <= section.address <= rom_end:
                        rom_section += f"{hex(section.address)} size {section.size} bytes\n"

                    if ram_start <= section.address <= ram_end:
                        ram_section += f"{hex(section.address)} size {section.size} bytes\n"

            string += ram_section + "\n" + rom_section

        return string
    
    def memory_region(self):
        string = f"Device ID {self.device_id.upper()}\n"
        string += f"RAM\n{self.ram_start} - {hex(int(self.ram_start, 16) + self.ram_size_word*4 - 1)}  size {self.ram_size_word*4} bytes\n"
        string += f"CLIC\n{self.clic_start} - {hex(int(self.clic_start, 16) + self.clic_size_word*4 - 1)}  size {self.clic_size_word*4} bytes\n"
        string += f"IO\n{self.io_start} - {hex(int(self.io_start, 16) + self.io_size_word*4 - 1)}  size {self.io_size_word*4} bytes\n"
        string += f"ROM\n{self.rom_start} - {hex(int(self.rom_start, 16) + self.rom_size_word*4 - 1)}  size {self.rom_size_word*4} bytes\n"
        
        return string

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

class ImageLoader:
    """
    Save Firmware image in memory that would be loaded into the target later.
    
    begin() - Prepare the to receive new image.
    add_section(...) - Add firmware as memory chunks.
    done() - Freeze any new additions into the current image.
    clear() - Remove any existing image.
    """
    def __init__(self):
        self.image = []
        self.active = False
    
    def begin(self):
        self.clear_image()
        self.active = True
    
    def add_section(self, address : int, data : str, size : int):
        if self.active:
            self.image.append(FirmwareSection(address, data, size))
            return True

        return False
    
    def done(self):
        self.active = False

    def clear_image(self):
        self.image.clear()
        self.active = False

class FirmwareSection:
    """
    Organises the firmware information into image objects to be loaded into the target.
    """
    def __init__(self, address : int, data : str, size : int):
        self.address = address
        self.data = data
        self.size = size
        self.valid = True

        if size != len(data)//2:
            print(f"[ERROR] While loading Firmware Image - size {size} does not match with the size of data {len(data)//2}")
            self.valid = False