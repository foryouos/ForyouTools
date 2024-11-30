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

public slots:
    // 获取支持的所有SQL 驱动
    QStringList Get_All_Sql_Driver();
    // 创建 与 数据库的链接，初始化 数据库函数，传入链接的数据库，以及数据库文件，
    bool Connect_Sql_Data(DBSQL DB_SQL,QString SQL_Name);



signals:
    // 发送链接数据库 信号
    void Send_Conn_Sql_Name(QString Sql_Name);
private:
    SqlData *m_sqldate = nullptr;
    QThread *mthread = nullptr;

};

#endif // SQLTHREAD_H
