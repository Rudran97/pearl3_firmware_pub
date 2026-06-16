# Firmware and Libraries for Pearl3

This repository contains firmware, drivers, and libraries for the [Pearl3](https://github.com/Rudran97/pearl3_pub.git) RISC-V microcontroller. It also includes example projects demonstrating the use of various hardware peripherals and software components available on the platform.

---

## Repository Structure

`$REPO_TOP` refers to the project root directory. All paths listed below are relative to this location.

### Pearl3 Firmware Library - `$REPO_TOP/prv32Lib`

Contains Pearl3-specific support files, including:

* Linker scripts
* Startup code
* Peripheral drivers
* Hardware abstraction source files

Additional drivers for custom hardware peripherals should be added to this directory.

### Third-Party Device Library - `$REPO_TOP/libraries`

Contains libraries used to interface with external hardware devices such as displays, sensors, and communication modules.

Additional third-party libraries should be placed in this directory.

### Examples - `$REPO_TOP/example`

Contains example applications demonstrating the use of:

* Pearl3 peripheral drivers
* External hardware libraries
* FreeRTOS integration

This directory also includes FreeRTOS demonstration projects and example applications for the Pearl3 platform.

### Utility and Tools - `$REPO_TOP/Utility`

Contains host-side utility programs, including:

* Program loader
* Debugger tools
* Basic terminal program
* Development utilities

All utilities require Python 3.x to run.

---

## Debugger Support

To assist with software debugging on the Pearl3 platform, a custom [debug port](Utility/debugger/debugger.py) is provided. The debug port acts as a wrapper around the native debugging commands supported by the microcontroller and translates them into packets that can be interpreted by the on-chip debug module.

Communication with the debug module is performed through the [transport layer](Utility/debugger/transport.py), which uses the dedicated `DI` and `DO` programming/debug pins.

There are two primary ways to debug software on the Pearl3 platform:

---

### Debugging with Pearl TUI

The Pearl Text User Interface (TUI) consists of a [debug shell](Utility/debugger/debug_shell.py) built on top of the debug port.

The TUI organizes responses received from the microcontroller and presents them in dedicated panes for:

- General-purpose registers
- Control and Status Registers (CSRs)
- Peripheral registers
- Memory contents

This provides a lightweight debugging environment without requiring an external debugger.

**Note**
The TUI does not currently support source-level debugging, source code listing, or advanced debugging features typically found in GDB. Its primary purpose is to provide a simple and efficient debugging environment for small embedded software projects.

---

### Debugging with GDB

The Pearl3 platform also supports debugging through the GNU Debugger (GDB).

This functionality is provided by a custom [GDB server](Utility/debugger/server.py), which bridges communication between GDB and the Pearl3 debug module. The server listens on port `3333` and can be accessed using any GDB client that supports the Remote Serial Protocol (RSP).

In addition to the `gdb server`, the [debug bridge](Utility/debugger/debugBridge.py) provides a higher-level interface built on top of the `debug port`. It combines existing debug commands with supporting utility tools to perform more complex operations, such as resetting the microcontroller.

The server currently supports the following packet types:

| Packet | Description                 |
| :---   | :---                        |
| `g`    | Read all registers.         |
| `p`    | Read a single register.     |
| `m`    | Read memory.                |
| `c`    | Continue execution.         |
| `s`    | Single-step execution.      |
| `z`    | Remove hardware breakpoint. |
| `Z`    | Insert hardware breakpoint. |
| `q`    | Essential query packets.    |

**Note**
The current implementation supports read-only debugging. Register writes, memory writes, and software breakpoints are not supported.
The standard GDB breakpoint commands (`Z0` and `z0`) are mapped to the two hardware trigger modules implemented in the Pearl3 microcontroller.

### GDB Monitor Commands

The Pearl3 GDB server also supports a set of custom monitor commands that provide direct access to debugger-specific functionality.
Use:

```gdb
monitor help
```

to display the list of supported monitor commands.

---

## Third-Party Software

This repository incorporates source code from the following third-party projects:

### GDB dashboard

Repository:

<https://github.com/cyrus-and/gdb-dashboard>

Used as a lightweight visual interface inside GDB.

### printf for Embedded Systems

Repository:

<https://github.com/mpaland/printf>

Used as a lightweight alternative to the standard C library `printf()` implementation.

### ST7735 TFT Display Driver

Repository:

<https://github.com/bablokb/pic-st7735>

Used to interface with ST7735-based TFT display modules.

### FreeRTOS Kernel

Repository:

<https://github.com/FreeRTOS/FreeRTOS-Kernel>

Used as the basis for the Pearl3 FreeRTOS port and examples.

### Terrain Game Demo

<https://www.instructables.com/Arduino-Endless-Run-Game-Using-LCD-Display-Push-Bu/>

Used as the basis for a demonstration game ported to the Pearl3 platform.

---