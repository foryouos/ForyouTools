#include "mysqldata.h"
#include <QtSql/QSqlDatabase>


MySQLData::MySQLData(QObject *parent)
    : SqlData{parent}
{

}

MySQLData::~MySQLData()
{

}

bool MySQLData::Connect_DataBase(QString DB_Name)
{

    return true;
}
