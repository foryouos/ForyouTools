#ifndef MYSQLDATA_H
#define MYSQLDATA_H

#include <QObject>

class MySQLData : public QObject
{
    Q_OBJECT
public:
    explicit MySQLData(QObject *parent = nullptr);

signals:
};

#endif // MYSQLDATA_H
