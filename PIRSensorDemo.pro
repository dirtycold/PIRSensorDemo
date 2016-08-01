#-------------------------------------------------
#
# Project created by QtCreator 2016-07-28T10:28:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PIRSensorDemo
TEMPLATE = app

CONFIG += C++11

LIBS += -lwiringPi


SOURCES += main.cpp\
        qcustomplot.cpp \
        pirsensordemowidget.cpp \
        pirsensor.cpp \
    pirsensordemosimplewidget.cpp

HEADERS  += qcustomplot.h \
            pirsensordemowidget.h \
            pirsensor.h \
    pirsensordemosimplewidget.h
