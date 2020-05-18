#! /usr/bin/env python3

import argparse
import vxi11

parser = argparse.ArgumentParser(description='Dump identification number.')
parser.add_argument('device', metavar='DEVICE', nargs=1, help='the ip address or hostname of the device')

args = parser.parse_args()

instr = vxi11.Instrument(args.device[0])
print(instr.ask("*IDN?"))


