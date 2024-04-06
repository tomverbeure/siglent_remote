#!/usr/bin/env python3

import argparse
import pyvisa, sys, io
from pyvisa.constants import StatusCode

from PIL import Image

def screendump(address, filename):
    rm = pyvisa.ResourceManager('@py')

    # Siglent SDS3204X
    scope = rm.open_resource('TCPIP::%s' % address)

    print(scope.write('SCDP'))
#    if status == StatusCode.success:
    scope.read_termination = None
    data = scope.read_raw(2000000)
    image = Image.open(io.BytesIO(data))
    image.save(filename)
    scope.close()
    rm.close()

if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='Grab a screenshot from a Siglent DSO.')
    parser.add_argument('--output', '-o', dest='filename', required=True,
        help='the output filename')
    parser.add_argument('address', metavar='ADDRESS', nargs=1,
        help='the ip address or hostname of the DSO')
    
    args = parser.parse_args()
    screendump(args.address[0], args.filename)

