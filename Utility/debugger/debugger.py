import transport
import time

CMD_TRIG0      = 0xD0
CMD_TRIG1      = 0xD1
CMD_PC         = 0xD6
CMD_LOG_REG    = 0xDA
CMD_SET_REG    = 0xEA
CMD_LOG_MEM    = 0xDB
CMD_SET_MEM    = 0xEB
CMD_SET_VALUE  = 0xE6
CMD_STEP       = 0xDC
CMD_RESUME     = 0xDD
CMD_ENTER      = 0xDE
CMD_EXIT_STEP  = 0xDF

"""
    Debugger expects packets in the following format: 6 Bytes
    packet[0]    = cmd : 1 Byte
    packet[1..4] = address/param in little endian format : 4 Bytes
    packet[5]    = trigger status - only applicable in trigger cfg mode : 1 Byte

    Debugger status response and common error codes: 4 Bytes
    ---------------------------------------------------------------------------------------------------
    | Code             | Type        | Description                                                    |
    ---------------------------------------------------------------------------------------------------
    | [0x0000_<cmd>00] | NO ERROR    | Debugger was able to execute cmd and returned successfully.    |
    | [0x0000_0000]    | UNDEF STATE | Debugger previous exited with an error possibly due to timeout |
    |                  |             | error. Correct handling of this error includes sending Enter   |
    |                  |             | debug command again.                                           |
    | [0x0000_<cmd>AF] | TIMEOUT     | Debugger timeout error. Last cmd/subcmd did not produce any    |
    |                  |             | response from debugger.                                        |
    | [0x0000_<cmd>02] | INVALID CMD | Debugger responded with a comm error due to invalid cmd.       |
    | [0x0000_<cmd>03] | REG ACCESS  | Debugger was not able to access core GPRs/CSRs.                |
    ---------------------------------------------------------------------------------------------------
"""

class Debugger:
    devices = {
        "PRVX3IMC48SH": {
                     ## base addr, size by words, pages(1k Bytes per page)
            "rom"  : ["0x80000000", 12288, 48],
            "clic" : ["0x40000000", 21, 1],
            "io"   : ["0x20000000", 84, 1],
            "ram"  : ["0x10000000", 4096, 12],
        }
    }

    def __init__(self, device_id, comm_port, speed=115200, read_timeout=3, test_mode=False, silent="none"):
        self.device_id = device_id
        self.comm_port = comm_port
        self.speed = speed
        self.read_timeout = read_timeout
        self.test_mode = test_mode
        
        self.silent_log = [""]

        if silent == "none":
            pass
        elif silent == "info":
            self.silent_log = ["info"]
        elif silent == "all":
            self.silent_log = ["info", "error"]

        self.response = []
        self.response_size = 0

        self.gpr_val = []
        self.csr_val = []
        self.ret_pc = 0
        self.dpc    = 0
        self.curr_insn =0
        self.ret_insn =0

        self.valid_status = {
            "reg"     : False,
            "sram"    : False,
            "stack"   : False
        }

        self.device_status = DeviceStatus.UNDEF

        ### Initialize transport layer ###
        if not self.test_mode:
            self.transport = transport.Transport(self.comm_port, self.speed, self.read_timeout)
    
    def rearrange_addr(self, addr : int):
        # addr parameter must be in hex
        addr = format(int(str(addr), 16), '08x') # convert the hex parameter in a string representing hex without the 0x prefix
        addr_list = [(int(addr[i:i+2], 16)) for i in range(0, len(addr), 2)] 
        addr_list.reverse()
        return addr_list
    
    def cmd_to_debugger(self, cmd, param=0, status=0, prg_halt=False):
        param = self.rearrange_addr(param)
        packet = []
        
        if not prg_halt:
            # Do not send <cmd> after 0xAD (program_and_halt) command was sent earlier. The core is partially in debug mode as
            # it already received the "enter debug" command from the host_if (dbg_sel). So only send the dtot information and
            # ignore <cmd>.
            packet.append(cmd)
        packet.extend(param)
        packet.append(status)

        if not self.test_mode:
            self.transport.write(packet)
        else:
            print(packet)
            for ele in packet:
                print(hex(ele))
    
    def get_debugger_response(self, size=4):
        if not self.test_mode:
            self.response, self.response_size = self.transport.read(size)
        else:
            self.response = ['DD', 'CC', 'BB', 'AA']
            self.response_size = 4
    
    def error(self, cmd, error_type):
        self.logging(f"[ERROR] Command {cmd} could not be executed", log_type="error")
        self.logging(f"[INFO] {error_type}", log_type="error")
    
    def info(self, msg):
        self.logging(msg, log_type="info")
    
    def logging(self, msg, log_type):
        if log_type not in self.silent_log:
            print(msg)
    
    def eval_response(self, cmd, resp):
        """
        Debugger status response and common error codes: 4 Bytes
        ---------------------------------------------------------------------------------------------------
        | Code             | Type        | Description                                                    |
        ---------------------------------------------------------------------------------------------------
        | [0x0000_<cmd>00] | NO ERROR    | Debugger was able to execute cmd and returned successfully.    |
        | [0x0000_0000]    | UNDEF STATE | Debugger previous exited with an error possibly due to timeout |
        |                  |             | error. Correct handling of this error includes sending Enter   |
        |                  |             | debug command again.                                           |
        | [0x0000_<cmd>AF] | TIMEOUT     | Debugger timeout error. Last cmd/subcmd resulted in a timeout. |
        | [0x0000_<cmd>02] | INVALID CMD | Debugger responded with a comm error due to invalid cmd.       |
        | [0x0000_<cmd>03] | REG ACCESS  | Debugger was not able to access core GPRs/CSRs.                |
        ---------------------------------------------------------------------------------------------------
        """
        if resp:
            cmd_code = resp[6:].upper()
            code = resp[4:].upper()
        else:
            self.error(f"0x{cmd:02x}", f" Response - '{resp}', debugger did not respond.")
            self.device_status = DeviceStatus.ERROR
            return False

        if cmd == CMD_TRIG0:
            if code == "0000":
                self.error("Trigger 0", f" Response - '{resp}', UNDEF STATE - execute enter debug command.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['AF']:
                self.error("Trigger 0", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.TIMEOUT
            else:
                self.info("[INFO] Trigger 0 command executed successfully.")
                self.device_status = DeviceStatus.STOPPED
                return True
            return False
        if cmd == CMD_TRIG1:
            if code == "0000":
                self.error("Trigger 1", f" Response - '{resp}', UNDEF STATE - execute enter debug command.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['AF']:
                self.error("Trigger 1", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.TIMEOUT
            else:
                self.info("[INFO] Trigger 1 command executed successfully.")
                self.device_status = DeviceStatus.STOPPED
                return True
            return False
        if cmd == CMD_SET_REG:
            if code == "0000":
                self.error("Set register", f" Response - '{resp}', UNDEF STATE - execute enter debug command.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['AF']:
                self.error("Set register", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.TIMEOUT
            else:
                self.info("[INFO] Set register command executed successfully.")
                self.device_status = DeviceStatus.STOPPED
                return True
            return False
        if cmd == CMD_SET_MEM:
            if code == "0000":
                self.error("Set memory", f" Response - '{resp}', UNDEF STATE - execute enter debug command.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['AF']:
                self.error("Set memory", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.TIMEOUT
            else:
                self.info("[INFO] Set memory command executed successfully.")
                self.device_status = DeviceStatus.STOPPED
                return True
            return False
        if cmd == CMD_SET_VALUE:
            if code == "0000":
                self.error("Set value", f" Response - '{resp}', UNDEF STATE - execute enter debug command.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['AF']:
                self.error("Set value", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.TIMEOUT
            else:
                self.info("[INFO] Set value command executed successfully.")
                self.device_status = DeviceStatus.STOPPED
                return True
            return False
        if cmd == CMD_STEP:
            if code == "0000":
                self.error("Step", f" Response - '{resp}', UNDEF STATE - execute enter debug command.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['AF']:
                self.error("Step", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.TIMEOUT
            else:
                self.info("[INFO] In step mode.")
                self.device_status = DeviceStatus.STOPPED
                return True
            return False
        elif cmd == CMD_RESUME:
            if code == "0000":
                self.error("Resume", f" Response - '{resp}', UNDEF STATE - execute enter debug command.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['AF']:
                self.error("Resume", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.TIMEOUT
            else:
                self.info("[INFO] Resuming execution.")
                self.device_status = DeviceStatus.RUNNING
                return True
            return False
        elif cmd == CMD_ENTER:
            if cmd_code in ['AF']:
                self.error("Enter debug", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['02']:
                self.error("Enter debug", f" Response - '{resp}', INVALID CMD - debugger already in debug mode.")
                self.device_status = DeviceStatus.STOPPED
            else:
                self.info("[INFO] Entered debug mode.")
                self.device_status = DeviceStatus.STOPPED
                return True
            return False
        elif cmd == CMD_EXIT_STEP:
            if code == "0000":
                self.error("Exit step", f" Response - '{resp}', UNDEF STATE - execute enter debug command.")
                self.device_status = DeviceStatus.UNDEF
            elif cmd_code in ['AF']:
                self.error("Exit step", f" Response - '{resp}', TIMEOUT - debugger responded with timeout error.")
                self.device_status = DeviceStatus.TIMEOUT
            else:
                self.info("[INFO] Exiting step mode.")
                self.device_status = DeviceStatus.STOPPED
                return True
            return False
        return False

    def pop_4bytes(self) -> str:
        """
        This method pops 4 bytes from response top and returns the word MSB to LSB form.
        e.g response = ['dd', 'cc', 'bb', 'aa', '11', '20', '30', ...]
        response now becomes ['11', '20', '30', ...]

        returns 'aabbccdd'  without the prefix
        """
        
        if self.response:
            word_list = self.response[:4]
            del self.response[:4]
            word_list.reverse()
            word = ''
            for bytes in word_list:
                word += bytes
            
            return word
        return None

    def enter_debug(self, tot_val=0, use_dtot=False, prg_halt=False):
        self.cmd_to_debugger(CMD_ENTER, tot_val, 1 if use_dtot else 0, prg_halt)
        self.get_debugger_response()
        resp = self.pop_4bytes()

        if not self.eval_response(CMD_ENTER, resp):
            self.logging("[ERROR] Enter debug", "error")
            return False
        
        return True
        
    def exit_step(self):
        self.cmd_to_debugger(CMD_EXIT_STEP)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        if not self.eval_response(CMD_EXIT_STEP, resp): self.logging("[ERROR] Exit step", "error")

    def log_reg_all(self):
        self.cmd_to_debugger(CMD_LOG_REG)
        self.get_debugger_response(size=53*4)

        ### Expecting 32 GPRs and 21 CSRs ###
        if self.response_size != 53*4:
            self.error("Log Reg", f"Expected 53*4 = {53*4} bytes but got {self.response_size} bytes instead")
        else:
            ### get GPR values ###
            self.gpr_val.clear()
            for _ in range(0, 32):
                value = self.pop_4bytes()
                if value:
                    self.gpr_val.append(value)

            ### get CSR values ###
            self.csr_val.clear()
            for _ in range(0, 32):
                value = self.pop_4bytes()
                if value:
                    self.csr_val.append(value)
            
            ### get PC of the retired instruction ###
            self.cmd_to_debugger(CMD_PC)
            self.get_debugger_response()
            self.ret_pc = self.pop_4bytes()
            self.dpc = self.csr_val[18]

            self.valid_status["reg"] = True
    
    def setVal(self, value : str):
        ## set the value and check the response
        self.cmd_to_debugger(CMD_SET_VALUE, value)
        self.get_debugger_response()
        resp = self.pop_4bytes()
        if self.eval_response(CMD_SET_VALUE, resp): self.info(f"[INFO] Value register set to {value}")
        else: self.logging("[ERROR] Set Value", "error")

        return None
    
    def getMem(self, addr : str) -> str:
        self.cmd_to_debugger(CMD_LOG_MEM, addr)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        if resp: return resp
        else: self.error("Read Mem", "debugger did not respond")

        return None

    def setMem(self, addr : str, value : str):
        self.setVal(value)

        ## set mem and check the response 
        self.cmd_to_debugger(CMD_SET_MEM, addr)
        self.get_debugger_response()
        resp = self.pop_4bytes()
        if self.eval_response(CMD_SET_MEM, resp): self.info(f"[INFO] Memory {addr} set.")
        else: self.logging("[ERROR] Set Memory", "error")

        for k, v in self.valid_status.items():
            self.valid_status[k] = False
        
        return None

    def getReg(self):
        if not self.valid_status.get("reg"):
            self.log_reg_all()

        return self.gpr_val

    def getCSR(self):
        if not self.valid_status.get("reg"):
            self.log_reg_all()

        return self.csr_val

    def setReg(self, regno : str, value : str):
        self.setVal(value)

        ## set register and check the response 
        self.cmd_to_debugger(CMD_SET_REG, regno)
        self.get_debugger_response()
        resp = self.pop_4bytes()
        if self.eval_response(CMD_SET_REG, resp): self.info(f"[INFO] Register {regno} set.")
        else: self.logging("[ERROR] Set Register", "error")

        for k, v in self.valid_status.items():
            self.valid_status[k] = False
        
        return None
    
    def setPC(self, value : str):
        # set dpc to value
        self.setReg("0x000007B1", value)

        return None

    def getRom(self, page):
        contents = []
        base_addr = self.devices.get(self.device_id).get("rom")[0]
        total_pages = self.devices.get(self.device_id).get("rom")[2] 

        if page < total_pages:
            ### 1kB = 1024 bytes = 256 words. So 256 words per page is going to be fetched
            for w in range(page*256, (256 + page*256)):
                contents.append(self.getMem(hex(int(base_addr, 16) + (w << 2))))
        
        return contents

    def getCLIC(self):
        contents = []
        base_addr = self.devices.get(self.device_id).get("clic")[0]
        words = self.devices.get(self.device_id).get("clic")[1]

        for w in range(0, words):
            contents.append(self.getMem(hex(int(base_addr, 16) + (w << 2))))
        
        return contents

    def getIO(self):
        contents = []
        base_addr = self.devices.get(self.device_id).get("io")[0]
        words = self.devices.get(self.device_id).get("io")[1]

        for w in range(0, words):
            contents.append(self.getMem(hex(int(base_addr, 16) + (w << 2))))
        
        return contents

    def getRam(self, page):
        contents = []
        base_addr = self.devices.get(self.device_id).get("ram")[0]
        total_pages = self.devices.get(self.device_id).get("ram")[2] 

        if page < total_pages:
            ### 1kB = 1024 bytes = 256 words. So 256 words per page is going to be fetched
            for w in range(page*256, (256 + page*256)):
                contents.append(self.getMem(hex(int(base_addr, 16) + (w << 2))))
        
        return contents

    def getStack(self, sp, fp):
        pass

    def getProgInfo(self) -> str:
        if not self.valid_status.get("reg"):
            self.log_reg_all()

        self.ret_insn = self.getMem(self.ret_pc)
        self.curr_insn = self.getMem(self.dpc)

        return self.dpc, self.curr_insn, self.ret_insn

    def Exit(self):
        self.exit_step()
        time.sleep(0.01)
        self.Trig0_remove()
        time.sleep(0.01)
        self.Trig1_remove()
        time.sleep(0.01)
        self.cmd_to_debugger(CMD_RESUME)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        if self.eval_response(CMD_RESUME, resp): self.info("[INFO] Exiting debug mode.")
        else: self.logging("[ERROR] Exit debug", "error")

        for k, v in self.valid_status.items():
            self.valid_status[k] = False

    def Step(self):
        self.cmd_to_debugger(CMD_STEP)
        time.sleep(0.01)
        self.cmd_to_debugger(CMD_RESUME)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        if self.eval_response(CMD_RESUME, resp):
            self.info("[INFO] Stepping over 1 instruction.")
            self.device_status = DeviceStatus.STOPPED
        else: self.logging("[ERROR] Step", "error")

        for k, v in self.valid_status.items():
            self.valid_status[k] = False

    def Continue(self):
        self.exit_step()
        time.sleep(0.01)
        self.cmd_to_debugger(CMD_RESUME)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        status = ContinueStatus.ERROR

        if self.eval_response(CMD_RESUME, resp):
            if resp[4:].upper() in ['DD00']:
                self.info("[INFO] Exiting debug mode - no trigger set")
                status = ContinueStatus.NO_TRIGGER
                self.device_status = DeviceStatus.RUNNING
            else:
                self.info("[INFO] Trigger Hit!")
                status = ContinueStatus.HIT
                self.device_status = DeviceStatus.STOPPED
        else:
            self.logging("[ERROR] Continue", "error")
            status = ContinueStatus.ERROR
            self.device_status = DeviceStatus.ERROR

        for k, v in self.valid_status.items():
            self.valid_status[k] = False
        
        return status

    def Trig0_set(self, addr : str):
        self.cmd_to_debugger(CMD_TRIG0, addr, status=1)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        if self.eval_response(CMD_TRIG0, resp): self.info(f"[INFO] Trigger 0 set to {addr}")
        else: self.logging("[ERROR] Set Trigger 0", "error")

        return resp

    def Trig1_set(self, addr : str):
        self.cmd_to_debugger(CMD_TRIG1, addr, status=1)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        if self.eval_response(CMD_TRIG1, resp): self.info(f"[INFO] Trigger 1 set to {addr}")
        else: self.logging("[ERROR] Set Trigger 1", "error")

        return resp

    def Trig0_remove(self):
        self.cmd_to_debugger(CMD_TRIG0, status=0)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        if self.eval_response(CMD_TRIG0, resp): self.info("[INFO] Trigger 0 removed.")
        else: self.logging("[ERROR] Remove Trigger 0", "error")

        return resp

    def Trig1_remove(self):
        self.cmd_to_debugger(CMD_TRIG1, status=0)

        self.get_debugger_response()
        resp = self.pop_4bytes()

        if self.eval_response(CMD_TRIG1, resp): self.info("[INFO] Trigger 1 removed.")
        else: self.logging("[ERROR] Remove Trigger 1", "error")

        return resp

class ContinueStatus:
    HIT = 1
    NO_TRIGGER = 3
    ERROR = 4

class DeviceStatus:
    STOPPED = 0
    RUNNING = 1
    UNDEF = 2
    TIMEOUT = 3
    ERROR = 4