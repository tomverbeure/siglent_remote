#! /usr/bin/env python3

import vxi11

instr = vxi11.Instrument("192.168.1.176")
print(instr.ask("*IDN?"))


