
#include <QApplication>
#include <QQmlApplicationEngine>

#include "MainWindow.hpp"
#include "PresentationViewer.hpp"

int main(int argc, char *argv[])
{


    QApplication app(argc, argv);

    // QT Window
    //MainWindow w;

    qmlRegisterType<PresentationViewer>("PP", 1, 0, "PresentationViewer");
    //register ScreenshotView, PdfView

    // QML Window
    QQmlApplicationEngine engine("qml/MainWindow.qml");
    
    return app.exec();
}
