QT += core
QT -= gui

TARGET = hashcode2016
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/objects/order.cpp \
    src/objects/drone.cpp \
    src/objects/warehouse.cpp \
    src/managers/warehousemanager.cpp \
    src/managers/dronemanager.cpp \
    src/managers/ordermanager.cpp \
    src/utils/parser.cpp \
    src/utils/utils.cpp \
    src/utils/writer.cpp \
    src/simulator.cpp

HEADERS += \
    src/objects/order.h \
    src/objects/drone.h \
    src/objects/warehouse.h \
    src/managers/warehousemanager.h \
    src/managers/dronemanager.h \
    src/managers/ordermanager.h \
    src/utils/macro.h \
    src/utils/parser.h \
    src/utils/utils.h \
    src/utils/writer.h \
    src/struct.h \
    src/simulator.h

