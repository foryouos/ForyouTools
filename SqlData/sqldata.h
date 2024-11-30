#ifndef SQLDATA_H
#define SQLDATA_H

#include <QObject>

// 接口函数  实际函数

class SqlData : public QObject
{
    Q_OBJECT

public:
    SqlData(QObject *parent = nullptr);
    virtual ~SqlData();

public slots:
    // 链接数据库 传入数据库
    virtual bool Connect_DataBase(QString DB_Name) = 0;


private slots:

signals:

private:

};
#endif // SQLDATA_H
