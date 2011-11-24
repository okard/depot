#!/usr/bin/env python3

import sys
import re

# Svg Library
class SvgWriter:
    def __init__(self, file):
        self.file = file
        self.tabs = 0
        self.stroke_color = "black"
        self.stroke_width = "1px"
        self.fill_color = "white"
        self.ident = 0
        
    def begin(self):
        self.file.write("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n")
        self.file.write("<svg xmlns=\"http://www.w3.org/2000/svg\" ")
        self.file.write("xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:ev=\"http://www.w3.org/2001/xml-events\" ");
        self.file.write("version=\"1.1\" baseProfile=\"full\">\n")
        
    def end(self) : self.file.write('</svg>\n')
    
    def beginDefs(self) : self.file.write('<defs>\n')
    
    def endDefs(self) : self.file.write('</defs>\n')
    
    def beginSymbol(self, id) : self.file.write('<symbol id="{}">\n'.format(id))
    
    def endSymbol(self) : self.file.write('</symbol>\n')
    
    def beginGroup(self, attr) : self.file.write('<g {} >\n'.format(attr))
    
    def endGroup(self) : self.file.write('</g>\n')

    def drawPolygon(self, points) : self.file.write('<polygon points="{0}" fill="{1}" stroke="{2}" stroke-width="{3}" />\n'.format(', '.join(map(str,points)), self.fill_color, self.stroke_color, self.stroke_width))

    def drawLine(self, x1, y1, x2, y2, transform):
        if transform == None:
            transform = ''
        else:
            transform = 'transform="{0}"'.format(transform)
        self.file.write('<line x1="{0}" y1="{1}" x2="{2}" y2="{3}" fill="{4}" stroke="{5}" stroke-width="{6}" {7} />\n'.format(x1, y1, x2, y2, self.fill_color, self.stroke_color, self.stroke_width, transform))     

    def drawCircle(self, x, y, r, transform):
        if transform == None:
            transform = ''
        else:
            transform = 'transform="{0}"'.format(transform)
        self.file.write('<circle cx="{0}" cy="{1}" r="{2}" fill="{3}" stroke="{4}" stroke-width="{5}" {6} />\n'.format(x, y, r, self.fill_color, self.stroke_color, self.stroke_width, transform))

    #set stroke
    def setStroke(self, color, width):
        self.stroke_color = color
        self.stroke_width = width

    #set fill
    def setFill(self, color):
        self.fill_color = color

#############################################################################
# Write Token
#############################################################################
def writeToken(svg, token):
    
    if(re.match('[0-2]{8}[0-5]', token) == None):
        print ('Invalid token: {0}\n'.format(token))
        return 
        
    svg.beginSymbol(token)
    
    #define sqare calculate token
    center = { 'x': 15, 'y' : 22.5 }
    
    #outer frame
    svg.setFill("#EEE8AA")
    svg.setStroke("black", "1px")
    svg.drawPolygon([17 ,0, 29, 10, 34, 40, 0, 40, 4, 10])
        
    #inner cross
    svg.setStroke("black", "0.5")
    for i in range(0, 4):
        rot = i*45
        svg.drawLine(15, 15, 15 ,30, "rotate({0} 15 22.5)".format(rot))
        
    # inner circle
    valuecolor = "white"
    if token[8] == '1': valuecolor = "black"
    elif token[8] == '2': valuecolor = "green"
    elif token[8] == '3': valuecolor = "red"
    elif token[8] == '4': valuecolor = "blue"
    elif token[8] == '5': valuecolor = "#ffd700"
    
    svg.setFill(valuecolor)
    svg.drawCircle("15", "22.5", "2", None)
    
    #inner round of circles
    svg.setStroke("black", "0.5")
    for i in range(0, 8):
        if token[i] == '0': continue

        if token[i] == '1':
            svg.setFill("white")
        else:
            svg.setFill("black")
            
        rot = i*45
        svg.drawCircle("15", "15", "2", "rotate({0} 15 22.5)".format(rot))
    
    svg.endSymbol()
    
#############################################################################
# printToken
#############################################################################
def printToken(svg, tokA, tokB):
    print("")

#############################################################################
# Main Program 
#############################################################################

# command lib - create lib
# command ov - create overview sheet
        
if len(sys.argv) < 4:
    sys.exit("Usage: script lib/ov SourceFile OutFile")    
    
if sys.argv[1] == 'lib':
    print("Create lib...")
           
    deffile = open(sys.argv[2], "r")
    
    #start svg file
    svgfile = open(sys.argv[3], "w")
    svg = SvgWriter(svgfile)    
    svg.begin()
    svg.beginDefs()
    
    toklist = set()

    for line in deffile:
        line = line.strip()
        if(line[:1] == '#'): continue
        if(len(line) == 0): continue
        
        values = line.split(';')
        
        #save token look for double fronts
        if values[0] in toklist:
            print("The first value {0} occurs twice".format(values[0]))
            continue
        
        toklist.add(values[0])
        writeToken(svg, values[0])
        writeToken(svg, values[1])
        
        print("{0}-{1}".format(values[0], values[1]))
        
    #end svg file
    svg.endDefs()
    svg.end()

    deffile.close()
    
    
if sys.argv[1] == 'ov':
    print("Create overview...")
    
    deffile = open(sys.argv[2], "r")
    
    #start svg file
    svgfile = open(sys.argv[3], "w")
    svg = SvgWriter(svgfile)    

    for line in deffile:
        line = line.strip()
        if(line[:1] == '#'): continue
        if(len(line) == 0): continue
        
        values = line.split(';')

        print("{0}-{1}".format(values[0], values[1]))
        
    #end svg file
    svg.end()

    deffile.close()

    
