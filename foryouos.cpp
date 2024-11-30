#include "foryouos.h"
#include "ui_foryouos.h"
#include "MainWidget/mainwidget.h"
#include "ToDoListWidget/todolistwidget.h"
#include "ColorWidget/colorwidget.h"
#include "FitWidget/fitwidget.h"
foryouos::foryouos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::foryouos)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/photo/Tools.png"));
    setWindowTitle("Foryouos 工具箱");
    // 子窗体加入到主窗体初始化
    this->AddWidget_Init();

    // 初始化ACtion事件
    this->UIACtion_Init();
    // 初始化Button按钮
    this->Button_Init();
    // 初始化 Foryouos控制器
    this->ForyouControlInit();

    //首次呈现在首页
    ui->MainStackWidget->setCurrentIndex(0);

    // 初始化Notify
    this->Notify_init();

    // 初始化相关的侧边栏操作
    this->Slide_Bar_Init();



#ifdef Debug
    // 测试主UI页面透明度
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(2000); // 2 seconds
    animation->setStartValue(1.0); // Fully opaque
    animation->setEndValue(0.0); // Fully transparent
    animation->start();
#endif




}

foryouos::~foryouos()
{
    // TODO:清理所有初始化的资源
    if(foryoucontrol != nullptr && mthread != nullptr && mthread->isRunning())
    {
        mthread->quit();
        mthread->wait();
        mthread->exit();
        delete mthread;
        mthread = nullptr;
        delete foryoucontrol;
        foryoucontrol = nullptr;
    }
    delete ui;
}

void foryouos::AddWidget_Init()
{
    // 初始化布局
    MainWidget *mainwidget = new MainWidget(this);
    ui->Main_Page_Loyout->addWidget(mainwidget);
    // 初始化ToDoList布局
    ToDoListWidget *todolistwidget = new ToDoListWidget(this);
    ui->TODOPage_Layout->addWidget(todolistwidget);
    // 初始化color widget
    ColorWidget *colorwidget = new ColorWidget(this);
    ui->ColorWidget_Layout->addWidget(colorwidget);
    // 初始化 健康模块
    FitWidget *fitwidget = new FitWidget(this);
    ui->FitWidgetLayout->addWidget(fitwidget);


}

void foryouos::UIACtion_Init()
{
    //TODO:初始化UIACtion
    connect(ui->Mainaction, &QAction::triggered,this,[&](){ui->MainStackWidget->setCurrentIndex(0);});
    connect(ui->ChineseColor, &QAction::triggered,this,[&]()
    {
        this->Chinese_Web_Page_Init();
        ui->MainStackWidget->setCurrentIndex(1);
    });
    connect(ui->ToDoaction, &QAction::triggered,this,[&](){ui->MainStackWidget->setCurrentIndex(2);});
    // 点击健康 管理
    connect(ui->FitAction,&QAction::triggered,this,[&](){ui->MainStackWidget->setCurrentIndex(3);});


}

void foryouos::Button_Init()
{
    //TODO:初始化Button
    connect(ui->MainactionBtn, &QPushButton::clicked,this,[&](){ui->MainStackWidget->setCurrentIndex(0);});
    connect(ui->ChineseColorBtn, &QPushButton::clicked,this,[&]()
            {
                this->Chinese_Web_Page_Init();
                ui->MainStackWidget->setCurrentIndex(1);
            });
    connect(ui->ToDoactionBtn, &QPushButton::clicked,this,[&](){ui->MainStackWidget->setCurrentIndex(2);});
    //初始化侧边栏
    connect(ui->HideSideBtn,&QPushButton::clicked,this,&foryouos::Main_Slide_Hide_Display_Control);

}

void foryouos::Slide_Bar_Init()
{
    //************* 主页面的 侧边框 **************
    // QPropertyAnimation 隐藏窗体后 让其它窗体 呈现出来
    MainpropertyAnimation = new QPropertyAnimation(ui->sideBar, "pos", this);
    MainpropertyAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    MainpropertyAnimation->setDuration(1000);
    //使用信号与槽机制 让隐藏与呈现动作实时呈现 t

    // 连接动画值变化的信号
    connect(MainpropertyAnimation, &QPropertyAnimation::valueChanged, this, [this](const QVariant &value) {
        // 每次动画值改变时，更新主控件的位置
        //qDebug()<<"数值发生改变";
        QPoint newPos = value.toPoint();
        int new_Pox_Change = newPos.x()+80;
        int New_Width = 0;
        if(G_Main_Slide_Status) //打开状态呢
        {
            // newPos.x() 从0 ~ -80  // 让其主窗体宽度逐渐变大
            New_Width = G_initialRightWidgetWidth - newPos.x(); // Right_Main_Widget的宽度一直变化，会出现累加的结果，要注意此处的Bug = G_initialRightWidgetWidth - newPos.x(); // 使用初始宽度 // Right_Main_Widget的宽度一直变化，会出现累加的结果，要注意此处的Bug
            // qDebug()<<"从打开到关闭"<<"newPos.x() :"<<newPos.x()<<"调整x轴:"<<new_Pox_Change<<"新宽度:"<<New_Width;
        }
        else
        {
            // newPos.x() 从 -80 ~ 0
            New_Width = G_initialRightWidgetWidth - (80 + newPos.x()); //宽度逐渐变小
            // qDebug()<<"从关闭到打开"<<"newPos.x() :"<<newPos.x()<<"调整x轴:"<<new_Pox_Change<<"新宽度:"<<New_Width;
        }

        ui->Right_Main_Widget->setGeometry(new_Pox_Change,0,New_Width, ui->Right_Main_Widget->height()); // 更新主控件位置
    });


    connect(MainpropertyAnimation, &QPropertyAnimation::finished, this, [this]() {
        // 当动画完成后更新布局

        ui->Main_Widget->update();

        // 更新主控件的位置 实时更新其位置
        if(G_Main_Slide_Status) //打开状态呢
        {
            // 打开到关闭
            ui->sideBar->setVisible(false); // 隐藏 是在完成之后
            G_Main_Slide_Status = false;
        }
        else
        {
            // 关闭到打开
            G_Main_Slide_Status = true;
        }
    });


}

void foryouos::ForyouControlInit()
{
    mthread = new QThread;
    foryoucontrol = new ForyouControl;
    connect(mthread,&QThread::started,foryoucontrol,&ForyouControl::ForyouControl_Init);
    foryoucontrol->moveToThread(mthread);
    mthread->start();
}

void foryouos::Chinese_Web_Page_Init()
{

}

void foryouos::Notify_init()
{

        qDebug()<<"2,Notify 初始化";
        notify = new NotifyManager(this);
        notify->setMaxCount(5); // 设置 同时呈现 浮动提示框的数量 默认为 5
        notify->setDisplayTime(5000); // 设置 浮动提示框 呈现的时间  默认值为 10000  即 10秒
        notify->setAnimateTime(100); // 设置 浮动提示框 从出现到呈现，从呈现时间到消失的逐步变化的是时间 默认值为300ms
        notify->setSpacing(10); // 设置 浮动提示框之前 的 间隔默认值为 10
        notify->setCornerMargins(20,20); // 设置 浮动提示框 圆角 默认为 10
        notify->setNotifyWndSize(300, 80);  // 设置 浮动提示框的 尺寸 宽度和高度
        // 设置样式
        notify->setStyleSheet("#notify-background {"
                              "background: black;"
                              "}"
                              "#notify-title{"
                              "font: bold 14px 黑体;"
                              "color: #eeeeee;"
                              "}"
                              "#notify-body{"
                              "font: 12px 黑体;"
                              "color: #dddddd;"
                              "}"
                              "#notify-close-btn{ "
                              "border: 0;"
                              "color: #999999;"
                              "}"
                              "#notify-close-btn:hover{ "
                              "background: #444444;"
                              "}", "black");
        // connect 连接 起来 如果点击了 消息通知 之后
        QObject::connect(notify, &NotifyManager::notifyDetail, [&](const QVariantMap &data)
        {
            this->Qmessagebox_Detail(("新消息"),data.value("title").toString(),data.value("body").toString());

        });
        // 初始化测试
#ifdef Debug
        int count = 1;
        QString text = g_notifies[rand()%g_notifies.size()];
        for(int i = 0;i<9;i++)
        {
            notify->notify(QStringLiteral("新消息%1").arg(count++), text);
        }
#endif


}

void foryouos::Qmessagebox_Detail(QString title, QString log, QString details)
{
    QMessageBox msgbox(QMessageBox::Information, title, log);
    // 涉及Detail的详细信息
    msgbox.setDetailedText(details);
    // msgbox.findChild<QDialogButtonBox*>()->setMinimumWidth(500);
    msgbox.exec();
}

void foryouos::Main_Slide_Hide_Display_Control()
{
    G_initialRightWidgetWidth = ui->Right_Main_Widget->width();
    //qDebug() << "动画开始时的 Right_Main_Widget 宽度:" << G_initialRightWidgetWidth;
    //首先判断 当前侧边栏的状态
    if(G_Main_Slide_Status) //打开状态呢
    {
        // 关闭侧边栏
        MainpropertyAnimation->setStartValue(QPoint(0, 0));
        MainpropertyAnimation->setEndValue(QPoint(-ui->sideBar->width(), 0));
    }
    else
    {
        //打开侧边栏
        ui->sideBar->setVisible(true); // 打开要立即
        MainpropertyAnimation->setStartValue(QPoint(-ui->sideBar->width(), 0)); //从负左边即进入隐藏区域
        MainpropertyAnimation->setEndValue(QPoint(0, 0));
    }
    //开启侧边栏移动
    MainpropertyAnimation->start();
}






