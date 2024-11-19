#include "mainwidgetcontrol.h"

MainWidgetControl::MainWidgetControl(QObject *parent)
    : QObject{parent}
{}

MainWidgetControl::~MainWidgetControl()
{

}

void MainWidgetControl::MainWidgetControlInit()
{
    this->Get_Week_of_size();
    this->Get_Year_of_Day();
}

void MainWidgetControl::Get_Week_of_size()
{
    int iWeekNumber = QDate::currentDate().weekNumber();
    int DayOfWeek = QDate::currentDate().dayOfWeek();
    qDebug()<<"MainWidgetControl Today iWeekNumber: "<<iWeekNumber<<"今天星期:"<<DayOfWeek;
    if (iWeekNumber % 2 == 0)
    {
        // Even 偶数
        emit Send_Week_Of_Size("大周",DayOfWeek);
    }
    else
    {
        // Odd 奇数
        emit Send_Week_Of_Size("小周",DayOfWeek);
    }
}

int MainWidgetControl::Get_Year_of_Day()
{
    // 获取当前年份
    int year = QDate::currentDate().year();

    // 创建表示当前年份的日期对象
    QDate currentYear(year, 1, 1);

    // 获取当前年份的天数
    int daysInYear = currentYear.daysInYear();

    // 获取当前日期
    QDate today = QDate::currentDate();

    // 计算到今天为止已经过去的天数
    int daysPassed = currentYear.daysTo(today);

    // 输出结果
    qDebug() << "Year:" << year;
    qDebug() << "Days in year:" << daysInYear;
    qDebug() << "Days passed until today:" << daysPassed;
    int leftdays =  daysInYear - daysPassed;

    emit Send_Year_Of_Today(daysInYear,daysPassed);

    return leftdays;

}
