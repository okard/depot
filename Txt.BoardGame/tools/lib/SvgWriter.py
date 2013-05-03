
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
  
