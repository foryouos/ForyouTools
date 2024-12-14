#ifndef SQLDATA_H
#define SQLDATA_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
// 接口函数  实际函数

class SqlData : public QObject
{
    Q_OBJECT

public:
    SqlData(QObject *parent = nullptr);
    virtual ~SqlData();

public slots:
    // 链接数据库 传入数据库
    virtual bool Connect_DataBase(QString DB_Name,QString Username,QString password) = 0;
    virtual bool Exec_statement(QString sql_code) = 0;  //执行SQL 语句
    virtual bool isTableExit(QString TableName,QString Tablecode) = 0; // 检查表是否存在，如果不存在则创建表格
    virtual bool Exec_Query_Data(QString query_code) = 0;
    virtual bool Close_Sql() = 0;




private slots:

signals:
    // 发送出去 Fit健康所需要 的 Sql数据
    void Send_Fit_Data(QString startDate,float Exercise,float BMI,QString Week,float weight);

private:


};
#endif // SQLDATA_H
