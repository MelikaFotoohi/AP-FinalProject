QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bank.cpp \
    building.cpp \
    card.cpp \
    developmentcard.cpp \
    dice.cpp \
    game.cpp \
    location.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    player.cpp \
    port.cpp \
    resourcecard.cpp \
    robber.cpp \
    specialcard.cpp \
    thread.cpp \
    tile.cpp \
    trade.cpp

HEADERS += \
    bank.h \
    building.h \
    card.h \
    developmentcard.h \
    dice.h \
    game.h \
    location.h \
    login.h \
    mainwindow.h \
    map.h \
    player.h \
    port.h \
    resourcecard.h \
    robber.h \
    specialcard.h \
    thread.h \
    tile.h \
    trade.h

FORMS += \
    login.ui \
    mainwindow.ui \
    map.ui \
    player.ui \
    trade.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
