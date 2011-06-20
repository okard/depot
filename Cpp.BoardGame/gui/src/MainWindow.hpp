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
#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <QMainWindow> 
#include <QGraphicsScene>

#include "ui_MainWindow.h"

#include <Game.h>
#include "BoardScene.hpp"
#include "GuiPlayer.hpp"

//Forward Declaration
class NewGameDialog;

/**
* Editor Main Window 
*/
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
    
private:
    /// Game Class
    Game game;
    
    /// Player A
    GuiPlayer playerA;
    
    // Player B
    //GuiPlayer, Network Player, KI Player
    
    /// Board Scene
    BoardScene scene;
    
    /// The Game Mode (to Game class?)
    enum GameMode
    {
        LocalGame,
        NetworkGame,
        AIGame
    };
    
    /// Selected game mode
    GameMode mode;
    
    /// New Game Dialog
    NewGameDialog* ngd;
    
public:
    /**
    * Creates a new Main Window
    */
    MainWindow(QWidget *parent = 0);
    
    /**
    * Destructs Main Window
    */
    virtual ~MainWindow();
    
    /**
    * Access to Game
    */
    Game& getGame();
    
    /**
    * Start Game
    */ 
    void startGame();
    
    /**
    * start a specific phase
    */
    void start(Game::Phase phase);
    
    
public slots:
    /// Start a new game
    void newGame();
    
};


#endif // __MAINWINDOW_HPP__