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

#include "TokenWidget.moc"


/**
* Create a new Token Widget
*/
TokenWidget::TokenWidget(QWidget* parent)
    : QWidget(parent), token(0)
{
    setupUi(this);
    
    //Connect clicked events
    connect(optTopSide, SIGNAL(toggled(bool)), this, SLOT(sideChanged()));
    connect(optBottomSide, SIGNAL(toggled(bool)), this, SLOT(sideChanged()));
    connect(btnActionN, SIGNAL(clicked()), this, SLOT(changeActionN()));
    connect(btnActionNE, SIGNAL(clicked()), this, SLOT(changeActionNE()));
    connect(btnActionE, SIGNAL(clicked()), this, SLOT(changeActionE()));
    connect(btnActionSE, SIGNAL(clicked()), this, SLOT(changeActionSE()));
    connect(btnActionS, SIGNAL(clicked()), this, SLOT(changeActionS()));
    connect(btnActionSW, SIGNAL(clicked()), this, SLOT(changeActionSW()));
    connect(btnActionW, SIGNAL(clicked()), this, SLOT(changeActionW()));
    connect(btnActionNW, SIGNAL(clicked()), this, SLOT(changeActionNW()));
    connect(btnBaseValue, SIGNAL(clicked()), this, SLOT(changeBaseValue()));
    
    front.setTopSide();
    back.setBottomSide();
    
    
    scene.addItem(&front);
    scene.addItem(&back);
    
    back.setPosition(1, 0);
        
    graphicsView->setScene(&scene);
    graphicsView->setSceneRect(QRectF(0.0f,0.0f, 2.0f, 1.0f));

    float scaleY = graphicsView->geometry().height()*2.0f;
    float scaleX = graphicsView->geometry().width()*2.0f;
    
    graphicsView->scale(scaleX, scaleX);
}

/**
* Destructor
*/
TokenWidget::~TokenWidget()
{
}

/**
* set the token
*/
void TokenWidget::setToken(Token* token)
{
    this->token = token;
    front.setToken(token);
    back.setToken(token);
}

/**
* Sync Token Settings with Gui Elements
*/
void TokenWidget::update()
{
    if(token == 0)
        return;
    
    Token::Side& side = optTopSide->isChecked() ? token->getTopSide() : token->getBottomSide();
    
    btnBaseValue->setText(QString::number(side.BaseValue));
    btnActionN->setText(side.Dir[Token::N] == Token::None ? "N" : side.Dir[Token::N] == Token::Move ? "M" : "A");
    btnActionNE->setText(side.Dir[Token::NE] == Token::None ? "N" : side.Dir[Token::NE] == Token::Move ? "M" : "A");
    btnActionE->setText(side.Dir[Token::E] == Token::None ? "N" : side.Dir[Token::E] == Token::Move ? "M" : "A");
    btnActionSE->setText(side.Dir[Token::SE] == Token::None ? "N" : side.Dir[Token::SE] == Token::Move ? "M" : "A");
    btnActionS->setText(side.Dir[Token::S] == Token::None ? "N" : side.Dir[Token::S] == Token::Move ? "M" : "A");
    btnActionSW->setText(side.Dir[Token::SW] == Token::None ? "N" : side.Dir[Token::SW] == Token::Move ? "M" : "A");
    btnActionW->setText(side.Dir[Token::W] == Token::None ? "N" : side.Dir[Token::W] == Token::Move ? "M" : "A");
    btnActionNW->setText(side.Dir[Token::NW] == Token::None ? "N" : side.Dir[Token::NW] == Token::Move ? "M" : "A");
    
    front.update();
    back.update();
    
    QString txt("Points: ");
    txt.append(QString::number(token->getValue()));
    lblPoints->setText(txt);
}

/**
* Event Switch between bottom and top side
*/
void TokenWidget::sideChanged()
{
    update();
}

/**
* Event for Edit a Direction if Token
*/
void TokenWidget::changeAction(QPushButton* button, Token::Direction dir)
{
    if(token == 0)
        return;
    
    Token::Side& side = optTopSide->isChecked() ? token->getTopSide() : token->getBottomSide();
    
    //Switch between None, Move and Attack
    if(button->text() == "N")
    {
        button->setText("M");
        side.Dir[dir] = Token::Move;
    }
    else if(button->text() == "M")
    {
        button->setText("A");
        side.Dir[dir] = Token::Attack;
    }
    else if(button->text() == "A")
    {
        button->setText("N");
        side.Dir[dir] = Token::None;
    }
    
    update();
}

void TokenWidget::changeActionN()
{
    changeAction(btnActionN, Token::N);
}

void TokenWidget::changeActionNE()
{
    changeAction(btnActionNE, Token::NE);
}

void TokenWidget::changeActionE()
{
    changeAction(btnActionE, Token::E);
}

void TokenWidget::changeActionSE()
{
    changeAction(btnActionSE, Token::SE);
}

void TokenWidget::changeActionS()
{
    changeAction(btnActionS, Token::S);
}

void TokenWidget::changeActionSW()
{
    changeAction(btnActionSW, Token::SW);
}

void TokenWidget::changeActionW()
{
    changeAction(btnActionW, Token::W);
}

void TokenWidget::changeActionNW()
{
    changeAction(btnActionNW, Token::NW);
}

/**
* Event Change the base value
*/
void TokenWidget::changeBaseValue()
{
    Token::Side& side = optTopSide->isChecked() ? token->getTopSide() : token->getBottomSide();
    
    int value = btnBaseValue->text().toInt();
    value++;
    if(value > Token::Gold)
        value = Token::Black;

    side.BaseValue = static_cast<Token::Base>(value);
    btnBaseValue->setText(QString::number(value));
    
    update();
}
