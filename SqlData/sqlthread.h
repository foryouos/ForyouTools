#ifndef SQLTHREAD_H
#define SQLTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QSqlDatabase>
// 建立数据库 连接
#include "sqldata.h"

enum DBSQL
{
    SQLite3,
    MYSQL
};



class SQLThread : public QObject
{
    Q_OBJECT
public:
    explicit SQLThread(QObject *parent = nullptr);
    ~SQLThread() override;

public slots:
    // 获取支持的所有SQL 驱动
    QStringList Get_All_Sql_Driver();
    // 创建 与 数据库的链接，初始化 数据库函数，传入链接的数据库，以及数据库文件，
    bool Connect_Sql_Data(DBSQL DB_SQL,QString SQL_Name,QString Username,QString password);
    // 执行SQL语句
    bool Exec_SQl_Statement(QString sql_code);
    // 判断表是否存在 ,如果表不存在 传入 创建表格的代码
    bool Judge_Table_IsExit(QString tableName,QString code);
    // 执行查询 数据库
    bool Exec_Sql_Query(QString QueryCode);

    // 处理线程 处理 sql中读取的数据
    void Deal_Fit_Data(QString startDate,float Exercise,float BMI,QString Week,float weight);



signals:
    // 发送链接数据库 信号
    void Send_Conn_Sql_Name(QString DB_Name,QString Username,QString password);
    // 发送数据库要执行的语句
    void Send_SQl_Statement(QString sql_code);
    // 判断数据库中 某个表格是否存在
    bool Send_Judge_Table_IsExit(QString table_name,QString table_Code);
    // 发送 查询数据库 中 的 数据
    void Send_Query_Sql_Data(QString Sql_code);
    // 发送出去 Fit健康所需要 的 Sql数据
    void Send_Fit_Data(QString startDate,float Exercise,float BMI,QString Week,float weight);

private:
    SqlData *m_sqldate = nullptr;
    QThread *mthread = nullptr;

};

#endif // SQLTHREAD_H
