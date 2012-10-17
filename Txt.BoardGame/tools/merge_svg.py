#!/usr/bin/env python3


import xml.etree.ElementTree as ET

overview = ET.parse('overview.svg')
root = overview.getroot()

tokenlib = ET.parse('tokenlib.svg')
#get token defs from tokenlib and add to root
tokendefs = tokenlib.findall('./{http://www.w3.org/2000/svg}defs')
root.append(tokendefs[0])




overview.write('overview_merged.svg')





