#!/usr/bin/env python3

import sys
import xml.etree.ElementTree as ET


#TODO extract tokenlib file from uses in overview?

if len(sys.argv) < 3:
    sys.exit("Usage: script overview.svg tokenlib.svg") 


overview = ET.parse(sys.argv[1])
root = overview.getroot()

tokenlib = ET.parse(sys.argv[2])
#get token defs from tokenlib and add to root
tokendefs = tokenlib.findall('./{http://www.w3.org/2000/svg}defs')
root.append(tokendefs[0])

#write new merged file
overview.write('merged_'+sys.argv[1])





