QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    area.cpp \
    arealinepiesettings.cpp \
    bar.cpp \
    barsettings.cpp \
    candlestick.cpp \
    candlesticksettings.cpp \
    chart.cpp \
    chartselection.cpp \
    chartsettings.cpp \
    chartwindow.cpp \
    controller.cpp \
    graphwindow.cpp \
    line.cpp \
    main.cpp \
    mainwindow.cpp \
    pie.cpp

HEADERS += \
    area.h \
    arealinepiesettings.h \
    bar.h \
    barsettings.h \
    candlestick.h \
    candlesticksettings.h \
    chart.h \
    chartselection.h \
    chartsettings.h \
    chartwindow.h \
    controller.h \
    flags.h \
    graphwindow.h \
    line.h \
    mainwindow.h \
    pie.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
