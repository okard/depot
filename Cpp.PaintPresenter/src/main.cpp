
#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "MainWindow.hpp"
#include "PresentationViewer.hpp"

int main(int argc, char *argv[])
{
	//QGuiApplication app(argc, argv);
	 QApplication app(argc, argv);

	//register ScreenshotView, PdfView ???
    qmlRegisterType<PresentationViewer>("PP", 1, 0, "PresentationViewer");

	// QML Window
	QQmlApplicationEngine engine;
	engine.setOutputWarningsToStandardError(true);
	engine.load("qml/MainWindow.qml");

    return app.exec();
}
