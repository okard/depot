#!/usr/bin/env python3

import sys
import re

from lib.SvgWriter import SvgWriter
from lib.Token import TokenDB, Token
from lib.TokenWriter import writeTokenFront, writeTokenBack


if len(sys.argv) < 3:
	sys.exit("Usage: genLibrary TokenDB.txt SingelView.svg")
    
print("Create svg library...")
	   
#start svg file
svgfile = open(sys.argv[2], "w")
svg = SvgWriter(svgfile)    
svg.begin()
svg.beginDefs()

#the function to write the definitions
def doit(token):
	
	#frontside
	writeTokenFront(svg, token)
	#backside
	writeTokenBack(svg, token)
	
	
	
	
	
	print("{0}-{1}-{2}-{3}".format(token.idno, token.directions, token.attack, token.defense))
	
	pass


tdb = TokenDB(sys.argv[1])
tdb.foreach(doit)
del tdb

#end svg file
svg.endDefs()
svg.end()

