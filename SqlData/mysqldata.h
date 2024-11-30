#ifndef MYSQLDATA_H
#define MYSQLDATA_H

#include <QObject>
#include "sqldata.h"
#include <QDebug>

class MySQLData : public SqlData
{
    Q_OBJECT
public:
    explicit MySQLData(QObject *parent = nullptr);
    ~MySQLData() override;

public slots:
    bool Connect_DataBase(QString DB_Name) override;

signals:

private:

};

#endif // MYSQLDATA_H
