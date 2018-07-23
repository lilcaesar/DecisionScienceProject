TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

LIBS += -lstdc++fs
LIBS += -lboost_filesystem -lboost_system

SOURCES += \
        main.cpp \
    clarkwrightfunctions.cpp \
    semaphore.cpp \
    genericfunctions.cpp

HEADERS += \
    clarkwrightfunctions.h \
    semaphore.h \
    genericfunctions.h
