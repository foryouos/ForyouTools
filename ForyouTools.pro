include($$PWD/Notify/qtnotify.pri)
QT       += core gui
QT += webenginewidgets  # 添加webengine模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colorthread.cpp \
    foryoucontrol.cpp \
    main.cpp \
    foryouos.cpp

HEADERS += \
    colorthread.h \
    foryoucontrol.h \
    foryouos.h

FORMS += \
    foryouos.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    photo.qrc
TARGET = foryouos

#RC_ICONS = color.png


