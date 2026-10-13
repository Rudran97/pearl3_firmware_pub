import serial.tools.list_ports as port

for ports in port.comports():
    print(ports)
