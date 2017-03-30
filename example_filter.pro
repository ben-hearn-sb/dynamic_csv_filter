QT += core
QT += gui
QT += widgets

CONFIG += c++11

TARGET = test_filter
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    custom_proxy_filter.cpp \
    csv_window.cpp \
    file_utils.cpp \
    general_utils.cpp \
    qt_utils.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    custom_proxy_filter.h \
    csv_window.h \
    file_utils.h \
    general_utils.h \
    qt_utils.h

INCLUDEPATH += C:/boost_1_63_0/
LIBS += "-LC:/boost_1_63_0/stage/lib/"
