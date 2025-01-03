﻿#include "todolistwidget.h"
#include "ui_todolistwidget.h"
#include <QListWidgetItem>
ToDoListWidget::ToDoListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToDoListWidget)
{
    ui->setupUi(this);
    // 点击呈现侧边栏
    connect(ui->AddTask,&QPushButton::clicked,this,[&](){if(!G_ToListDetail_Slide_Status){this->ToDoListDetail_Side_DisPlay_Control(true);}});
    //隐藏toList详情侧边栏
    connect(ui->Close_DoDetaiSlide,&QPushButton::clicked,this,[&](){this->ToDoListDetail_Side_DisPlay_Control(false);});
    // 初始化任务清单侧边栏
    this->ToDoList_Side_Init();



    // 循环初始化
    // 每一行是一个QListWidgetItem

    for(int x=0;x<10;x++)
    {
        // 填充字符串
        QString str = QString::asprintf("192.168.1.%d",x);

        // 新建一个项

        QListWidgetItem *aItem = new QListWidgetItem();

        aItem->setText(str);                        // 设置文字标签
        //aItem->setIcon(aIcon);                      // 设置图标
        aItem->setCheckState(Qt::Unchecked);          // 设为选中状态
        aItem->setFlags(Qt::ItemIsSelectable |      // 设置为不可编辑状态
                        Qt::ItemIsUserCheckable
                        |Qt::ItemIsEnabled);

        // 增加项到列表中
        ui->ToDoList->addItem(aItem);
    }


}

ToDoListWidget::~ToDoListWidget()
{
    delete ui;
}

void ToDoListWidget::ToDoList_Side_Init()
{
    // ***************** 任务清单侧边栏 ****************
    ToListpropertyAnimation = new QPropertyAnimation(ui->ToDoListDetail_Side, "pos", this); //加上任务名称
    ToListpropertyAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    // ToListpropertyAnimation->setDuration(300);
    // 侧边栏隐藏与呈现之后的操作
    // 连接动画值变化的信号
    connect(ToListpropertyAnimation, &QPropertyAnimation::valueChanged, this, [this](const QVariant &value) {
        // 每次动画值改变时，更新主控件的位置
        QPoint newPos = value.toPoint();
        int New_Width = 0;
        if(G_ToListDetail_Slide_Status) //打开状态呢
        {
            New_Width = newPos.x();
        }
        else
        {

            New_Width = newPos.x();
        }
        ui->ToDoListWidget_Left->setGeometry(ui->ToDoListWidget_Left->x(),ui->ToDoListWidget_Left->x(),New_Width, ui->ToDoListWidget_Left->height()); // 更新主控件位置
    });


    connect(ToListpropertyAnimation, &QPropertyAnimation::finished, this, [this]() {
        // 更新主控件的位置 实时更新其位置
        if(G_ToListDetail_Slide_Status) //打开状态呢
        {
            // 打开到关闭
            ui->ToDoListDetail_Side->setVisible(false); // 隐藏 是在完成之后
            G_ToListDetail_Slide_Status = false;
        }
        else
        {
            ui->ToDoListDetail_Side->setVisible(true); // 隐藏 是在完成之后
            // 关闭到打开
            G_ToListDetail_Slide_Status = true;
        }
    });


    // 调用呈现与关闭 ToDoListDetail_Side 函数
    this->ToDoListDetail_Side_DisPlay_Control(false);
}

void ToDoListWidget::ToDoListDetail_Side_DisPlay_Control(bool display)
{
    G_ToListDetail_Slide_Width = ui->ToDoListWidget_Left->width();
    if(display)
    {
        ToListpropertyAnimation->setStartValue(QPoint(ui->ToDoWidget->width(), 0)); //从负左边即进入隐藏区域
        ToListpropertyAnimation->setEndValue(QPoint(ui->ToDoWidget->width()-ui->ToDoListDetail_Side->width() , 0));
        //设置方向，向后
        ToListpropertyAnimation->setDirection(QAbstractAnimation::Forward);
    }
    else
    {

        ToListpropertyAnimation->setStartValue(QPoint(ui->ToDoWidget->width(), 0)); //从负左边即进入隐藏区域
        ToListpropertyAnimation->setEndValue(QPoint(ui->ToDoWidget->width()-ui->ToDoListDetail_Side->width() , 0));
        //设置方向，向后
        ToListpropertyAnimation->setDirection(QAbstractAnimation::Backward);
    }
    //开启侧边栏移动
    ToListpropertyAnimation->start();
}
