#-------------------------------------------------
#
# Project created by QtCreator 2021-03-30T22:07:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dynamic_BG
TEMPLATE = app
LIBS += -lUser32 -lAdvapi32

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

RC_ICONS = DyBg.ico

SOURCES += \
        main.cpp \
        widget.cpp \
    Snipaste_Model/image.cpp \
    Snipaste_Model/snapshot.cpp \
    SysTray_Model/mytray.cpp

HEADERS += \
        widget.h \
    Snipaste_Model/image.h \
    Snipaste_Model/snapshot.h \
    SysTray_Model/mytray.h

FORMS += \
        widget.ui \
    Snipaste_Model/image.ui \
    Snipaste_Model/snapshot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
