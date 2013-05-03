#!/usr/bin/env python3

import sys
import re

from lib.SvgWriter import SvgWriter
from lib.Token import TokenDB, Token
from lib.TokenWriter import writeTokenFront, writeTokenBack


########################################################################################################
# generate an overview from list
# for print out and so on

class OverviewContext():
    outfile = None
    svg =  None
    x_pos = 1.5
    y_pos = 1.5
    rows = 0
    cols = 0
    count = 0
    
    def __init__(self, fileName):
        self.outfile = open(fileName, "w")
        self.svg = SvgWriter(self.outfile) 
        self.svg.beginFormat('210mm', '297mm')
        
    def __del__(self):
        self.svg.end()
        self.outfile.close()
        
    def next(self):
        # width= 22mm height=27mm
        # calculate the possible elements per column and row for din a4 paper
        # 10 rows 7 columns currently doesn't make sense
        self.count += 1
        step_x = 8
        step_y = 8
        self.x_pos += step_x
        self.cols += 1
        if(self.x_pos >= 50):
            self.cols = 0
            self.rows += 1
            self.x_pos = 1.5
            self.y_pos += step_y
    
    def write(self, libfile, value):
        self.svg.file.write('<use xlink:href="{0}#{1}" x="{2}mm" y="{3}mm" width="22mm" height="27mm" />\n'.format(libfile, value, self.x_pos, self.y_pos))
        self.next()
        
    # possible elements left
    def space_left(self):
        return (10*7)- self.count
        
    
if len(sys.argv) < 4:
	sys.exit("Usage: script deffile libfile outfile")   
	
arg_deffilename = sys.argv[1]
arg_libfilename = sys.argv[2]
arg_overviewtpl = sys.argv[3]
	
#check if sys.argv[4] has an index placeholder {0} element
if not "{0}" in arg_overviewtpl:
	sys.exit("Outfile required a index place holder '{0}' in name")

print("Create overview...")

# the token db file
deffile = open(arg_deffilename, "r")
# required for referencing
libfile = arg_libfilename

# overview{0}.svg
overviewIndex = 0
overviewFile = OverviewContext(arg_overviewtpl.format(overviewIndex))

#TODO: create multiple page files

def next_file():
	print("Creating new Overview File...")
	global overviewIndex
	global overviewFile
	overviewIndex += 1
	del overviewFile
	overviewFile = OverviewContext(arg_overviewtpl.format(overviewIndex))
	
	
# add a instance for each token pair in token db list
for line in deffile:
	line = line.strip()
	if(line[:1] == '#'): continue
	if(len(line) == 0): continue
	
	values = line.split(';')
	
	frontid = values[3]+'f'
	backid = values[3]+'b'
	
	# this creates 6 entries
	for i in range(0, 3):  
		if overviewFile.space_left() < 2:
			next_file()
		
		print("{0}-{1}".format(frontid, backid))
		overviewFile.write(libfile, frontid)
		overviewFile.write(libfile, backid)

del overviewFile

deffile.close()

