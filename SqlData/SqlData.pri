# 通过线程的形式 引用 SQL多态,来对数据库进行初始化，
# 使用数据库线程池的方案来提高 数据库访问的效率


SOURCES += \
    # main.cpp \
    $$PWD/mysqldata.cpp \
    $$PWD/sqldata.cpp \
    $$PWD/sqllite.cpp \
    $$PWD/sqlthread.cpp

HEADERS += \
    $$PWD/mysqldata.h \
    $$PWD/sqldata.h \
    $$PWD/sqllite.h \
    $$PWD/sqlthread.h

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target
