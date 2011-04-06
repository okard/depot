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

#include "MainWindow.moc"

#include "NewGameDialog.hpp"
#include "GraphicsTokenItem.hpp"
#include "TokenWidget.hpp"

/**
* Main Window Constructor
*/
MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
{
    //setup ui
    setupUi(this);
    showMaximized();
    
    // Connect Signals and Slots
    connect(actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    
    //TODO Calulcate right scale for scene
    
    //TODO Set Scene Rect for baord and sideboard view
    
    boardView->setScene(&scene);
    
    sideboardView->setScene(&scene);
    sideboardView->setSceneRect(QRectF(0.0f, 0.0f, 60.0f, 60.0f));
    sideboardView->update();
    
        
    // new game dialog
    ngd = new NewGameDialog(*this);
}

/**
* Destructor
*/
MainWindow::~MainWindow()
{
    delete ngd;
}

/**
* Start Game
*/ 
void MainWindow::startGame()
{
    game.start();
    
    //show pick window?
    
    QDialog* dia = new QDialog(this);
    dia->setModal(true);
    
    TokenWidget* wid = new TokenWidget(dia);
    wid->setToken(new Token());
    
    dia->show();
    
    //which players turn
    
    //set up board scene for game
    scene.setup(&game);
    
    
    //reset
    boardView->resetTransform();
    sideboardView->resetTransform();
    
    float size = static_cast<float>(game.getBoard()->getSize());
    boardView->setSceneRect(QRectF(.0f, .0f, size, size));
   

    //calulate right scale faktor
    //boardView->geometry();
    float scale = boardView->geometry().height()/size;
    boardView->scale(scale, scale);
    
    //sideboard scene rect width = count of tokens for player ?
    sideboardView->setSceneRect(QRectF(0.0f, 0.0f, game.getPlayerA()->tokenCount(), 1.0f));
    float scaleSide = boardView->geometry().height()/10.0f-1.0f;
    sideboardView->scale(scaleSide, scaleSide);
}

/**
* Acces to Game
*/
Game& MainWindow::getGame()
{
    return game;
}

/// Start a new game
void MainWindow::newGame()
{
    // NewGameDialog prepares the Game Class
    // After that picking phase began
    // then the set phase
    // then game begins
    ngd->setModal(true);
    ngd->show();
}