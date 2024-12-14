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
    bool Connect_DataBase(QString DB_Name,QString Username,QString password) override;

    // 查询 语句
    bool Exec_statement(QString sql_code) override;

    bool isTableExit(QString TableName,QString Tablecode) override;

    // 查询数据库中 的结果
    bool Exec_Query_Data(QString query_code) override;

    // 关闭数据库
    bool Close_Sql() override;

signals:


private:

};

#endif // MYSQLDATA_H
