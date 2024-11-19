# QT       += core gui

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # main.cpp \
    $$PWD/fitwidget.cpp

HEADERS += \
    $$PWD/fitwidget.h

FORMS += \
    $$PWD/fitwidget.ui

# 添加其他需要的设置，比如依赖
# DEPENDPATH += $$PWD
# INCLUDEPATH += $$PWD
# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target
