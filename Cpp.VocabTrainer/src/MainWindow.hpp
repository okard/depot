#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include <QMainWindow>
#include "ui_MainWindow.h"


namespace VocabTrainer {

class MainWindow : public QMainWindow, private Ui::MainWindow
{
public:
    MainWindow();
};

} //end namespace VocabTrainer

#endif // MAINWINDOW_HPP
