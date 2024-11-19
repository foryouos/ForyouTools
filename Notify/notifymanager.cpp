#include "notifymanager.h"
#include "notifywnd.h"
#include <QApplication>
#include <QScreen>

NotifyManager::NotifyManager(QObject *parent) : QObject(parent)
{
    // 默认值
    m_maxCount = 5;
    m_displayTime = 10000;
    m_animateTime = 300;
    m_spacing = 10;
    m_notifyWndSize = QSize(300, 60);
    m_defaultIcon = ":/message.png";
    m_styleSheets["default"] =
            "#notify-background {"
            "background: white;"
            "border-radius: 4px;"
            "}"
            "#notify-title{"
            "font-weight: bold;"
            "font-size: 14px;"
            "color: #333333;"
            "}"
            "#notify-body{"
            "font-size: 12px;"
            "color: #444444;"
            "}"
            "#notify-close-btn{ "
            "border: 0;"
            "color: #999999;"
            "}"
            "#notify-close-btn:hover{ "
            "background: #cccccc;"
            "}";
    m_isShowQueueCount = true;

    setCornerMargins(10, 10);
    // 初始化 NotifyCountWnd 队列提示框，设计基础性UI
    m_notifyCount = new NotifyCountWnd(this);
}
// 调用的入口函数 传入 标题和 文本内容
void NotifyManager::notify(const QString &title, const QString &body, const QVariantMap &data)
{
    QVariantMap tmp = data;
    tmp.insert("title", title);
    tmp.insert("body", body);
    m_dataQueue.enqueue(tmp); // 进入队列当中
    showNext();// 呈现下一个数据
}

void NotifyManager::setMaxCount(int count)
{
    m_maxCount = count;
}

int NotifyManager::displayTime() const
{
    return m_displayTime;
}

void NotifyManager::setDisplayTime(int displayTime)
{
    m_displayTime = displayTime;
}

int NotifyManager::animateTime() const
{
    return m_animateTime;
}

void NotifyManager::setAnimateTime(int animateTime)
{
    m_animateTime = animateTime;
}

int NotifyManager::spacing() const
{
    return m_spacing;
}

void NotifyManager::setSpacing(int spacing)
{
    m_spacing = spacing;
}

QPoint NotifyManager::cornerPos() const
{
    return m_cornerPos;
}
// 设置边沿距离:
// right 指定通知窗口与屏幕右边缘的距离(边距)
// bottom: 指定通知窗口与屏幕低边缘的距离
void NotifyManager::setCornerMargins(int right, int bottom)
{
    // 获取主屏幕可用区域
    QRect desktopRect = QApplication::primaryScreen()->availableGeometry();
    // 获取右下角的坐标
    QPoint bottomRignt = desktopRect.bottomRight();
    //计算通知位置
    m_cornerPos = QPoint(bottomRignt.x() - right, bottomRignt.y() - bottom);
}

QSize NotifyManager::notifyWndSize() const
{
    return m_notifyWndSize;
}

void NotifyManager::setNotifyWndSize(int width, int height)
{
    m_notifyWndSize = QSize(width, height);
}

QString NotifyManager::defaultIcon() const
{
    return m_defaultIcon;
}

void NotifyManager::setDefaultIcon(const QString &defaultIcon)
{
    m_defaultIcon = defaultIcon;
}

QString NotifyManager::styleSheet(const QString &theme) const
{
    if (!m_styleSheets.contains(theme)) return m_styleSheets.value("default");
    return m_styleSheets.value(theme);
}

void NotifyManager::setStyleSheet(const QString &styleSheet, const QString &theme)
{
    m_styleSheets[theme] = styleSheet;
}

void NotifyManager::setShowQueueCount(bool isShowQueueCount)
{
    m_isShowQueueCount = isShowQueueCount;
    if (!m_isShowQueueCount) m_notifyCount->showArranged(0);
}
// 呈现数据 逐步
void NotifyManager::showNext()
{
    // 如果当前的数据 操作设定的预定义最大值 在最上角呈现总数
    if (m_notifyList.size() >= m_maxCount || m_dataQueue.isEmpty())
    {
        showQueueCount();
        return;
    }
    // 申请一个新的提示框进行呈现
    NotifyWnd *notify = new NotifyWnd(this);
    m_notifyList.append(notify); // 加入到提示框列表
    notify->showArranged(m_notifyList.size());//相识排列
    notify->setData(m_dataQueue.dequeue());// 从队列中取出数据 标题详细信息等，用户点击之后也会将对应的详细信息传出去
    // 呈现队列总数
    showQueueCount();

    // 当当前提示框销毁后的处理
    connect(notify, &QObject::destroyed, this, [notify, this](){
        int index = m_notifyList.indexOf(notify);
        m_notifyList.removeAt(index);
        for (; index<m_notifyList.size(); index++)
            m_notifyList[index]->showArranged(index+1);
        // 定时延时之后 点击下一个
        QTimer::singleShot(m_animateTime, this, [this](){
            showNext();
        });
    });
    // 提示框窗体，如果被点击之后，提示框销毁，发送输出，前端可以通过弹窗的形式读取 提示框中的详细信息
    connect(notify, &ArrangedWnd::clicked, this, [notify, this](){
        notify->deleteLater();
        QVariantMap data = notify->data();
        QTimer::singleShot(0, this, [this, data](){
            emit notifyDetail(data); // 保证窗口先销毁，避免模式窗口阻塞事件
        });
    });

    connect(notify, &ArrangedWnd::rclicked, this, [notify](){
        notify->deleteLater();
    });
}
//呈现 队列 总数
void NotifyManager::showQueueCount()
{
    if (!m_isShowQueueCount) return;
    if (!m_dataQueue.isEmpty())
    {
        m_notifyCount->showArranged(m_maxCount+1);
        m_notifyCount->setCount(m_dataQueue.size());
    }
    else m_notifyCount->showArranged(0);
}
