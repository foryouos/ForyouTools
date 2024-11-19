#-------------------------------------------------
#
# Project created by QtCreator 2022-07-05T12:14:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = datetime2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    button_day.cpp \
    date_time_edit.cpp \
    date_time_widget.cpp \
    time_scrollbar.cpp

HEADERS  += mainwindow.h \
    button_day.h \
    date_time_defines.h \
    date_time_edit.h \
    date_time_widget.h \
    time_scrollbar.h

FORMS    += mainwindow.ui \
    date_time_widget.ui

RESOURCES += \
    resource/datetime.qrc
