#include "PresentationDialog.hpp"

#include <QApplication>
#include <QDesktopWidget>

PresentationDialog::PresentationDialog(QWidget *parent) :
    QDialog(parent)
{

    //set size to screen (fullscreen)
    QRect screenres = QApplication::desktop()->screenGeometry(1);
    this->move(QPoint(screenres.x(), screenres.y()));
    //this->showFullScreen();

    //this->isVisible()
}
