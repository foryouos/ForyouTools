include($$PWD/Notify/qtnotify.pri)
include($$PWD/MainWidget/MainWidget.pri)
include($$PWD/ToDoListWidget/ToDoListWidget.pri)
include($$PWD/ColorWidget/ColorWidget.pri)
include($$PWD/WaveProgressBar/WaveProgressBar.pri)
include($$PWD/FitWidget/FitWidget.pri)  # 健康模块
include($$PWD/SqlData/SqlData.pri)  # 数据库操作模块
include($$PWD/DataTimeCombox/DataTimeCombox.pri)  # DataTimeCombox 模块 用户选择 时间 UI 美化


QT       += core gui
QT       += charts
# QT += webenginewidgets  # 添加webengine模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # colorthread.cpp \
    foryoucontrol.cpp \
    main.cpp \
    foryouos.cpp

HEADERS += \
    # colorthread.h \
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

DISTFILES += \
    README.md


