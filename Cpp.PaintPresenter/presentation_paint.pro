#-------------------------------------------------
#
# Project created by QtCreator 2013-06-18T11:10:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = presentation_paint
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


#INCLUDEPATH += poppler-qt5/include
#LIBPATH += poppler-qt5
#LIBS += -lpoppler-qt5.so
LIBS +=  -lpoppler-qt5

SOURCES += src/main.cpp\
    src/PresentationDialog.cpp \
    src/MainWindow.cpp \
    src/PaintWidget.cpp

HEADERS  += \
    src/PresentationDialog.hpp \
    src/MainWindow.hpp \
    src/PaintWidget.hpp \
    src/View.hpp \
    src/PaintTool.hpp

FORMS    += src/mainwindow.ui

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
    images/icon_black.png
