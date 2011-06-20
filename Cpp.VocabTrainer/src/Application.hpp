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
#ifndef __VT_APPLICATION_HPP__
#define __VT_APPLICATION_HPP__

#include <QApplication>
#include <QSystemTrayIcon>

#include "VocableDisplay.hpp"


namespace VocabTrainer {

class Application : public QApplication
{
    Q_OBJECT
private:
    // Option/Setting Window
    
    ///Tray Icon
    QSystemTrayIcon trayIcon;
    
    ///The Vocable Display Window
    VocableDisplay vocabDisplay;
    
    
    Application();
    Application(const Application& app);   
    virtual ~Application();
    
public:
    
    static Application* instance();
    
    
    //test function
    void show();
};


} //end namespace VocabTrainer




#endif //__VT_APPLICATION_HPP__






