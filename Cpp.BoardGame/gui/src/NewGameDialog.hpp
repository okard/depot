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
#ifndef __NEWGAMEDIALOG_HPP__
#define __NEWGAMEDIALOG_HPP__

#include <QDialog>

#include "ui_NewGameDialog.h"

#include "MainWindow.hpp"

/**
* Dialog to start a new Game
*/
class NewGameDialog : public QDialog, private Ui::NewGameDialog
{
    Q_OBJECT
    
private:
    MainWindow& mainWindow;
    
public:
    /**
    * Creates a new Main Window
    */
    NewGameDialog(MainWindow& parent);
    
    /**
    * Destructs Main Window
    */
    virtual ~NewGameDialog();
    
public slots:
    
    void startLocalGame();
    void startAIGame();   
    void hostGame();
    void connectToGame(); 
};



#endif // __NEWGAMEDIALOG_HPP__