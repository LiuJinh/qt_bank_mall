#-------------------------------------------------
#
# Project created by QtCreator 2017-11-27T21:34:04
#
#-------------------------------------------------

QT       += core gui
QT       +=       network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bank
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    commonfunc.cpp \
    login.cpp \
    personaldetail.cpp \
    signup.cpp \
    usercontrol.cpp \
    userdetail.cpp \
    maininterface.cpp \
    changepassword.cpp \
    transfer.cpp \
    server.cpp

HEADERS += \
    commonfunc.h \
    login.h \
    personaldetail.h \
    signup.h \
    usercontrol.h \
    userdetail.h \
    maininterface.h \
    changepassword.h \
    transfer.h \
    server.h

FORMS += \
        mainwindow.ui \
    login.ui
