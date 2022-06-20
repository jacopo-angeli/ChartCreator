######################################################################
# Automatically generated by qmake (3.1) Sun Jun 19 09:27:55 2022
######################################################################
TEMPLATE = app
TARGET = ChartCreator
QT = core gui widgets charts
INCLUDEPATH += .

ROOT_DIRECTORY = $$PWD/ChartCreator
BUILD_DIRECTORY = $${ROOT_DIRECTORY}/build
EXEC_DIRECTORY = $${ROOT_DIRECTORY}

DESTDIR = $${EXEC_DIRECTORY}
QMAKE_QMAKE = $${EXEC_DIRECTORY}
OBJECTS_DIR = $${BUILD_DIRECTORY}/obj
MOC_DIR = $${BUILD_DIRECTORY}/moc
RCC_DIR = $${BUILD_DIRECTORY}/rcc

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
SOURCES += \
    cppFiles/area.cpp \
    cppFiles/arealinepiesettings.cpp \
    cppFiles/bar.cpp \
    cppFiles/barsettings.cpp \
    cppFiles/candlestick.cpp \
    cppFiles/candlesticksettings.cpp \
    cppFiles/chart.cpp \
    cppFiles/chartselection.cpp \
    cppFiles/chartsettings.cpp \
    cppFiles/controller.cpp \
    cppFiles/line.cpp \
    cppFiles/main.cpp \
    cppFiles/mainwindow.cpp \
    cppFiles/pie.cpp

HEADERS += \
    hFiles/area.h \
    hFiles/arealinepiesettings.h \
    hFiles/bar.h \
    hFiles/barsettings.h \
    hFiles/candlestick.h \
    hFiles/candlesticksettings.h \
    hFiles/chart.h \
    hFiles/chartselection.h \
    hFiles/chartsettings.h \
    hFiles/controller.h \
    hFiles/flags.h \
    hFiles/line.h \
    hFiles/mainwindow.h \
    hFiles/pie.h

RESOURCES = application.qrc
