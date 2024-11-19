#ifndef SQLDATA_H
#define SQLDATA_H

#include <QWidget>

// 接口函数  实际函数

class SqlData : public QWidget
{
    Q_OBJECT

public:
    SqlData(QWidget *parent = nullptr);
    ~SqlData();

};
#endif // SQLDATA_H
