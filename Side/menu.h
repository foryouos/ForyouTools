//  /*******************************************************************************
//  * Author      :  ChuanQin Yu                                                   *
//  * Copyright   :  (c) ChuanQin Yu 2023-2024                                     *
//  * mail        :  ycq1014@gmail.com                                             *
//  * License     :  http://www.boost.org/LICENSE_1_0.txt                          *
//  ********************************************************************************

#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QtWidgets>

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);

private:
    // 头部标题 菜单栏最小化按钮
    QLabel *titleLabel = new QLabel;                                  // 标题
    QPushButton *minimizeButton = new QPushButton;                    // 最小化按钮

    QButtonGroup buttonGroup;                                         // 按钮组

    QPushButton* newPage1Btn = new QPushButton;                       // 新建页面1按钮
    QPushButton* newPage2Btn = new QPushButton;                       // 新建页面2按钮
    QPushButton* newPage3Btn = new QPushButton;                       // 新建页面3按钮

    bool isMinimized = false;                                        // 是否最小化

    void init();

    // 设置pushbutton的各项参数, 文字, icon
    static void setPushButton(QPushButton *button, const QString& url, const QString& text);
    static void setPushButton(QPushButton *button, const QString& text);

    // 设置菜单栏最小化与正常的状态
    void setMenu(bool isMini);


signals:
    void buttonClicked(int buttonId);                               // 带有按钮标识符的信号

public slots:
    void onButtonClicked(int id);
    void onMinimizeButtonClicked();
};

#endif //SIDEBARWIDGET_H
