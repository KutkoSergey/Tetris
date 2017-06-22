QT       += core gui
QT+= widgets
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app


SOURCES += main.cpp\
    MainWindow.cpp \
    Field.cpp \
    element.cpp \
    control.cpp \
    class_file.cpp \
    my_exception.cpp

HEADERS  += \
    class_file.h \
    MainWindow.h \
    Feild.h \
    element.h \
    control.h \
    my_exception.h

FORMS    +=

QMAKE_CXXFLAGS += -std=c++11
