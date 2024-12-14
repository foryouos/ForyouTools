#include "sqlthread.h"
#include "sqllite.h"
#include "mysqldata.h"
SQLThread::SQLThread(QObject *parent)
    : QObject{parent}
{}

SQLThread::~SQLThread()
{
    if(m_sqldate != nullptr && mthread != nullptr && mthread->isRunning())
    {
        mthread->quit();
        mthread->wait();
        mthread->exit();
        delete mthread;
        mthread = nullptr;
        delete m_sqldate;
        m_sqldate = nullptr;
    }
}

QStringList SQLThread::Get_All_Sql_Driver()
{
    QStringList drivers = QSqlDatabase::drivers(); //获取到qt中所支持的数据库类型

    return drivers;

}

bool SQLThread::Connect_Sql_Data(DBSQL DB_SQL,QString SQL_Name,QString Username,QString password)
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
    connect(this,&SQLThread::Send_SQl_Statement,m_sqldate,&SqlData::Exec_statement);
    connect(this,&SQLThread::Send_Judge_Table_IsExit,m_sqldate,&SqlData::isTableExit);
    connect(this,&SQLThread::Send_Query_Sql_Data,m_sqldate,&SqlData::Exec_Query_Data);
    // 接受来自 线程sql中传出的读取健康数据
    connect(m_sqldate,&SqlData::Send_Fit_Data,this,&SQLThread::Deal_Fit_Data);
    mthread->start();

    emit Send_Conn_Sql_Name(SQL_Name,Username,password);

    return true;

}

bool SQLThread::Exec_SQl_Statement(QString sql_code)
{
    emit Send_SQl_Statement(sql_code);
    return true;
}

bool SQLThread::Judge_Table_IsExit(QString tableName,QString code)
{
    // 判断数据库 表 是否存在
    emit Send_Judge_Table_IsExit(tableName,code);
    return true;
}

bool SQLThread::Exec_Sql_Query(QString QueryCode)
{
    emit Send_Query_Sql_Data(QueryCode);
    return true;
}

void SQLThread::Deal_Fit_Data(QString startDate, float Exercise, float BMI, QString Week, float weight)
{
    emit Send_Fit_Data( startDate, Exercise, BMI, Week, weight);
}
