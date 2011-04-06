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
#ifndef __TOKENWIDGET_HPP__
#define __TOKENWIDGET_HPP__

#include <QWidget>

#include "ui_TokenWidget.h"

#include <Token.h>
#include "GraphicsTokenItem.hpp"

/**
* The Token Widget
*/
class TokenWidget : public QWidget,  protected Ui::TokenWidget
{
    Q_OBJECT
    
private:
    
    //Change to reference?
    /// The edited token
    Token* token;
    
    /// the front of token
    GraphicsTokenItem front;
    
    /// the back of token
    GraphicsTokenItem back;
    
    /// Scene
    QGraphicsScene scene;
    
public:
    /// Create a new TokenWidget
    TokenWidget(QWidget* parent = 0);
    
    /// Destructor 
    virtual ~TokenWidget();
    
    /// set token
    void setToken(Token* token);
    
    /// show
    void update();

public slots:
    void sideChanged();
    
    void changeAction(QPushButton* button, Token::Direction dir);
    void changeActionN();
    void changeActionNE();
    void changeActionE();
    void changeActionSE();
    void changeActionS();
    void changeActionSW();
    void changeActionW();
    void changeActionNW();
    
    void changeBaseValue();

};


#endif // __TOKENWIDGET_HPP__
