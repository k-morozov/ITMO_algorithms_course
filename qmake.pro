TEMPLATE = app

CONFIG += console c++17
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17 -lstdc++fs -O3 -Wall -Wextra -pedantic

CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
