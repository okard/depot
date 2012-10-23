#!/usr/bin/env python3

import sys
import re

# Svg Library
class SvgWriter:
    """SVG Writer Class to create SVG Files"""
    
    # track internal state
    # openTag: 'defs' 'symbol' 'svg' 'initial' 'end'
    tabs = 0
    stroke_color = "black"
    stroke_width = "1px"
    fill_color = "white"
    ident = 0
    
    
    def __init__(self, ostream):
        
        # open file if string
        # else IOBase
        # or exception
        
        # isinstance(ostream, io.IOBase)
        # open(fileName, "w")
        self.file = ostream
   
        
    def begin(self):
        self.file.write("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n")
        self.file.write("<svg xmlns=\"http://www.w3.org/2000/svg\" ")
        self.file.write("xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:ev=\"http://www.w3.org/2001/xml-events\" ");
        self.file.write("version=\"1.1\" baseProfile=\"full\">\n")
        
    def beginFormat(self, width, height):
        #todo fix viewbox
        # dict as param { unit:"" }
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
        

# TokenDB
class TokenDB:
    
    def __init__(self, fileName):
        self.file = open(fileName, "r")
    
    def __del__(self):
        self.file.close()
    
    def foreach(self, func):
        #svg.file.seek(0)
        for line in self.file:
            line = line.strip()
            if(line[:1] == '#'): continue
            if(len(line) == 0): continue
            values = line.split(';')
            #valid step?
            if not isValidToken(values[0]):
                raise Exception("Invalid Front Side")
            if not isValidToken(values[1]):
                raise Exception("Invalid Back Side")
            # values.
            func(values[0], values[1])
        
        
#############################################################################
# check Token
############################################################################# 
def isValidToken(token):
    if(re.match('[0-2]{8}[0-3X]', token) == None):
        print ('Invalid token: {0}\n'.format(token))
        return False
    else:
        return True
        
# Calulcate Token Value
def calcTokenValue(front, back):
    v = { "1":1, "2":3, "3":5}
    sum = 0
    for i, c in enumerate(front):
        if i == 8:
            sum += v[c]
        else:
            sum += int(c)
    for i, c in enumerate(back):
         if i == 8:
            sum += v[c]
         else:
            sum += int(c)
    return sum

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
    
    # strength of back side
    # TODO light gray filled?
    vrect_size = radius*0.80
    svg.setStroke("#7e7e7e", "0.3")
    svg.setFill("#7e7e7e")
    if not back_value == None:
        bstrength = int(3 if back_value == 'X' else back_value)
        for i in range(0, bstrength):
            svg.drawRect((rect['width']-2)-((2.5 * i)+vrect_size),  rect['height']-3, vrect_size, vrect_size)
        
    # strength front side
    svg.setStroke("black", "0.3")
    svg.setFill("black")
    fstrength = int(3 if token[8] == 'X' else token[8])
    for i in range(0, fstrength):
        svg.drawRect(2+(2.5 * i),  rect['height']-3, vrect_size, vrect_size)
    
    
    #inner cross
    svg.setStroke("black", "0.5")
    for i in range(0, 4):
        rot = i*45
        svg.drawLine(center['x'], center['y']-line, center['x'] ,center['y']+line, "rotate({0} {1} {2})".format(rot, center['x'], center['y']))
        
    
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
# Main Program 
#############################################################################

# command lib - create lib
# command ov - create overview sheet
# command sv - single view
# command com - command mode

        
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
        
        print("{0}-{1}-{2}".format(values[0], values[1], calcTokenValue(values[0], values[1])))
        
    #end svg file
    svg.endDefs()
    svg.end()

    deffile.close()
    
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
        
    
    

if sys.argv[1] == 'ov':
    
    if len(sys.argv) < 5:
        sys.exit("Usage: script ov deffile libfile outfile")   
        
    #check if sys.argv[4] has an index placeholder {0} element
    if not "{0}" in sys.argv[4]:
        sys.exit("Outfile required a index place holder '{0}' in name")
    
    print("Create overview...")
    
    # the token db file
    deffile = open(sys.argv[2], "r")
    # required for referencing
    libfile = sys.argv[3]
    
    # overview{0}.svg
    overviewIndex = 0
    overviewFile = OverviewContext(sys.argv[4].format(overviewIndex))
    
    #TODO: create multiple page files
    
    def next_file():
        print("Creating new Overview File...")
        global overviewIndex
        global overviewFile
        overviewIndex += 1
        del overviewFile
        overviewFile = OverviewContext(sys.argv[4].format(overviewIndex))
        
        
    # add a instance for each token pair in token db list
    for line in deffile:
        line = line.strip()
        if(line[:1] == '#'): continue
        if(len(line) == 0): continue
        
        values = line.split(';')
 
        # this creates 6 entries
        for i in range(0, 3):  
            if overviewFile.space_left() < 2:
                next_file()
            
            print("{0}-{1}".format(values[0], values[1]))
            overviewFile.write(libfile, values[0])
            overviewFile.write(libfile, values[1])
    
    del overviewFile
    
    deffile.close()


# command mode

if sys.argv[1] == 'com':
    
    if len(sys.argv) < 4:
        sys.exit("Usage: script com CommandFile TokenLib.svg")
   
    
# single view 

if sys.argv[1] == 'sv':
    
    if len(sys.argv) < 4:
        sys.exit("Usage: script sv TokenDB.txt OutputTemplate")
        
    def doit(front, back):
        print("{0}-{1}".format(front,back))
        # each token one svg file
        # create name "generated/token_{0}_{1}_{2}.svg"
        # calcTokenValue(front, back)
        fileName = sys.argv[3].format(calcTokenValue(front, back), front, back)
        svgfile = open(fileName, "w")
        svg = SvgWriter(svgfile)    
        svg.begin()
        
        # write symbols
        svg.beginDefs()
        writeToken(svg, front, back[8])
        writeToken(svg, back)
        svg.endDefs()
        
        # write drawings
        svg.file.write('<use xlink:href="#{0}" x="{1}mm" y="{2}mm" width="22mm" height="27mm" />\n'.format(front, 0, 0))
        svg.file.write('<use xlink:href="#{0}" x="{1}mm" y="{2}mm" width="22mm" height="27mm" />\n'.format(back, "7", 0))
        
        svg.end()
        svgfile.close()
        pass
        
    tdb = TokenDB(sys.argv[2])
    tdb.foreach(doit)
    del tdb
       
    
# Create single images for each token? or double images with front and backside?
# Create also latex db template

    
