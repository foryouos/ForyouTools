#include "sqllite.h"

SqlLite::SqlLite(QObject *parent)
    : SqlData{parent}
{

}

SqlLite::~SqlLite()
{

}

bool SqlLite::Connect_DataBase(QString DB_Name)
{
    // TODO:从没有数据库  到创建

    qDebug()<<"需要连接的数据库名称为:"<<DB_Name;



    return true;
}
