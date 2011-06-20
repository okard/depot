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
#include "BoardScene.moc"

#include <QMessageBox>

#include "GraphicsTokenItem.hpp"


///setup scene for game //create fields and so on
void BoardScene::setup(Game* game)
{
    //Create Fields?
    //game->getBoard()->
    unsigned int boardSize = game->getBoard()->getSize();
    
    //create fields
    //draw only from 0 1 ???
    
    //scale scene?
    
    //Backgrould color for fields
    QBrush background(QColor(246,246,164), Qt::SolidPattern);
    
    // Create Board
    for(int x=0; x < boardSize; x++)
    {
        for(int y=0; y < boardSize; y++)
        {
            QGraphicsRectItem* item = addRect(QRectF(x, y, 1, 1), QPen(), background);
            //connect item fieldSelected event
            //connect(item, SIGNAL(clicked()), this, SLOT(fieldSelected()));
            fields.append(item);
        }
    }
    
    //create GraphicsTokenItem for each players army
    //tokens should no token.isActive
    //so draw for each player the the army
    
    
    //testgraphic token
    GraphicsTokenItem* item = new GraphicsTokenItem();
    item->setToken(new Token());
    item->setPosition(0,0);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    addItem(item);   
}



/**
* Field got selected
*/
void BoardScene::fieldSelected()
{
    //set brush for field
    QMessageBox::information(0, QString("Event"), QString("Clicked"));
}