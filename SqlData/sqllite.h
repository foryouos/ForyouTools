#ifndef SQLLITE_H
#define SQLLITE_H

#include <QObject>
#include "sqldata.h"
#include <QDateTime>


class SqlLite : public SqlData
{
    Q_OBJECT
public:
    explicit SqlLite(QObject *parent = nullptr);
    ~SqlLite() override;
public slots:
    bool Connect_DataBase(QString DB_Name,QString Username,QString password) override;
    // 执行 语句

    // 查询 语句
    bool Exec_statement(QString sql_code) override;
    // 检查数据表是否存在
    bool isTableExit(QString TableName,QString Tablecode) override;
    // 查询数据库中 的结果
    bool Exec_Query_Data(QString query_code) override;

    // 关闭数据库
    bool Close_Sql() override;



private:
    QSqlDatabase m_database;


};

#endif // SQLLITE_H
