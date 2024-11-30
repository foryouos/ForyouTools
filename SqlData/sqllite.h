#ifndef SQLLITE_H
#define SQLLITE_H

#include <QObject>
#include "sqldata.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class SqlLite : public SqlData
{
    Q_OBJECT
public:
    explicit SqlLite(QObject *parent = nullptr);
    ~SqlLite() override;
public slots:
    bool Connect_DataBase(QString DB_Name) override;
signals:
};

#endif // SQLLITE_H
