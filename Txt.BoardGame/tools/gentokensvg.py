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
        
    def beginFormat(self, width, height):
        self.file.write("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n")
        self.file.write("<svg xmlns=\"http://www.w3.org/2000/svg\" ")
        self.file.write("xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:ev=\"http://www.w3.org/2001/xml-events\" ");
        self.file.write('width="{0}" height="{1}" viewBox="0 0 210 297" '.format(width, height))
        self.file.write("version=\"1.1\" baseProfile=\"full\">\n")
        
    def end(self) : self.file.write('</svg>\n')
    
    def beginDefs(self) : self.file.write('<defs>\n')
    
    def endDefs(self) : self.file.write('</defs>\n')
    
    def beginSymbol(self, id) : self.file.write('<symbol id="{}">\n'.format(id))
    
    def endSymbol(self) : self.file.write('</symbol>\n')
    
    def beginGroup(self, attr) : self.file.write('<g {} >\n'.format(attr))
    
    def endGroup(self) : self.file.write('</g>\n')

    def drawPolygon(self, points) : self.file.write('<polygon points="{0}" fill="{1}" stroke="{2}" stroke-width="{3}" />\n'.format(', '.join(map(str,points)), self.fill_color, self.stroke_color, self.stroke_width))

    #draw line
    def drawLine(self, x1, y1, x2, y2, transform = None):
        if transform == None:
            transform = ''
        else:
            transform = 'transform="{0}"'.format(transform)
        self.file.write('<line x1="{0}" y1="{1}" x2="{2}" y2="{3}" fill="{4}" stroke="{5}" stroke-width="{6}" {7} />\n'.format(x1, y1, x2, y2, self.fill_color, self.stroke_color, self.stroke_width, transform))     

    #draw circle
    def drawCircle(self, x, y, r, transform = None):
        if transform == None:
            transform = ''
        else:
            transform = 'transform="{0}"'.format(transform)
        self.file.write('<circle cx="{0}" cy="{1}" r="{2}" fill="{3}" stroke="{4}" stroke-width="{5}" {6} />\n'.format(x, y, r, self.fill_color, self.stroke_color, self.stroke_width, transform))

    #draw rect
    def drawRect(self, x, y, width, height, transform = None):
        if transform == None:
            transform = ''
        else:
            transform = 'transform="{0}"'.format(transform)
        self.file.write('<rect x="{0}" y="{1}" width="{2}" height="{3}" fill="{4}" stroke="{5}" stroke-width="{6}" {7}/>'.format(x, y, width, height, self.fill_color, self.stroke_color, self.stroke_width, transform))
        
    #set stroke
    def setStroke(self, color, width):
        self.stroke_color = color
        self.stroke_width = width

    #set fill
    def setFill(self, color):
        self.fill_color = color
        
#############################################################################
# check Token
############################################################################# 
def isValidToken(token):
    if(re.match('[0-2]{8}[0-5]', token) == None):
        print ('Invalid token: {0}\n'.format(token))
        return False
    else:
        return True
    
def getValueColor(value):
    if value == '1': return "black"
    elif value == '2': return "green"
    elif value == '3': return "red"
    elif value == '4': return "blue"
    elif value == '5': return "#ffd700"
    else: return "white"

#############################################################################
# Write Token
#############################################################################
def writeToken(svg, token, back_value=None):
    
    if not isValidToken(token):
        return;
        
    svg.beginSymbol(token)
    
    
    #calculate
    rect = { 'width': 20, 'height': 25 }
    center = { 'x': rect['width']/2, 'y' : 13.5 }
    egde = 2.5
    line = 5.0
    radius = 1.5
    
    #outer frame
    #svg.setFill("#EEE8AA")
    svg.setFill("white")
    svg.setStroke("black", "1")
    poly = []
    poly.append(rect['width']/2); poly.append(0)
    poly.append(rect['width']-egde); poly.append(egde)
    poly.append(rect['width']); poly.append(rect['height'])
    poly.append(0); poly.append(rect['height'])
    poly.append(egde); poly.append(egde)
    
    #[rect['width']/2 ,0, 29, 10, 34, 40, 0, 40, 4, 10]
    svg.drawPolygon(poly)
    
    #on front side draw upgrade info for backside
    if not back_value == None:
        radius_i = radius*1.5
        svg.setStroke("#8D8D8D", "0.3")
        svg.setFill(getValueColor(back_value))
        svg.drawRect(rect['width']/2-radius_i, rect['height']-radius_i-0.5, radius_i*2, radius_i*0.70)
        #svg.drawCircle(rect['width']-radius-1.5, rect['height']-radius-1, radius, None)
        
    #inner cross
    svg.setStroke("black", "0.5")
    for i in range(0, 4):
        rot = i*45
        svg.drawLine(center['x'], center['y']-line, center['x'] ,center['y']+line, "rotate({0} {1} {2})".format(rot, center['x'], center['y']))
        
    # inner circle
    valuecolor = getValueColor(token[8])
    svg.setFill(valuecolor)
    svg.drawCircle(center['x'], center['y'], radius, None)
    
    #inner round of circles
    svg.setStroke("black", "0.5")
    for i in range(0, 8):
        if token[i] == '0': continue

        if token[i] == '1':
            svg.setFill("white")
        else:
            svg.setFill("black")
            
        rot = i*45
        svg.drawCircle(center['x'], center['y']-line, radius, "rotate({0} {1} {2})".format(rot, center['x'], center['y']))
    
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
        
if len(sys.argv) < 2:
    sys.exit("Usage: script lib/ov")     

# generate svg library
if sys.argv[1] == 'lib':
    
    if len(sys.argv) < 4:
        sys.exit("Usage: script lib SourceFile OutFile")
    
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
        
        if not isValidToken(values[0]):
            continue
        
        if not isValidToken(values[1]):
            continue
        
        #save token look for double fronts
        if values[0] in toklist:
            print("The frontside token {0} occurs twice".format(values[0]))
            continue
        
        if values[1] in toklist:
            print("The backside token {0} occurs in frontside list".format(values[1]))
            continue
        
        toklist.add(values[0])
        #frontside
        writeToken(svg, values[0], values[1][8])
        #backside
        writeToken(svg, values[1])
        
        print("{0}-{1}".format(values[0], values[1]))
        
    #end svg file
    svg.endDefs()
    svg.end()

    deffile.close()
    
# generate an overview from list
# for print out and so on
if sys.argv[1] == 'ov':
    
    if len(sys.argv) < 5:
        sys.exit("Usage: script ov deffile libfile outfile")   
    
    print("Create overview...")
    
    deffile = open(sys.argv[2], "r")
    
    libfile = sys.argv[3]
    
    #start svg file
    outfile = open(sys.argv[4], "w")
    svg = SvgWriter(outfile) 
    svg.beginFormat('210mm', '297mm')
    
    x_pos = 1.5
    y_pos = 1.5
   
    # calculate next position
    def next():
        step_x = 8
        step_y = 8
        global x_pos
        global y_pos
        x_pos += step_x
        if(x_pos >= 50):
            x_pos = 1.5
            y_pos += step_y
        
    # add a instance for each token pair in token db list
    for line in deffile:
        line = line.strip()
        if(line[:1] == '#'): continue
        if(len(line) == 0): continue
        
        values = line.split(';')

        print("{0}-{1}".format(values[0], values[1]))
        
        for i in range(0, 3):
            svg.file.write('<use xlink:href="{0}#{1}" x="{2}mm" y="{3}mm" width="22mm" height="26mm" />\n'.format(libfile, values[0], x_pos, y_pos))
            next()
        
            svg.file.write('<use xlink:href="{0}#{1}" x="{2}mm" y="{3}mm" width="22mm" height="27mm" />\n'.format(libfile, values[1], x_pos, y_pos))
            next()
           
    #end svg file
    svg.end()

    deffile.close()

    
