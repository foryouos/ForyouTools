#include "foryouos.h"
#include "ui_foryouos.h"

foryouos::foryouos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::foryouos)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/photo/Tools.png"));
    setWindowTitle("Foryouos 工具箱");
    // 初始化ACtion事件
    this->UIACtion_Init();
    // 初始化 Foryouos控制器
    this->ForyouControlInit();

    //首次呈现在首页
    ui->MainStackWidget->setCurrentIndex(0);

    // 初始化Notify
    this->Notify_init();

    // // 设置窗口最小大小为1000x700
    // this->setMinimumSize(QSize(1000, 700));
    // // 启用样式表对窗口背景的控制
    // this->setAttribute(Qt::WA_StyledBackground, true);
    // // 设置窗口标题为"musicPlayer"
    // this->setWindowTitle(tr("demo_menu"));
    // // 设置窗口图标
    // this->setWindowIcon(QIcon(QString::fromUtf8(":/res/logo.svg")));
    // // 设置窗口的样式表为蓝色背景
    // QString styleSheet = QString("background-color: #2177B8");
    // this->setStyleSheet(styleSheet);




}

foryouos::~foryouos()
{
    // TODO:清理所有初始化的资源
    if(m_webView != nullptr)
    {
        m_webView->close();
        delete m_webView;
        m_webView = nullptr;
    }
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

    //TODO:初始化Button
    connect(ui->MainactionBtn, &QPushButton::clicked,this,[&](){ui->MainStackWidget->setCurrentIndex(0);});
    connect(ui->ChineseColorBtn, &QPushButton::clicked,this,[&]()
            {
                this->Chinese_Web_Page_Init();
                ui->MainStackWidget->setCurrentIndex(1);
            });
    connect(ui->ToDoactionBtn, &QPushButton::clicked,this,[&](){ui->MainStackWidget->setCurrentIndex(2);});
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
    if(m_webView == nullptr)
    {
        m_webView = new QWebEngineView(this);
        QStackedLayout *layout =new QStackedLayout(ui->frame);//1、引入布局，用于存放QWebengineView；
        //2、指定的父项ui->frame是在ui界面引入了一个QFrame,用于加载QWebengineView。
        ui->frame->setLayout(layout); //设置frame的布局为layout。
        layout->addWidget(m_webView);
        m_webView->load(G_Chinese_Color_Url);
    }
    else
    {
        m_webView->reload();
    }

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
        QObject::connect(notify, &NotifyManager::notifyDetail, [](const QVariantMap &data)
                         {
                             QMessageBox msgbox(QMessageBox::Information, QStringLiteral("新消息"), data.value("title").toString());
                             // 涉及Detail的详细信息
                             msgbox.setDetailedText(data.value("body").toString());
                             // msgbox.findChild<QDialogButtonBox*>()->setMinimumWidth(500);
                             msgbox.exec();
                         });
        // 初始化测试
        int count = 1;
        QString text = g_notifies[rand()%g_notifies.size()];
        notify->notify(QStringLiteral("新消息%1").arg(count++), text);

}

QSplitter *foryouos::createVerticalSplitter(QWidget *parent, QWidget *content1, QWidget *content2, Qt::Orientation orientation, int size1, int size2)
{
    // 创建右边页面的QSplitter控件
    auto *splitter = new QSplitter(orientation, parent);
    splitter->addWidget(content1);                          // 添加左侧边栏到分割窗口中
    splitter->addWidget(content2);                          // 添加内容容器到分割窗口中
    // 设置初始高度
    splitter->setSizes(QList<int>() << size1 << size2);
    // 获取分割窗口的句柄
    QSplitterHandle *splitterHandle1 = splitter->handle(1);  // 获取右侧部分的句柄
    // 设置句柄样式，并禁用拖动功能
    splitterHandle1->setEnabled(false);

    return splitter;
}



