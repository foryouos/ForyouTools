#include "sqllite.h"

SqlLite::SqlLite(QObject *parent)
    : SqlData{parent}
{

}

SqlLite::~SqlLite()
{
    qDebug()<<"执行 SqlLite的析构 函数";
    this->Close_Sql();
}

bool SqlLite::Connect_DataBase(QString DB_Name,QString Username,QString password)
{
    // TODO:从没有数据库  到创建

    qDebug()<<"需要连接的数据库名称为:"<<DB_Name;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        try {
            m_database.setDatabaseName(DB_Name);
            m_database.setUserName(Username);
            m_database.setPassword(password);
        } catch (...) {
            qDebug()<<"打开数据库文件异常";
        }
    }
    try {
        // 打开数据库
        m_database.open();
        qDebug()<<"打开数据库成功";
    } catch (...) {
        qDebug()<<"打开QSQLITE数据库出现异常"<<m_database.lastError();
    }

    return true;
}

bool SqlLite::Exec_statement(QString sql_code)
{
    if(m_database.isOpen())
    {
        QSqlQuery m_sqlquery;
        m_sqlquery.prepare(sql_code);
        if(!m_sqlquery.exec(sql_code))
        {
            qDebug()<<"Error : Fail to create table ."<<m_sqlquery.lastError();
            return false;
        }
        else
        {
            qDebug()<<"Table Created";
            return true;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool SqlLite::isTableExit(QString TableName,QString Tablecode)
{
    qDebug()<<"存在的数据库表格:"<<m_database.tables();
    if(m_database.tables().contains(TableName))
    {
        qDebug()<<"数据库表存在";
        return true;
    }
    else
    {
        qDebug()<<"数据库表不存在";
        this->Exec_statement(Tablecode);
        return false;
    }
}

bool SqlLite::Exec_Query_Data(QString query_code)
{
    qDebug()<<"查询数据库";
    //SELECT Data,Exercise,BMI,Week,weight FROM Fit;
    QSqlQuery sqlQuery;
    sqlQuery.exec(query_code);
    if(sqlQuery.exec())
    {
        while (sqlQuery.next()) {
            // 获取详细的子
            try {
                QString startDate =sqlQuery.value(0).toString();
                float Exercise = sqlQuery.value(1).toFloat();
                float BMI = sqlQuery.value(2).toFloat();
                QString Week = sqlQuery.value(3).toString();
                float weight = sqlQuery.value(4).toFloat();

                emit Send_Fit_Data(startDate,Exercise,BMI,Week,weight);
            } catch (...) {
                qDebug()<<"Bug:  解析 数据库数据 出错,请检查查看的 健康管理数据";
            }


        }
    }
    else
    {
        return false;
    }
    return true;
}

bool SqlLite::Close_Sql()
{
    qDebug()<<"关闭数据库";
    if(m_database.isOpen())
    {
        m_database.close();
    }
    return true;
}
