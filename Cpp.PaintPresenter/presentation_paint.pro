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
LIBPATH += poppler-qt5
#LIBS += -lpoppler-qt5.so

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/paintwidget.cpp

HEADERS  += src/mainwindow.h \
    src/paintwidget.h

FORMS    += src/mainwindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    readme.md
