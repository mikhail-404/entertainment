QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += c++11

SOURCES += \
    main.cpp \
    GameWidget.cpp \
    GameLogic.cpp

HEADERS += \
    GameWidget.hpp \
    GameLogic.hpp \
    MiniGame.hpp
