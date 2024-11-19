#include "arrangedwnd.h"
#include "notifymanager.h"
//对QObject的属性进行动画效果，它们使用QPropertyAnimation来实现属性值的平滑过渡
static QPropertyAnimation *propertyAnimationOnTarget(QObject *target, const QByteArray &propertyName, const QVariant &endValue, int duration)
{
    //需要动画化的属性名称，通常是目标对象的可动画属性名(如位置，透明度)
    QPropertyAnimation *animation = new QPropertyAnimation(target, propertyName, target);
    animation->setStartValue(target->property(propertyName));
    animation->setEndValue(endValue);
    animation->setDuration(duration);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    return animation;
}

template<typename func>
static inline void propertyAnimationOnTarget(QObject *target, const QByteArray &propertyName, const QVariant &endValue, int duration, func onFinished)
{
    QPropertyAnimation *animation = propertyAnimationOnTarget(target, propertyName, endValue, duration);
    QObject::connect(animation, &QPropertyAnimation::finished, target, onFinished);
}

ArrangedWnd::ArrangedWnd (NotifyManager *manager, QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint)
{
    m_manager = manager;
    m_posIndex = 0;
    // 不使用系统的背景绘制，使窗体不会被系统默认背景颜色影响
    setAttribute(Qt::WA_NoSystemBackground, true);
    // 设置背景透明
    setAttribute(Qt::WA_TranslucentBackground, true);
    // 固定大小
    setFixedSize(manager->notifyWndSize());

    connect(manager, &QObject::destroyed, this, &QObject::deleteLater);
}
// 鼠标按压事件 点击左键 点击右键
void ArrangedWnd::mousePressEvent(QMouseEvent *event)
{
    // 当检测到 鼠标点击事件 之后，发送点击事件，NotifyManager会对点击事件进行处理 清楚
    switch (event->button())
    {
    case Qt::LeftButton: emit clicked(); break;
    case Qt::RightButton: emit rclicked(); break;
    default: break;
    }
}
// 处理显示排列的顺序
void ArrangedWnd::showArranged(int posIndex)
{
    if (m_posIndex == posIndex) return;
    m_posIndex = posIndex;
    if (posIndex <= 0) // 隐藏
    {
        if (!isVisible()) return;
        propertyAnimationOnTarget(this, "windowOpacity", 0, m_manager->animateTime(), [this](){
            hide();
            emit visibleChanged(false);
        });
        return;
    }

    // 计算提醒框的位置
    QSize wndsize = m_manager->notifyWndSize(); // setNotifyWndSize 设定的值 包含宽度和高度
    // 计算偏移值 高度*现在的索引 + 浮动提示框之前 的 间隔默认值为 10 * 索引
    QSize offset = QSize(wndsize.width(), wndsize.height()*posIndex + m_manager->spacing()*(posIndex-1));
    // 计算坐标
    QPoint pos = m_manager->cornerPos() - QPoint(offset.width(), offset.height());

    if (!isVisible()) // 显示
    {
        show();
        move(pos);
        setWindowOpacity(0);
        propertyAnimationOnTarget(this, "windowOpacity", 1, m_manager->animateTime(), [this](){
            emit visibleChanged(true);
        });
    }
    else // 移动位置
    {
        propertyAnimationOnTarget(this, "pos", pos, m_manager->animateTime());
    }
}


