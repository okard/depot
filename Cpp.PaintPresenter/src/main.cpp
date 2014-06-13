
#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "PresentationViewer.hpp"
#include "PdfView.hpp"
#include "ViewListModel.hpp"

int main(int argc, char *argv[])
{
	//QGuiApplication app(argc, argv);
	 QApplication app(argc, argv);

	//register ScreenshotView, PdfView ???
    qmlRegisterType<PresentationViewer>("PP", 1, 0, "PresentationViewer");
	qmlRegisterType<View>("PP", 1, 0, "View");
	qmlRegisterType<PdfView>("PP", 1, 0, "PdfView");
	qmlRegisterType<ViewListModel>("PP", 1, 0, "ViewListModel");
	//register ScreenshotView

	// QML Window
	QQmlApplicationEngine engine;
	engine.setOutputWarningsToStandardError(true);
	engine.load("qml/MainWindow.qml");

    return app.exec();
}
