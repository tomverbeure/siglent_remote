#! /usr/bin/env python3

import pdb
import argparse
import vxi11

parser = argparse.ArgumentParser(description='Dump identification number.')
parser.add_argument('device', metavar='DEVICE', nargs=1, help='the ip address or hostname of the device')

args = parser.parse_args()

pdb.Pdb().set_trace()

instr = vxi11.Instrument(args.device[0])
print(instr.ask("*IDN?"))


