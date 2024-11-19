#include "notifywnd.h"
#include "notifymanager.h"
#include <QBoxLayout>
#include <QGraphicsDropShadowEffect>
// 提示框
NotifyWnd::NotifyWnd (NotifyManager *manager, QWidget *parent)
    : ArrangedWnd(manager, parent) // 初始化基类与变量 调用了基类ArrangedWnd的构造函数，传递了manager和parent参数
{
    background = new QFrame(this);
    background->setGeometry(3, 3, width()-6, height()-6);
    background->setObjectName("notify-background");

    QHBoxLayout *mainLayout = new QHBoxLayout(background);
    QVBoxLayout *contentLayout = new QVBoxLayout();
    // 图标标题
    iconLabel = new QLabel(background);
    iconLabel->setFixedSize(40, 40);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setWordWrap(true);
    // title
    titleLabel = new QLabel(background);
    titleLabel->setObjectName("notify-title");
    // 主题
    bodyLabel = new QLabel(background);
    bodyLabel->setObjectName("notify-body");
    bodyLabel->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    bodyLabel->setWordWrap(true);

    contentLayout->addWidget(titleLabel);
    contentLayout->addWidget(bodyLabel);
    contentLayout->setStretch(1,1);

    mainLayout->addWidget(iconLabel);
    mainLayout->addLayout(contentLayout);
    mainLayout->setAlignment(iconLabel, Qt::AlignTop);
    // 提示框右上角 的 关闭按钮
    closeBtn = new QPushButton("×", background);
    closeBtn->setObjectName("notify-close-btn");
    closeBtn->setFixedSize(24, 24);
    closeBtn->move(background->width() - closeBtn->width(), 0); // 移动位置
    connect(closeBtn, &QPushButton::clicked, this, &QObject::deleteLater);// 点击之后
    // 设置样式
    setStyleSheet(m_manager->styleSheet());

    // 边框阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置阴影偏移
    shadow->setBlurRadius(5);  //设置模糊半径，产生一个阴影效果
    background->setGraphicsEffect(shadow);

    // 连接信号 当提示框的 能否可见 发生改变之后
    connect(this, &ArrangedWnd::visibleChanged, [this](bool visible){
        if (visible)
        {
            int displayTime = m_data.value("displayTime", m_manager->displayTime()).toInt();
            QTimer::singleShot(displayTime, this, [this](){
                showArranged(0);
            });
        }
        else deleteLater();
    });
}

QVariantMap NotifyWnd::data() const
{
    return m_data;
}

// 需显示后调用
void NotifyWnd::setData(const QVariantMap &data)
{
    m_data = data;

    QPixmap icon;
    QVariant iconv = data.value("icon");
    if (iconv.type() == QVariant::Pixmap) icon = iconv.value<QPixmap>();
    if (iconv.type() == QVariant::String) icon = QPixmap(iconv.toString());
    else icon = QPixmap(m_manager->defaultIcon());
    icon = icon.scaled(QSize(32, 32), Qt::KeepAspectRatio);
    iconLabel->setPixmap(icon);

    QString title = data.value("title").toString();
    titleLabel->setText(title);

    // 计算可显示行数及长度
    QString body = m_data.value("body").toString();
    QSize s1 = bodyLabel->size();
    QSize s2 = bodyLabel->fontMetrics().size(Qt::TextSingleLine, body);
    int linecount = s1.height()/s2.height();
    int charcount = qFloor(1.0*body.size()*s1.width()/s2.width()) * linecount;
    QString bodyElid = charcount > body.size() ? body : (body.left(charcount-1)+"…");
    bodyLabel->setText(bodyElid);

    if (data.contains("styleSheet"))
        setStyleSheet(data.value("styleSheet").toString());
    else if (data.contains("theme"))
        setStyleSheet(m_manager->styleSheet(data.value("theme").toString()));
}

NotifyCountWnd::NotifyCountWnd(NotifyManager *manager, QWidget *parent)
    : ArrangedWnd(manager, parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents, true);// 设置背景透明 且空间不接受鼠标事件
    // 创建窗体所需空间
    iconLabel = new QLabel(this);
    iconLabel->setFixedSize(40, 40);
    iconLabel->setAlignment(Qt::AlignCenter);

    countLabel = new QLabel(this);
    countLabel->setObjectName("notify-count");
    countLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(iconLabel);
    mainLayout->addWidget(countLabel);

    // 文字阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(2, 2);  //设置阴影偏移 向右下方偏移2 像素
    shadow->setBlurRadius(5); //设置模糊半径，产生一个阴影效果
    setGraphicsEffect(shadow);

    setStyleSheet("#notify-count {"
                  "font: 20px Verdana;"
                  "color: #dd424d;"
                  "}");
    // 获取默认UI
    QPixmap icon = QPixmap(m_manager->defaultIcon());
    icon = icon.scaled(QSize(32, 32), Qt::KeepAspectRatio); //对UI尺寸进行方法 并保存比例
    iconLabel->setPixmap(icon);
    //设置隐藏呈现渐进效果
    flickerAnim = new QPropertyAnimation(this, "windowOpacity", this);
    flickerAnim->setStartValue(1);//开始时
    flickerAnim->setKeyValueAt(0.25, 0.1);// 当动画运行到25%时，窗口透明度将变为0.1(相对透明)
    flickerAnim->setKeyValueAt(0.5, 1);// 当运行到50%时透明度恢复为1(完全不透明)
    flickerAnim->setEndValue(1);//结束时完全不透明
    flickerAnim->setDuration(2000);
    flickerAnim->setLoopCount(-1);

    connect(this, &ArrangedWnd::visibleChanged, [this](bool visible){
        if (visible) flickerAnim->start();
        else flickerAnim->stop();
    });
}

void NotifyCountWnd::setCount(int count)
{
    countLabel->setNum(count); // 用于将数字转换为字符串并显示在标签上，特别适合用于显示整数类型的值
}
