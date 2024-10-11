#ifndef COLORTHREAD_H
#define COLORTHREAD_H

#include <QObject>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
class ColorThread : public QObject
{
    Q_OBJECT
public:
    explicit ColorThread(QObject *parent = nullptr);

public slots:

    void Color_Init_Slot();
    // 查询颜色明细 所有 颜色名称
    // 查询函数

signals:


private:
    QString Current_Path;

};

#endif // COLORTHREAD_H
