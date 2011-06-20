/*
    This file is part of VocabTrainer.

    VocabTrainer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with VocabTrainer.  If not, see <http://www.gnu.org/licenses/>. 
*/
#include "VocableDisplay.hpp"

#include <QDesktopWidget>
#include <QMoveEvent>

using VocabTrainer::VocableDisplay;


VocableDisplay::VocableDisplay(QWidget* parent)
    : QFrame(parent, Qt::CustomizeWindowHint | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
{
    setupUi(this);
    
    //TODO right detection on all platforms and wms
    QRect geoScreen = QApplication::desktop()->screenGeometry(this);

    //use complete width, height = 1/10 of screen, y position + 20 current workaround
    this->setGeometry(geoScreen.x(), geoScreen.y()+20, geoScreen.width(), geoScreen.height()/10);
    this->setFixedSize(this->width(), this->height());
}


VocableDisplay::~VocableDisplay()
{

}


void VocableDisplay::moveEvent(QMoveEvent* event)
{
    event->ignore();
    QFrame::moveEvent(event);
}


void VocableDisplay::closeEvent(QCloseEvent* e)
{

}
