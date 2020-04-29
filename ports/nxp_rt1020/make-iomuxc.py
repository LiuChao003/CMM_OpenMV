#!/usr/bin/env python
"""Creates the pinmap file for i.MX RTxxxx"""

import argparse
import sys
import csv

import re

def main():
    parser = argparse.ArgumentParser(
        prog="make-iomuxc.py",
        usage="%(prog)s [options] [command]",
        description="Generate board specific pin file"
    )
    parser.add_argument(
        "-f", "--file",
        help="Specifies the iomuxc input file, usually they are fsl_iomuxc.h files",
        default="rt1020_fsl_iomuxc.h"
    )

    args = parser.parse_args(sys.argv[1:])
    print("// args=", sys.argv)

    print('// This file was automatically generated by make-iomuxc.py')
    print('//')

    
    dict ={}
    p = re.compile(r'#define\s+IOMUXC_')
    #ptnPinName = re.compile(r'[_A-Z]+[0-9]*[0-9][0-9]_[A-Z]')
    ptnPinName = re.compile(r'(?P<pin>[A-Z_]+[0-9]+[0-9_]*)')
    fd = open(args.file)
    for sLine in fd:
        r = re.match(p, sLine)
        if r == None:
            continue
        sLine = sLine[r.end():]
        pinType = sLine[:4]
        sLine = sLine[5:]
        if (pinType == 'SNVS'):
            n1 = sLine.find('GPIO')
            if n1 < 0:
                continue
            pinName = sLine[:n1-1]
        else:
            lst = sLine.split(' ')
            sMapVal = ''.join(lst[1:])
            sMapVal = sMapVal[:-2] if sMapVal[-2] == '\r' else sMapVal[:-1] # trim \r\n
            lst = lst[0].split('_')
            for i in range(-1, -len(lst), -1):
                if lst[i][0].isdigit():
                    pinName = '_'.join(lst[:i+1])
                    sigName = '_'.join(lst[i+1:])
                    if pinName in dict.keys():
                        dict[pinName] += [(sigName, sMapVal)]
                    else:
                        dict[pinName] = [(sigName, sMapVal)]                    
                    break
    fd.close()
    dict = dict
    lstOut = ['ComboName,AFReg,AF,InSelReg,InSel,PadCfgReg']
    for key in dict.keys():        
        lst = dict[key]
        for tup in lst:            
            sComboKey = key + '_' + tup[0]
            sMap = tup[1]
            lstOut.append(sComboKey + ',' + sMap)
    import os.path as path
    sCsvFile = path.splitext(args.file)[0] + '.csv'
    fd = open(sCsvFile, 'wb')
    sOut = '\r\n'.join(lstOut) + '\r\n'
    print(sOut)
    fd.write(sOut.encode())
    fd.close()
if __name__ == "__main__":
    main()