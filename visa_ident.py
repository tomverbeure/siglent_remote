#! /usr/bin/env python3

import pyvisa

rm = pyvisa.ResourceManager()
#siglent = rm.open_resource("TCPIP::192.168.1.176::INSTR")
siglent = rm.open_resource("TCPIP::192.168.1.176")
print(siglent.query('*IDN?'))

