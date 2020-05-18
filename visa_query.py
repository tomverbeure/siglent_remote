#! /usr/bin/env python3

import sys
import pyvisa

rm = pyvisa.ResourceManager()
siglent = rm.open_resource("TCPIP::%s" % sys.argv[1])
print(siglent.query('*IDN?'))
print(siglent.query(sys.argv[2]))

