//  /*******************************************************************************
//  * Author      :  ChuanQin Yu                                                   *
//  * Copyright   :  (c) ChuanQin Yu 2023-2024                                     *
//  * mail        :  ycq1014@gmail.com                                             *
//  * License     :  http://www.boost.org/LICENSE_1_0.txt                          *
//  ********************************************************************************

#include "menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumWidth(200);
    this->setMaximumWidth(300);
    this->setAttribute(Qt::WA_StyledBackground, true);  // 启用样式表对窗口背景的控制

    // 设置样式表，包括背景颜色
    QString styleSheet = "background-color: #A0A083;"
                         "border-radius: 7px;";
    this->setStyleSheet(styleSheet);

    init();

    // 连接信号与槽，当最小化按钮被点击时，发送信号
    connect(minimizeButton, &QPushButton::clicked, this, &Menu::onMinimizeButtonClicked);

    // 连接信号与槽，当按钮选中时调用自定义的槽函数
    connect(&buttonGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &Menu::onButtonClicked);
}

void Menu::init()
{
    auto *layout = new QVBoxLayout;

    // 设置标题
    titleLabel->setText(tr("     menu"));
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFixedHeight(40);
    titleLabel->setStyleSheet("background-color: #A0A083;"
                             "border-radius: 7px;");
    titleLabel->setStyleSheet("color: white;");
    titleLabel->setFont(QFont("Microsoft YaHei", 12, QFont::Bold));

    // 创建最小化按钮
    minimizeButton->setFixedSize(35, 35);
    minimizeButton->setStyleSheet("background-color: #A0A083;"
                                 "border-radius: 7px;");
    setPushButton(minimizeButton, QString::fromUtf8(":/res/vehicle.svg"), "");
    minimizeButton->setFlat(true);

    auto *titleLayout = new QHBoxLayout;
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(minimizeButton);

    layout->addLayout(titleLayout);

    // 创建菜单栏按钮控件
    setPushButton(newPage1Btn, QString::fromUtf8(":/res/taxi.svg"), tr("First page"));
    setPushButton(newPage2Btn, QString::fromUtf8(":/res/RetroStingyCar.svg"), tr("Second page"));
    setPushButton(newPage3Btn, QString::fromUtf8(":/res/CartoonTaxi.svg"), tr("Third page"));

    // 创建按钮组
    buttonGroup.addButton(newPage1Btn, 1);
    buttonGroup.addButton(newPage2Btn, 2);
    buttonGroup.addButton(newPage3Btn, 3);

    // 使用样式表设置控件的背景透明和高度增加 字体设置
    QFont font("Microsoft YaHei", 10);              // 创建字体，指定字体名称和字体大小
    font.setPointSizeF(font.pointSizeF() * 1.25);                    // 将字体大小放大1.25倍

    foreach(QAbstractButton *b, buttonGroup.buttons()) {
        b->setStyleSheet("background-color: transparent;"
                             "opacity: 0;"
                             "border-radius: 7px;");
        // 设置按钮的高度和字体
        b->setFixedHeight(40);
        b->setFont(font);
    }

    // 设置第一个按钮为默认选中状态
    if (QAbstractButton *firstButton = buttonGroup.button(1)) {
        firstButton->setChecked(true);
        onButtonClicked(1);
    }

    // 创建布局
    layout->addWidget(newPage1Btn);
    layout->addWidget(newPage2Btn);
    layout->addWidget(newPage3Btn);

    // 添加一个竖直方向的额弹簧
    auto *spacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(spacer);
    // 设置布局
    this->setLayout(layout);
}

void Menu::onButtonClicked(int id)
{
    // 获取选中的按钮
    auto *button = qobject_cast<QPushButton*>(buttonGroup.button(id));

    // 将所有按钮的样式表恢复到初始状态
    for(QAbstractButton *b : buttonGroup.buttons()) {
        if (b != button) {
            b->setStyleSheet("background-color: transparent;"
                                "opacity: 0;"
                                "border-radius: 7px;");
        }
    }

    // 更改选中按钮的样式
    if (button) {
        button->setStyleSheet("background-color: rgba(0, 0, 0, 0.2);"
                              "border-radius: 7px;");

        emit buttonClicked(id);
    }
}

void Menu::setPushButton(QPushButton *button, const QString& url, const QString& text)
{
    // 设置按钮的文字和图标
    button->setText(text);
    QIcon icon;
    // 图标大小设置为30*30
    icon.addFile(url, QSize());
    button->setIcon(icon);
    button->setIconSize(QSize(30, 30));

    // 设置按钮光标样式
    button->setCursor(QCursor(Qt::PointingHandCursor));
}

void Menu::setPushButton(QPushButton *button, const QString& text)
{
    button->setText(text);
}

void Menu::onMinimizeButtonClicked()
{
    isMinimized = !isMinimized;
    setMenu(isMinimized);
}

void Menu::setMenu(bool isMini)
{
    // 最小化
    if (isMini)
    {
        // 设置最小宽度和最大宽度
        this->setMinimumWidth(50);
        this->setMaximumWidth(50);

        newPage1Btn->setText("");
        newPage2Btn->setText("");
        newPage3Btn->setText("");
        titleLabel->setText("");

        // 设置按钮的图标
        setPushButton(minimizeButton, QString::fromUtf8(":/res/RetroStingySUV.svg"), "");
    }
    // 正常
    else {
        // 设置最小宽度和最大宽度
        this->setMinimumWidth(200);
        this->setMaximumWidth(300);

        newPage1Btn->setText(tr("First page"));
        newPage2Btn->setText(tr("Second page"));
        newPage3Btn->setText(tr("Third page"));
        titleLabel->setText(tr("     menu"));

        setPushButton(minimizeButton, QString::fromUtf8(":/res/vehicle.svg"), "");
    }
}