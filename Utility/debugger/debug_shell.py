import debugger as dbg
import shlex
import argparse

"""
    Debug Shell interface. Will only run when debugger is used standalone.
"""

class DebugShell:
    def __init__(self, device_id, comm_port, speed, dtot, read_timeout):
        self.dbg = dbg.Debugger(
            device_id=device_id,
            comm_port=comm_port,
            speed=speed,
            read_timeout=read_timeout,
            test_mode=False
        )

        self.device_id = device_id
        self.dtot = dtot

        self.tui = DebugTUI()

        self.running = True
        self.last_line = ""

        self.bpts = {
            "Breakpoint 0": (f"{0:08x}", False),
            "Breakpoint 1": (f"{0:08x}", False),
        }

        ### Command table ###
        self.commands = {
            "info"      : self.cmd_info,
            "i"         : self.cmd_info,
            "step"      : self.cmd_step,
            "s"         : self.cmd_step,
            "sv"        : self.cmd_step_and_view_all,
            "continue"  : self.cmd_continue,
            "c"         : self.cmd_continue,
            "break"     : self.cmd_break,
            "b"         : self.cmd_break,
            "delete"    : self.cmd_delete,
            "d"         : self.cmd_delete,
            "x"         : self.cmd_mem,
            "enter"     : self.cmd_enter_debug,
            "e"         : self.cmd_enter_debug,
            "exit"      : self.cmd_exit,
            "quit"      : self.cmd_exit,
            "q"         : self.cmd_exit,
            "help"      : self.cmd_help,
        }

    def launch_debug_shell(self):
        print("Entering debugger shell. Type 'help' for commands.")

        while self.running:
            try:
                line = input("(prvdbg) ").strip()
                if not line:
                    if not self.last_line:
                        continue
                    else:
                        line = self.last_line

                args = shlex.split(line)
                cmd = args[0]
                cmd_args = args[1:]

                if cmd in self.commands:
                    self.commands[cmd](cmd_args)
                    self.last_line = line
                else:
                    print(f"Unknown command: {cmd}")
            except Exception as e:
                print(f"Error: {e}")
    
    def cmd_info(self, args):
        if not args:
            print("Usage: info <reg|csr|all>")
            return

        subcmd = args[0]

        gpr = self.dbg.getReg()
        csr = self.dbg.getCSR()
        pc, curr_insn, ret_insn = self.dbg.getProgInfo()

        if subcmd in ["reg", "registers", "r"]:
            self.tui.viewReg(gpr, show_reg_num=False, cols=8, align="left")
        elif subcmd in ["csr"]:
            self.tui.viewCSR(csr, cols=3, align="right")
        elif subcmd in ["prog"]:
            self.tui.viewProgInfo(pc, curr_insn, ret_insn, cell_sep=3, align="left")
        elif subcmd in ["io"]:
            io = self.dbg.getIO()
            self.tui.viewIO(io, cols=3)
        elif subcmd in ["clic"]:
            clic = self.dbg.getCLIC()
            self.tui.viewCLIC(clic, cols=3)
        elif subcmd in ["breakpoints", "b"]:
            self.tui.viewBreakpoints(self.bpts, cell_sep=2, align="left")
        elif subcmd in ["state"]:
            self.tui.viewReg(gpr, show_reg_num=False, cols=8, align="left")
            self.tui.viewCSR(csr, cols=3, align="right")
            self.tui.viewProgInfo(pc, curr_insn, ret_insn, cell_sep=3, align="left")
        else:
            print(f"Unknown info command: {subcmd}")
    
    def cmd_step(self, args):
        self.dbg.Step()
        self.dbg.getReg()
        self.dbg.getCSR()
        self.dbg.getProgInfo()
    
    def cmd_step_and_view_all(self, args):
        self.cmd_step(None)
        self.cmd_info(["state"])

    def cmd_continue(self, args):
        self.dbg.Continue()

    def cmd_break(self, args):
        if not args:
            print("Usage: break <trig_module> <addr>")
            return
        
        # hex (0x...), decimal
        addr = int(args[1], 0) & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
        addr_hex = hex(addr)    # convert the int into hex

        if args[0] == "0":
            if self.dbg.Trig0_set(addr_hex): self.bpts["Breakpoint 0"] = (addr_hex, True)
        elif args[0] == "1":
            if self.dbg.Trig1_set(addr_hex): self.bpts["Breakpoint 1"] = (addr_hex, True)
        else:
            print("Only trigger0 and trigger1 is supported")
            return

    def cmd_delete(self, args):
        if not args:
            print("Usage: delete <trig_module>")
            return

        module = int(args[0], 0)

        if module == 0:
            if self.dbg.Trig0_remove(): self.bpts["Breakpoint 0"] = (f"{0:08x}", False)
        elif module == 1:
            if self.dbg.Trig1_remove(): self.bpts["Breakpoint 1"] = (f"{0:08x}", False)
        else:
            print("Only trigger0 and trigger1 is supported")
            return

    def cmd_mem(self, args):
        if not args:
            print("Usage: x m:s:r:io:c <addr> <words>")
            return

        subcmd = args[0]

        if subcmd in ["m", "mem"] :
            if args[1] and args[2]:
                addr = int(args[1], 0) & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
                addr_hex = hex(addr)
                words = int(args[2], 0)
                val = []

                for c in range (0, words):
                    val.append(self.dbg.getMem(hex(int(addr_hex, 16) + (c << 2))))
                
                self.tui.viewMem(addr=addr_hex, value=val, header_name="Memory")
            else:
                print("For 'm' prvoide the base address <addr> and word counts <word> ")
        elif subcmd in ["s", "ram"]:
            if args[1] and int(args[1], 0) < self.dbg.devices.get(self.device_id).get("ram")[2]:
                page = int(args[1], 0) & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
                val = self.dbg.getRam(page)
                view_addr = hex(int(self.dbg.devices.get(self.device_id).get("ram")[0], 16) + page*256)
                self.tui.viewMem(addr=view_addr, value=val, header_name=f"Ram Page {page}")
            else:
                print("For 'ram' prvoide the page <page> to read. Page size must between 0 and", f'{self.dbg.devices.get(self.device_id).get("ram")[2]}')
        elif subcmd in ["r", "rom"]:
            if args[1] and int(args[1], 0) < self.dbg.devices.get(self.device_id).get("rom")[2]:
                page = int(args[1], 0) & int(str(0xffffffff), 0)  # make sure the integer fits within 32 bits
                val = self.dbg.getRom(page)
                view_addr = hex(int(self.dbg.devices.get(self.device_id).get("rom")[0], 16) + page*256)
                self.tui.viewRegion(addr=view_addr, value=val, type="rom", header_name=f"Rom Page {page}")
            else:
                print("For 'rom' prvoide the page <page> to read. Page size must between 0 and", f'{self.dbg.devices.get(self.device_id).get("rom")[2]}')
        elif subcmd in ["io"]:
            val = self.dbg.getIO()
            self.tui.viewRegion(addr=self.dbg.devices.get(self.device_id).get("io")[0], value=val, type="io", header_name="Peripherals")
        elif subcmd in ["c", "clic"]:
            val = self.dbg.getCLIC()
            self.tui.viewRegion(addr=self.dbg.devices.get(self.device_id).get("clic")[0], value=val, type="clic", header_name="CLIC")
        else:
            print(f"Unknown info command: {subcmd}")

    def cmd_enter_debug(self, args):
        prg_halt = False
        if args:
            subcmd = args[0]
        else:
            subcmd = ""

        if subcmd in ["nc", "ncmd"] :
            prg_halt = True

        self.dbg.enter_debug(tot_val=self.dtot, use_dtot=True, prg_halt=prg_halt)
        self.running = True

    def cmd_exit(self, args):
        self.dbg.Exit()
        for k in self.bpts.keys():
            self.bpts[k] = (f"{0:08x}", False)

        self.running = False

    def cmd_help(self, args):
        print("""
            Debugger commands:
            info|i reg|registers|r:csr:prog:state:clic:
                   breakpoints|b:io                      - Show registers:Show CSR:Show program info:Show all registers:
                                                           Show clic:Show breakpoints:Show peripheral registers.
            step|s                                       - Step one instruction.
            sv                                           - Step one instruction and view all infos.
            continue|c                                   - Resume execution.
            break|b 0:1 <addr>                           - Set HW breakpoint to either trig0 or trig1.
            delete 0:1                                   - delete breakpoint trig0 or trig1.
            x m <addr> <words>                           - Read specific memory section.
                                                           For 'm' type, base address and number of words to be fetched
                                                           must be provided.
              s|sram:r|rom <page>                        - Read SRAM or ROM section 1kB at a time.
                                                           For 's' and 'r' type, the page number must be provided
              io:c|clic                                  - Read Peripheral or Clic memory section.
            enter|e [<nc|ncmd>]                          - Enter debugger. Provide <nc> or <ncmd> when entering after program
                                                           and halt or reset and halt commands i.e., commands involving 0xAD.
            exit|quit|q                                  - Exit debugger.
            """)

##########################################################################################################
##########################################################################################################

"""
    Optional Text User Interface. Will only be used when debugger is run standalone
"""

class DebugTUI:
    reg_abi = [
        ("x0",  "zero"), ("x1",  "ra"),   ("x2",  "sp"),   ("x3",  "gp"),
        ("x4",  "tp"),   ("x5",  "t0"),   ("x6",  "t1"),   ("x7",  "t2"),
        ("x8",  "s0/fp"),("x9",  "s1"),   ("x10", "a0"),   ("x11", "a1"),
        ("x12", "a2"),   ("x13", "a3"),   ("x14", "a4"),   ("x15", "a5"),
        ("x16", "a6"),   ("x17", "a7"),   ("x18", "s2"),   ("x19", "s3"),
        ("x20", "s4"),   ("x21", "s5"),   ("x22", "s6"),   ("x23", "s7"),
        ("x24", "s8"),   ("x25", "s9"),   ("x26", "s10"),  ("x27", "s11"),
        ("x28", "t3"),   ("x29", "t4"),   ("x30", "t5"),   ("x31", "t6"),
    ]

    csr_list = {
		0: "misa",
		1: "mvendorid",
		2: "marchid",
		3: "mimpid",
		4: "mhartid",
		5: "minstret",
		6: "mstatus",
		7: "mie",
		8: "mtvec",
		9: "mip",
		10: "mcause",
		11: "mepc",
		12: "mscratch",
		13: "mtval",
		14: "tselect",
		15: "tdata1",
		16: "tdata2",
		17: "dcsr",
		18: "dpc",
		19: "dscratch0",
		20: "dscratch1"
    }

    io_list = {
        0: "DDRA",
        1: "PORTA",
        2: "LATA",
        3: "DDRB",
        4: "PORTB",
        5: "LATB",
        6: "LATD",
        7: "ALTOUTACON",
        8: "ALTOUTBCON",
        9: "ALTOUTA",
        10: "ALTOUTB",
        11: "T0CON",
        12: "T0L",
        13: "T0H",
        14: "T0ABUF",
        15: "T0BBUF",
        16: "T1CON",
        17: "T1L",
        18: "T1H",
        19: "T1ABUF",
        20: "T1BBUF",
        21: "T2CON",
        22: "T2L",
        23: "T2H",
        24: "T2ABUF",
        25: "T2BBUF",
        26: "T3CON",
        27: "T3L",
        28: "T3H",
        29: "T3ABUF",
        30: "T3BBUF",
        31: "T4CON",
        32: "T4L",
        33: "T4H",
        34: "T4BUF",
        35: "TC0BUF",
        36: "T5CON",
        37: "T5L",
        38: "T5H",
        39: "T5BUF",
        40: "TC1BUF",
        41: "TFREG",
        42: "INT0MAP",
        43: "INT1MAP",
        44: "INT2MAP",
        45: "INT3MAP",
        46: "INT4MAP",
        47: "INT5MAP",
        48: "INT6MAP",
        49: "INT7MAP",
        50: "ALTOUTEN",
        51: "URT0CON",
        52: "URT0BRG",
        53: "URT0TX",
        54: "URT0RX",
        55: "URT1CON",
        56: "URT1BRG",
        57: "URT1TX",
        58: "URT1RX",
        59: "I2C0CON0",
        60: "I2C0CON1",
        61: "I2C0CON2",
        62: "I2C0TX",
        63: "I2C0RX",
        64: "EXT0CON",
        65: "EXT1CON",
        66: "EXT2CON",
        67: "EXT3CON",
        68: "PWM0CON",
        69: "PWM0DC",
        70: "PWM1CON",
        71: "PWM1DC",
        72: "PWM2CON",
        73: "PWM2DC",
        74: "PWM3CON",
        75: "PWM3DC",
        76: "PWM4CON",
        77: "PWM4DC",
        78: "PWM5CON",
        79: "PWM5DC",
        80: "SPI0CON0",
        81: "SPI0CON1",
        82: "SPI0TX",
        83: "SPI0RX",
    }

    clic_list = {
        0: "INT0ADDR",
        1: "INT1ADDR",
        2: "INT2ADDR",
        3: "INT3ADDR",
        4: "INT4ADDR",
        5: "INT5ADDR",
        6: "INT6ADDR",
        7: "INT7ADDR",
        8: "INT0PRIO",
        9: "INT1PRIO",
        10: "INT2PRIO",
        11: "INT3PRIO",
        12: "INT4PRIO",
        13: "INT5PRIO",
        14: "INT6PRIO",
        15: "INT7PRIO",
        16: "INTCON",
        17: "IRQID",
        18: "INTSRC",
        19: "INTCLR",
        20: "INTSTAT",
    }

    def __init__(self):
        pass

    def to_printable(self, byte_val: int):
        if 0x20 <= byte_val <= 0x7E:
            return chr(byte_val)
        return "."

    def format_cells(self, name, alias, value, show_name=True, type="gpr", align="right"):
        """ Return a fixed-width cell """
        if align == "right":
            if type == "gpr":
                if show_name:
                    return f"{name:>3} {alias:>5} 0x{value:08x}"
                else:
                    return f"{alias:>5} 0x{value:08x}"
            if type == "csr":
                return f"{name:>9} 0x{value:08x}"
            elif type in ["pc", "insn", "break"]:
                return f"{name:>12} 0x{value:08x}"
            elif type in ["io_named", "clic_named"]:
                return f"{name:>12} 0x{value:04x}"
            elif type in ["mem", "stack"]:
                byte_line = f"[ 0x{name} ] "
                ch = ""

                for i in range(0, len(value), 8):
                    byte_line += f" {value[i+6:i+8]} {value[i+4:i+6]} {value[i+2:i+4]} {value[i:i+2]} "

                    b3 = int(value[i:i+2], 16)
                    b2 = int(value[i+2:i+4], 16)
                    b1 = int(value[i+4:i+6], 16)
                    b0 = int(value[i+6:i+8], 16)
                    ch += f" {self.to_printable(b0)} {self.to_printable(b1)} {self.to_printable(b2)} {self.to_printable(b3)} "

                return byte_line + ch
            elif type in ["rom", "clic", "io"]:
                return f"[ 0x{name} ] 0x{value}"
        elif align == "left":
            if type == "gpr":
                if show_name:
                    return f"{name:<3} {alias:<5} 0x{value:08x}"
                else:
                    return f"{alias:<5} 0x{value:08x}"
            if type in ["csr", "pc", "insn", "break"]:
                return f"{name:<9} 0x{value:08x}"

        return 0

    def print_text(self, header_name, cells, cell_sep=2, cols=3):
        # Determine max cell width to keep columns aligned
        cell_width = max(len(c) for c in cells) + cell_sep

        # +5 is added because there are 3 spaces in the front and 2 spaces in the back in each row
        header_border = "-"*(cell_width*cols - (len(header_name) + 9) + 5) 

        print(f"----- {header_name} " + header_border + "--")

        for i in range(0, len(cells), cols):
            row = cells[i:i+cols]

            # Pad incomplete rows with empty cells
            if len(row) < cols:
                row += [""] * (cols - len(row))

            formatted = "".join(f"{c:<{cell_width}}" for c in row)
            print(f"    {formatted} ")

        print("------" + "-"*len(header_name) + "-" + header_border + "--")

    def viewReg(self, reg_val, show_reg_num=True , cell_sep=2, cols=4, align="right"):
        cells = [self.format_cells(r, a, int(reg_val[int(r[1:])], 16), show_reg_num, type="gpr", align="right") for r, a in self.reg_abi]
        self.print_text(header_name="Registers", cells=cells, cell_sep=cell_sep, cols=cols)

    def viewCSR(self, csr_val, cell_sep=3, cols=4, align="left"):
        cells = [self.format_cells(csr, "", int(csr_val[num], 16), True, "csr", align) for num, csr in self.csr_list.items()]
        self.print_text(header_name="Control & Status Registers", cells=cells, cell_sep=cell_sep, cols=cols)
    
    def viewIO(self, io_val, cell_sep=2, cols=4):
        cells = [self.format_cells(io, "", int(io_val[num], 16), True, "io_named") for num, io in self.io_list.items()]
        self.print_text(header_name="Peripheral Registers", cells=cells, cell_sep=cell_sep, cols=cols)

    def viewCLIC(self, clic_val, cell_sep=2, cols=4):
        cells = [self.format_cells(clic, "", int(clic_val[num], 16), True, "clic_named") for num, clic in self.clic_list.items()]
        self.print_text(header_name="CLIC Registers", cells=cells, cell_sep=cell_sep, cols=cols)

    def viewProgInfo(self, pc, curr_insn, next_insn, cell_sep=2, cols=3, align="left"):
        cells = []
        cells.append(self.format_cells("pc", "", int(pc, 16), True, "pc", align=align))
        cells.append(self.format_cells("Curr Insn", "", int(curr_insn, 16), True, "insn", align=align))
        cells.append(self.format_cells("Ret Insn", "", int(next_insn, 16), True, "insn", align=align))

        self.print_text(header_name="Program Information", cells=cells, cell_sep=cell_sep, cols=cols)
    
    def viewBreakpoints(self, bpts, cell_sep=2, cols=1, align="left"):
        cells = [self.format_cells(name + " set at address " if state[1] else " Inactive ", "", int(state[0], 16), True, "break", align) for name, state in bpts.items()]
        self.print_text(header_name="Breakpoints", cells=cells, cell_sep=cell_sep, cols=cols)

    def viewMem(self, addr, value, header_name="Memory"):
        vl = dict()
        next_addr = int(str(addr), 16)

        for w in range (0, len(value)):
            if (w % 4 == 0) and (w != 0):
                next_addr += 4*4

            base_addr = format(next_addr, '08x')
            if base_addr in vl: vl[base_addr] += value[w]
            else: vl[base_addr] = value[w]
        
        cells = [self.format_cells(a, "", v, type="mem") for a, v in vl.items()]
        self.print_text(header_name=header_name, cells=cells, cols=1)
    
    def viewRegion(self, addr, value, type, header_name="Rom", cell_sep=3):
        cells = [self.format_cells(format(int(str(addr), 16) + i*4, '08x'), "", value[i], type=type) for i in range(0, len(value))]
        self.print_text(header_name=header_name, cells=cells, cell_sep=cell_sep, cols=3)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Pearl debugger shell:")

    # Arguments
    parser.add_argument('--device', help="Device ID", type=str, default="prvx3imc48sh")
    parser.add_argument('-p', '--port', help="Serial port to debugger", type=str, default="/dev/cu.usbserial-0078EE22")
    parser.add_argument('-s', '--speed', help="Serial communication speed", type=int, default=115200)
    parser.add_argument('--dtot', help="Debug timeout timer in seconds (must be in integer and value >= 1)", type=int, default=3)

    args = parser.parse_args()

    device_id = args.device.upper()
    port = args.port
    speed = args.speed
    dtot = args.dtot
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


    shell = DebugShell(device_id=device_id, comm_port=port, speed=speed, dtot=dtot_to_hex, read_timeout=read_timeout)
    shell.launch_debug_shell()