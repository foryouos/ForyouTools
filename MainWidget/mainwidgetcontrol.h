#ifndef MAINWIDGETCONTROL_H
#define MAINWIDGETCONTROL_H

#include <QObject>
#include <QDate>
class MainWidgetControl : public QObject
{
    Q_OBJECT
public:
    explicit MainWidgetControl(QObject *parent = nullptr);
    ~MainWidgetControl() override;

    // 控制函数初始化
    void MainWidgetControlInit();


public slots:
    // 计算本周是大周还是 小周，计算方式以每年的第一周为小周，依次类推到年底，
    // 奇数周 小周，偶数周 大周
    void Get_Week_of_size();
    // 获取一年的剩余天数
    int Get_Year_of_Day();

signals:
    // 发出本周是大周还是小周
    void Send_Week_Of_Size(QString week);
    // 发出今年移动多少天，已经过去多少天
    void Send_Year_Of_Today(int year_day,int daysPassed);



private:

};

#endif // MAINWIDGETCONTROL_H
