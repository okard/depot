#include "PresentationDialog.hpp"

#include <QApplication>
#include <QDesktopWidget>

PresentationDialog::PresentationDialog(QWidget *parent) :
    QDialog(parent)
{

    //set size to screen (fullscreen)
    //if second screen is available?
    QRect screenres = QApplication::desktop()->screenGeometry(1);
    this->move(QPoint(screenres.x(), screenres.y()));
    this->resize(screenres.width(), screenres.height());
    //this->showFullScreen();
}

void PresentationDialog::toggleVisibility()
{
    if(this->isVisible())
        this->hide();
    else
        this->showFullScreen();

}
