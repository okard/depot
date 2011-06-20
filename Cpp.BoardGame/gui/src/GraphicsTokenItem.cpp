/*
The MIT License

Copyright (c) 2011 okard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "GraphicsTokenItem.hpp"

#include <QPainter>
#include <QMessageBox>

#include <Token.h>

/**
* Create new Graphics Token
*/
GraphicsTokenItem::GraphicsTokenItem()
    : dimension(.0f, .0f, 1.0f, 1.0f), token(0)
{
    
    //edges also
    
    //Create Circles
    for(int i=0; i< 7; i++)
    {
        circles[i] = new QGraphicsEllipseItem(this);
        circles[i]->setRect(0,0,radius,radius);
        
        //map events
    }
    
}

/**
* Destructor
*/  
GraphicsTokenItem::~GraphicsTokenItem()
{
}
    

/**
* Get Bounding Rect
*/
QRectF GraphicsTokenItem::boundingRect() const
{
    return dimension;
}

/**
* paint token
*/
void GraphicsTokenItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if(token == 0)
        return;
    
    Token::Side& side = drawTopSide ? token->getTopSide() : token->getBottomSide();
    
    //move to egde
    painter->translate(dimension.x(), dimension.y());
    
    //rotate when south direction?

    painter->setRenderHint(QPainter::Antialiasing);
    //the pen for all drawings?
    painter->setPen(QPen(Qt::black, 0.01, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
    
    
    //edge = 1/10 height?
    // the egde spacing
    float egde = dimension.height()/7.0f;
    
    QPointF points[5];
    points[0] = QPointF(dimension.width()/2, 0);  //top middle
    points[1] = QPointF(dimension.width()-egde, egde); //right top
    points[2] = QPointF(dimension.width(), dimension.height()); //bottom right
    points[3] = QPointF(0, dimension.height());  //bottom left
    points[4] = QPointF(egde, egde); //left top
    
    painter->setBrush(QBrush(QColor(237,237,200), Qt::SolidPattern));
    painter->drawPolygon(points, 5);
    
    //go to center, a little bit more on y axis
    painter->translate(dimension.width()/2, dimension.height()/2 + egde/2);
    

    // length of cross
    float length = dimension.height()/3.8f;
    
    //draw lines and outer circles
    for(int i=0; i < 4; i++)
    {
        painter->drawLine(QLineF(0, length, 0, -length));
        
        //set right brushes
        
        if(side.Dir[i] > Token::None)
        {
            //New Circles drwaing
            QPointF p(0,-length);
            //circles[i]->translate(p.rx(), p.ry());
            circles[i]->setPos(p);
            circles[i]->paint(painter,option,widget);
            
            painter->setBrush(QBrush(side.Dir[i] == Token::Move ? Qt::white : Qt::black, Qt::SolidPattern));
            painter->drawEllipse(QPointF(0,-length), radius, radius);
        }
        
        if(side.Dir[i+4] > Token::None)
        {
            painter->setBrush(QBrush(side.Dir[i+4] == Token::Move ? Qt::white : Qt::black, Qt::SolidPattern));
            painter->drawEllipse(QPointF(0,length), radius, radius);
        }
        
        painter->rotate(45.0f);
    } 
    
    //center circle 
    //set right brush
    switch(side.BaseValue)
    {
        case Token::Black:
            painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
            break;
        case Token::Green:
            painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
            break;
        case Token::Red:
            painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
            break;
        case Token::Blue:
            painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
            break;
        case Token::Gold:
            painter->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
            break;
    }
    painter->drawEllipse(QPointF(0,0), radius, radius);
}


/**
* Update Token Data
*/
void GraphicsTokenItem::update()
{
    //update token information
    
    QGraphicsItem::update();
}


/**
* Mouse Clock Event
*/ 
void GraphicsTokenItem::mousePressEvent (QGraphicsSceneMouseEvent* event)
{
    //QMessageBox::information(0, QString("Event"), QString("Clicked"));
    //when is Active mark field under item
    //fire selected event?
}


/**
* Set top side drawing
*/
void GraphicsTokenItem::setTopSide()
{
    drawTopSide = true;
}

/**
* Set bottom side drawing
*/
void GraphicsTokenItem::setBottomSide()
{
    drawTopSide = false;
}
    

/**
* Set Position
*/
void GraphicsTokenItem::setPosition(int x, int y)
{
    dimension.moveTo(x, y);
}


/** 
* Set the size of token
*/
void GraphicsTokenItem::setSize(int x, int y)
{
    dimension.setSize(QSizeF(x, y));
}

/** 
* set Token
*/
void GraphicsTokenItem::setToken(Token* token)
{
    //TODO Update Circles
    this->token = token;
}

/**
* Get token
*/
Token* GraphicsTokenItem::getToken()
{
    return this->token;
}

