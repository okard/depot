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
#include "Application.hpp"

using VocabTrainer::Application;

Application::Application()
    : QApplication(0, 0)
{

}

Application::Application(const VocabTrainer::Application& app)
    : QApplication(0,0)
{
}


Application* Application::instance()
{
    static Application app;
    return &app;
}

