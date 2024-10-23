#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QThread>
#include "mainwidgetcontrol.h"
#include "./WaveProgressBar/wareprogressbar.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

public slots:
    // 呈现本周
    void Deal_Week_Size_Display(QString weeksize);
    // 呈现本年度剩余天数 呈现今年剩余多少天，已经过去多少天 通过UI的形式呈现出来
    void Deal_Year_Of_Today_Display_UI(int year_day,int daysPassed);


signals:
    void SetMainWidget_Init(); //获取本周是大周还是小周


private:
    Ui::MainWidget *ui;
    QThread *mthread = nullptr;
    MainWidgetControl *maintwidgetcontrol = nullptr;
    WareProgressBar * wareprogress_year= nullptr;



};
#endif // MAINWIDGET_H
