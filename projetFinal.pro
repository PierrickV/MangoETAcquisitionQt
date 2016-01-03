#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T08:41:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projetFinal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mangoconfiguration.cpp \
    lecturevoie.cpp \
    hled.cpp \
    e_Numerique.cpp \
    e_Analogique.cpp \
    mangogsm.cpp \
    sdtopc.cpp \
    s_numerique.cpp \
    iris_bdd.cpp

HEADERS  += mainwindow.h \
    mangoconfiguration.h \
    lecturevoie.h \
    hled.h \
    e_Numerique.h \
    e_Analogique.h \
    mangogsm.h \
    sdtopc.h \
    s_numerique.h \
    iris_bdd.h

FORMS    += mainwindow.ui

include(D:/MangoAcqQt/qextserialport-1.2rc/src/qextserialport.pri)

RESOURCES += \
    ressources.qrc
