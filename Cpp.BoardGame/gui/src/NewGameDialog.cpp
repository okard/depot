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
#include "NewGameDialog.moc"

#include "GuiPlayer.hpp"


/**
* Creates a new Main Window
*/
NewGameDialog::NewGameDialog(MainWindow& parent)
    : QDialog(&parent), mainWindow(parent)
{
    setupUi(this);
    
    //Connect events
    connect(btnLocalGame, SIGNAL(clicked()), this, SLOT(startLocalGame()));
    connect(btnConnect, SIGNAL(clicked()), this, SLOT(connectToGame()));
    connect(btnHost, SIGNAL(clicked()), this, SLOT(hostGame()));
    connect(btnStartAIGame, SIGNAL(clicked()), this, SLOT(startAIGame()));
}

/**
* Destructs Main Window
*/
NewGameDialog::~NewGameDialog()
{
    
}


/**
* Start a new local game
*/
void NewGameDialog::startLocalGame()
{
    Game& g = mainWindow.getGame();
    
    // TODO Memory Leak
    
    g.setBoard(new Board(spinBoardSize->value()));
    
    // setup player assign with mainwindow?
    // for picking dialog
    
    // army size
    
    g.setPlayerA(new GuiPlayer());
    g.setPlayerB(new GuiPlayer());
    
    //start game at main window
    mainWindow.startGame();
    
    this->close();
}

/**
* Start a new AI Game
*/
void NewGameDialog::startAIGame()
{
     Game& g = mainWindow.getGame();
     
     //prepare game for ai play
     
     this->close();
}

/**
* Host a new Network Game
*/
void NewGameDialog::hostGame()
{
     Game& g = mainWindow.getGame();
     
     //prepare game for network play
     
     //start listening for connect
     //if connect happens configure players and let game begin
     
     
     this->close();
}

/**
* Connect to a new network game
*/
void NewGameDialog::connectToGame()
{
    Game& g = mainWindow.getGame();
    
    //connect to a listening game host
    
    //if connect succesful start game
    
    this->close();
}