#-------------------------------------------------
#
# Project created by QtCreator 2013-06-18T11:10:45
#
#-------------------------------------------------

TEMPLATE = app

QT       += core gui declarative widgets qml quick

TARGET = presentation_paint

QMAKE_CXXFLAGS += -std=c++11

CONFIG += qml_debug console

# whats wrong????
#unix:INCLUDEPATH += "/usr/include/qt/QtQml"
#unix:INCLUDEPATH += "/usr/include/qt/QtQuick"
#LIBS += -lQt5Qml
#LIBS += -lQt5Quick

LIBS +=  -lpoppler-qt5

SOURCES += src/main.cpp\
    src/PaintTool.cpp \
    src/PaintWidget.cpp \
    src/PresentationViewer.cpp \
	src/view/View.cpp \
	src/view/PdfView.cpp \
	src/view/ViewListModel.cpp


HEADERS  += \
	src/Helper.hpp \
    src/PaintWidget.hpp \
    src/PaintTool.hpp \
    src/PresentationViewer.hpp \
	src/view/View.hpp \
	src/view/PdfView.hpp \
	src/view/ViewListModel.hpp


RESOURCES += \
    resources.qrc

OTHER_FILES += \
    readme.md \
    qml/MainWindow.qml \
    images/icon_yellow.png \
    images/icon_windows.png \
    images/icon_trash.png \
    images/icon_screenshot_clear.png \
    images/icon_screenshot.png \
    images/icon_save.png \
    images/icon_red.png \
    images/icon_prev.png \
    images/icon_presentation.png \
    images/icon_pen2.png \
    images/icon_pen.png \
    images/icon_pdf.png \
    images/icon_next.png \
    images/icon_highlighter.png \
    images/icon_green.png \
    images/icon_ereaser.png \
    images/icon_draw_text.png \
    images/icon_draw_rectangle.png \
    images/icon_clear.png \
    images/icon_blue.png \
    images/icon_black.png \
    qml/PresenterWidget.qml \
    qml/MainWindow.js \
    qml/TimerWidget.qml \
    qml/PresentationWindow.qml
