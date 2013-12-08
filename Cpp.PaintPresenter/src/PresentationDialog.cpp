#include "PresentationDialog.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QPaintEvent>

#include "PaintWidget.hpp"

PresentationDialog::PresentationDialog(PaintWidget &widget)
    : QDialog(&widget), widget_(widget), toggleViewAction_("Presentation Dialog", this)
{
    //get screen
    QRect screenres = QApplication::desktop()->screenGeometry(1);
    //move dialog to screen
    this->move(QPoint(screenres.x(), screenres.y()));


    connect(&toggleViewAction_, &QAction::triggered, this, &PresentationDialog::toggleVisibility);

    //hook up drawingschanged event of paint widget

    //set size to screen (fullscreen)
    //if second screen is available?

    //this->resize(screenres.width(), screenres.height());
    //this->showFullScreen();
}

PresentationDialog::~PresentationDialog()
{

}

void PresentationDialog::paintEvent(QPaintEvent *event)
{
    QRect dirtyRect = event->rect();
    QPainter painter(this);
    widget_.paintTo(dirtyRect, painter);
}


void PresentationDialog::toggleVisibility()
{
    if(this->isVisible())
    {
        this->hide();
        toggleViewAction_.setChecked(false);
    }
    else
    {
        this->showFullScreen();
        toggleViewAction_.setChecked(true);
    }

}
