#include "sqlthread.h"
#include "sqllite.h"
#include "mysqldata.h"
SQLThread::SQLThread(QObject *parent)
    : QObject{parent}
{}

QStringList SQLThread::Get_All_Sql_Driver()
{
    QStringList drivers = QSqlDatabase::drivers(); //获取到qt中所支持的数据库类型


    return drivers;

}

bool SQLThread::Connect_Sql_Data(DBSQL DB_SQL, QString SQL_Name)
{
    if(mthread == nullptr)
    {
        mthread = new QThread;
    }
    if(m_sqldate == nullptr)
    {
        switch (DB_SQL) {
        case DBSQL::SQLite3:
            m_sqldate = new SqlLite;



            break;
        case DBSQL::MYSQL:
        {
            m_sqldate = new MySQLData;
            break;
        }
        default:
            break;
        }
    }
    m_sqldate->moveToThread(mthread);
    // 使用信号与槽函数 连接 数据库
    connect(this,&SQLThread::Send_Conn_Sql_Name,m_sqldate,&SqlData::Connect_DataBase);
    mthread->start();

    emit Send_Conn_Sql_Name(SQL_Name);

    return true;

}
