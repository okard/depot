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


INCLUDEPATH += poppler-qt5/include
#LIBPATH += poppler-qt5
#LIBS += -lpoppler-qt5.so
LIBS += "-L/home/master/20.Dev/10.Projects/10.Depot/Cpp.PaintPresenter/poppler-qt5" -lpoppler-qt5

SOURCES += src/main.cpp\
    src/PresentationDialog.cpp \
    src/MainWindow.cpp \
    src/PaintWidget.cpp

HEADERS  += \
    src/PresentationDialog.hpp \
    src/MainWindow.hpp \
    src/PaintWidget.hpp

FORMS    += src/mainwindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    readme.md
