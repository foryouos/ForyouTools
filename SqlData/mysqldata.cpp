#include "mysqldata.h"
#include <QtSql/QSqlDatabase>


MySQLData::MySQLData(QObject *parent)
    : SqlData{parent}
{

}

MySQLData::~MySQLData()
{

}

bool MySQLData::Connect_DataBase(QString DB_Name,QString Username,QString password)
{

    return true;
}

bool MySQLData::Exec_statement(QString sql_code)
{
    return true;
}

bool MySQLData::isTableExit(QString TableName, QString Tablecode)
{
    return true;
}

bool MySQLData::Exec_Query_Data(QString query_code)
{
    return true;
}
bool MySQLData::Close_Sql()
{
    return true;
}
