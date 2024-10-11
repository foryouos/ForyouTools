#ifndef FORYOUCONTROL_H
#define FORYOUCONTROL_H

#include <QObject>
#include <QMessageBox>
#include <QThread>
#include "colorthread.h"
class ForyouControl : public QObject
{
    Q_OBJECT
public:
    explicit ForyouControl(QObject *parent = nullptr);
    ~ForyouControl() override;

public slots:
    void ForyouControl_Init();


signals:

private slots:

    // 中国传统色初始化
    void Chinese_Color_Init();

    // 私有变量
private:

    // 定义私有类
private:

    QThread *Color_Thread = nullptr;
    ColorThread *colorthread = nullptr;
};

#endif // FORYOUCONTROL_H
