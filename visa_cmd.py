#! /usr/bin/env python3

import sys
import pyvisa
from pyvisa.constants import StatusCode

rm = pyvisa.ResourceManager()
siglent = rm.open_resource("TCPIP::%s" % sys.argv[1])
print(siglent.query('*IDN?'))

result, status = siglent.write(sys.argv[2])
print(result)
print(status)
if status == StatusCode.success:
    print(siglent.query(':MEAS:VRMS? CHAN1'))

siglent.close()
rm.close()
