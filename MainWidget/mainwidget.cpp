#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPropertyAnimation>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    mthread = new QThread;
    maintwidgetcontrol = new MainWidgetControl;
    // 发送请求
    connect(this,&MainWidget::SetMainWidget_Init,maintwidgetcontrol,&MainWidgetControl::MainWidgetControlInit);
    // 处理返回请求的数据
    connect(maintwidgetcontrol,&MainWidgetControl::Send_Week_Of_Size,this,&MainWidget::Deal_Week_Size_Display);
    // 处理返回的 已经获取的天数
    connect(maintwidgetcontrol,&MainWidgetControl::Send_Year_Of_Today,this,&MainWidget::Deal_Year_Of_Today_Display_UI);
    maintwidgetcontrol->moveToThread(mthread);
    mthread->start();

    // 调用获取大周还是小周
    emit SetMainWidget_Init();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::Deal_Week_Size_Display(QString weeksize,int weekof_day)
{
    ui->WeekSize->setText(weeksize);
    ui->WeekDay->setText(QString::number(weekof_day));
}

void MainWidget::Deal_Year_Of_Today_Display_UI(int year_day, int daysPassed)
{
    ui->Year_Left_Day->setText(QString::number(year_day-daysPassed));
    if(wareprogress_year==nullptr)
    {
        wareprogress_year = new WareProgressBar(this);
    }
    wareprogress_year->setWaveHeight(0);                          // 设置水波高度
    wareprogress_year->setPieCircleColor(QColor(255,107,107));    // 设置饼行进度条圆颜色
    wareprogress_year->setwaterColor(QColor(255,107,107));        // 设置水颜色
    wareprogress_year->setWaterIsvisible(true);                   // 设置水是否可见
    wareprogress_year->setPeiIsForwardOrientation(false);         // 设置饼型进度条圆前进方向
    wareprogress_year->setMaxValue(year_day);
    wareprogress_year->setMinValue(0);
    wareprogress_year->setValue(daysPassed);
    // wareprogress_year->setSuffixText("V");                         // 设置后缀文本
    // ret->set

    ui->DayWaveBarLayout->addWidget(wareprogress_year);

    qDebug()<<ui->DayWaveBarWidget->pos()<<ui->DayWaveBarWidget->width()<<ui->DayWaveBarWidget->height();
    //实现对年份百分比的缩放 并循环
    QPropertyAnimation *pAnimation = new QPropertyAnimation(ui->DayWaveBarWidget, "geometry");
    pAnimation->setDuration(3000); // 设置动画执行时间，单位毫秒
    pAnimation->setStartValue(QRect(520, 70, 200, 191)); // 初始值
    pAnimation->setEndValue(QRect(520, 70, 200, 96)); // 结束值
    pAnimation->setEasingCurve(QEasingCurve::InOutQuad); // 设置速度曲线
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped); // 执行动画，结束后删除对象

}
