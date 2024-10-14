#ifndef FORYOUOS_H
#define FORYOUOS_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>

#include "foryoucontrol.h"
#include <QWebEngineView>
#include <QPropertyAnimation>
// #include "Side/menu.h"
#include <QStackedLayout>
#include "notifymanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class foryouos; }
QT_END_NAMESPACE

class foryouos : public QMainWindow
{
    Q_OBJECT

public:
    foryouos(QWidget *parent = nullptr);
    ~foryouos() override;


private:
    Ui::foryouos *ui;

    // 调用线程 私有 函数
private slots:
    // 初始化ACtion点击 导向的窗体事件
    void UIACtion_Init();
    // 初始化按钮信号与槽函数
    void Button_Init();
    // 所有涉及侧边栏的初始化操作
    void Slide_Bar_Init();
    void ForyouControlInit();// foryouos控制线程初始化
    // 初始化中国传统色页面
    void Chinese_Web_Page_Init();
    // 右下角 弹窗通知 初始化
    void Notify_init();
    // 定义弹窗多功能应用函数
    void Qmessagebox_Detail(QString title,QString log,QString details);

    // 执行主页面侧边栏的隐藏与呈现功能
    void Main_Slide_Hide_Display_Control();



private:

private :
    QThread *mthread = nullptr;
    ForyouControl *foryoucontrol = nullptr;

    QWebEngineView *m_webView = nullptr; // 页面显示对象指针

    NotifyManager *notify = nullptr;
    QPropertyAnimation *propertyAnimation = nullptr;




    // 定义全局变量
private:
    // https://colors.ichuantong.cn/
    // https://www.zhongguose.com/#yufenhong
    QString G_Chinese_Color_Url = "https://colors.ichuantong.cn/";



    // Notify 定义其相关的全局参数，可以在此处进行更改
    QStringList g_notifies = {
        QStringLiteral("我从来不相信什么懒洋洋的自由，我向往的自由是通过勤奋和努力实现的更广阔的人生，那样的自由才是珍贵的、有价值的。"),
        QStringLiteral("我相信一万小时定律，我从来不相信天上掉馅饼的灵感和坐等的成就。"),
        QStringLiteral("做一个自由又自律的人，靠势必实现的决心认真地活着。"),
        QStringLiteral("你的脸上云淡风轻，谁也不知道你的牙咬得有多紧。"),
        QStringLiteral("你走路带着风，谁也不知道你膝盖上仍有曾摔伤的淤青。"),
        QStringLiteral("你笑得没心没肺，没人知道你哭起来只能无声落泪。"),
        QStringLiteral("要让人觉得毫不费力，只能背后极其努力。"),
        QStringLiteral("我们没有改变不了的未来，只有不想改变的过去。"),
        QStringLiteral("如果逃避眼前的现实，越是逃，就越是会陷入痛苦的境地。"),
        QStringLiteral("要有面对问题的勇气，渡过这个困境的话，应该就能一点点地解决问题。感激遇到的所有人吧。"),
        QStringLiteral("虽然晚了点，依靠自己的力量前进吧。为了开始新的人生。")
    };

    //全局侧边栏的状态
    bool G_Main_Slide_Status = true;

    // 记录但侧边栏发生变化时，右窗体的宽度
    int G_initialRightWidgetWidth; // 存储 Right_Main_Widget 的初始宽度



};
#endif // FORYOUOS_H
