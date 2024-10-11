#ifndef NOTIFYMANAGER_H
#define NOTIFYMANAGER_H

#include <QtCore>

class NotifyWnd;
class NotifyCountWnd;
class NotifyManager : public QObject
{
    Q_OBJECT

public:
    explicit NotifyManager( QObject *parent = 0);

    void notify(const QString &title, const QString &body, const QVariantMap &data = QVariantMap());

    void setMaxCount(int count); // 设置 同时呈现 浮动提示框的数量 默认为 5

    int displayTime() const;
    void setDisplayTime(int displayTime); // 设置 浮动提示框 呈现的时间  默认值为 10000  即 10秒

    int animateTime() const;
    void setAnimateTime(int animateTime); // 设置 浮动提示框 从出现到呈现，从呈现时间到消失的逐步变化的是时间 默认值为300ms

    int spacing() const;
    void setSpacing(int spacing); // 设置 浮动提示框之前 的 间隔默认值为 10

    QPoint cornerPos() const;
    void setCornerMargins(int right, int bottom);  // 设置 浮动提示框 圆角 默认为 10

    QSize notifyWndSize() const;
    void setNotifyWndSize(int width, int height);  // 设置 浮动提示框的 尺寸 宽度和高度

    QString defaultIcon() const;
    void setDefaultIcon(const QString &defaultIcon);  // 设置浮动提示框默认的 ICON 上边和左边的 Logo

    QString styleSheet(const QString &theme = "default") const;
    void setStyleSheet(const QString &styleSheet, const QString &theme = "default"); // 设置样式

    void setShowQueueCount(bool isShowQueueCount); // 如果提示框数据 超过设置的最大值，是否在上方呈现 未曾想的总数

signals:
    void notifyDetail(const QVariantMap &data);

private:
    void showNext();
    void showQueueCount();

    QQueue<QVariantMap> m_dataQueue;
    QList<NotifyWnd *> m_notifyList;
    NotifyCountWnd *m_notifyCount;

    int m_maxCount;
    bool m_isShowQueueCount;
    int m_displayTime;
    int m_animateTime;
    int m_spacing;
    QPoint m_cornerPos;
    QSize m_notifyWndSize;
    QString m_defaultIcon;
    QMap<QString, QString> m_styleSheets;
};

#endif // NOTIFYMANAGER_H
