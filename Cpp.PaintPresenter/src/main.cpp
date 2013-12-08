#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QApplication app(argc, argv);
    QQmlApplicationEngine engine("main.qml");
    return app.exec();
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    
    return a.exec();
}
