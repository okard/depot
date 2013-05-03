#!/usr/bin/env python3

import sys
import re

from lib.SvgWriter import SvgWriter
from lib.Token import TokenDB, Token
from lib.TokenWriter import writeTokenFront, writeTokenBack


if len(sys.argv) < 3:
        sys.exit("Usage: genLibrary TokenDB.txt path/template_{id}.svg")
    
print("Create svg library...")


#the function to write the definitions
def doit(token):
	 # each token one svg file
	# create name "generated/token_{0}.svg"
	# calcTokenValue(front, back)
	fileName = sys.argv[2].format(token.idno)
	svgfile = open(fileName, "w")
	svg = SvgWriter(svgfile)    
	svg.begin()
	
	# write symbols
	svg.beginDefs()
	writeTokenFront(svg, token)
	writeTokenBack(svg, token)
	svg.endDefs()
	
	# write drawings
	svg.file.write('<use xlink:href="#{0}" x="{1}mm" y="{2}mm" width="22mm" height="27mm" />\n'.format(token.idno+'f', 0, 0))
	svg.file.write('<use xlink:href="#{0}" x="{1}mm" y="{2}mm" width="22mm" height="27mm" />\n'.format(token.idno+'b', "7", 0))
	
	svg.end()
	svgfile.close()
	
	print("{0}-{1}-{2}-{3}".format(token.idno, token.directions, token.attack, token.defense))
	
	pass


tdb = TokenDB(sys.argv[1])
tdb.foreach(doit)
del tdb
