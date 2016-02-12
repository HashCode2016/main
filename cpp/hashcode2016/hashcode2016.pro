QT += core
QT -= gui

TARGET = hashcode2016
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    order.cpp \
    drone.cpp \
    warehouse.cpp \
    warehousemanager.cpp \
    dronemanager.cpp \
    ordermanager.cpp \
    parser.cpp

HEADERS += \
    order.h \
    drone.h \
    warehouse.h \
    warehousemanager.h \
    dronemanager.h \
    ordermanager.h \
    macro.h \
    parser.h

