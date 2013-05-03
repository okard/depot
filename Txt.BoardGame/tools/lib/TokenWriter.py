


#############################################################################
# Write Token Front!
#############################################################################
def writeTokenFront(svg, token):
    
    if not token.valid():
        return;
        
    svg.beginSymbol(token.idno+'f')
    
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
    
    # token defense
    vrect_size = radius*0.80
    svg.setStroke("#7e7e7e", "0.3")
    svg.setFill("#7e7e7e")

    for i in range(0, int(token.defense)):
        svg.drawRect((rect['width']-2)-((2.5 * i)+vrect_size),  rect['height']-3, vrect_size, vrect_size)
        
    # token attack
    svg.setStroke("black", "0.3")
    svg.setFill("black")
    for i in range(0, int(token.attack)):
        svg.drawRect(2+(2.5 * i),  rect['height']-3, vrect_size, vrect_size)
    
    #inner cross
    svg.setStroke("black", "0.5")
    for i in range(0, 4):
        rot = i*45
        svg.drawLine(center['x'], center['y']-line, center['x'] ,center['y']+line, "rotate({0} {1} {2})".format(rot, center['x'], center['y']))
        
    
    #inner round of circles
    svg.setStroke("black", "0.5")
    for i in range(0, 8):
        if token.directions[i] == '0': continue

        if token.directions[i] == '1':
            svg.setFill("white")
        else:
            svg.setFill("black")
            
        rot = i*45
        svg.drawCircle(center['x'], center['y']-line, radius, "rotate({0} {1} {2})".format(rot, center['x'], center['y']))
    
    svg.endSymbol()
    
#############################################################################
# Write Token Back!
#############################################################################
def writeTokenBack(svg, token):

    if not token.valid():
        return;
        
    svg.beginSymbol(token.idno+'b')
    
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
    
    svg.drawPolygon(poly)
    
    #draw circle
    
    svg.setStroke("black", "0.5")
    svg.drawCircle(center['x'], center['y'], 6)
    
    #draw values tok.calcValue(), Lvl win points, id
    svg.setFill("black");
    svg.setStroke("black", "0");
    svg.drawText(2.5, rect['height']-2, token.idno);
    svg.drawText(rect['width']-5.5, rect['height']-2, token.calcValue())
        
    svg.endSymbol()
    
