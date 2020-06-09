#-------------------------------------------------
#
# Project created by QtCreator 2019-08-12T21:29:45
#
#-------------------------------------------------

QT += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    clientschat.cpp \
    Client.cpp \
    Packaging.cpp \
    LoginDialog.cpp \

HEADERS  += \
    clientschat.h \
    Client.h \
    Packaging.h \
    LoginDialog.h \

RESOURCES += \
    resource.qrc

DISTFILES +=
