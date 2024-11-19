#-------------------------------------------------
#
# Project created by QtCreator 2022-07-05T12:14:28
#
#-------------------------------------------------

# QT       += core gui

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# TARGET = datetime2
# TEMPLATE = app


SOURCES += \
    # $$PWD/mainwindow.cpp \
    $$PWD/button_day.cpp \
    $$PWD/date_time_edit.cpp \
    $$PWD/date_time_widget.cpp \
    $$PWD/time_scrollbar.cpp \
         # main.cpp

HEADERS  +=  \
    # $$PWD/mainwindow.h \
    $$PWD/button_day.h \
    $$PWD/date_time_defines.h \
    $$PWD/date_time_edit.h \
    $$PWD/date_time_widget.h \
    $$PWD/time_scrollbar.h

FORMS    += \
    # $$PWD/mainwindow.ui \
    $$PWD/date_time_widget.ui

RESOURCES += \
    $$PWD/resource/datetime.qrc
