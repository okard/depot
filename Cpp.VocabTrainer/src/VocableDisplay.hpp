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
#ifndef __VT_VOCABLEDISPLAY_HPP__
#define __VT_VOCABLEDISPLAY_HPP__

#include <QFrame>
#include "ui_VocableDisplay.h"


namespace VocabTrainer {

/**
* Shows a Vocable at Display
*/
class VocableDisplay : public QFrame, private Ui::VocableDisplay
{
    
private:
    
public:
    VocableDisplay(QWidget* parent = 0);
    virtual ~VocableDisplay();
    
protected:
    
    virtual void closeEvent(QCloseEvent *e);
    virtual void moveEvent(QMoveEvent * event);
};
    

} // end namespace VocabTrainer

#endif //  __VT_VOCABLEDISPLAY_HPP__