/********************************************************************************
** Form generated from reading UI file 'foryouos.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORYOUOS_H
#define UI_FORYOUOS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_foryouos
{
public:
    QAction *ChineseColor;
    QAction *Mainaction;
    QAction *ToDoaction;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *Main_Widget;
    QHBoxLayout *horizontalLayout;
    QWidget *sideBar;
    QGridLayout *gridLayout_2;
    QToolButton *ChineseColorBtn;
    QToolButton *ToDoactionBtn;
    QToolButton *MainactionBtn;
    QSpacerItem *verticalSpacer;
    QStackedWidget *MainStackWidget;
    QWidget *Main_Page;
    QLabel *label;
    QGroupBox *groupBox;
    QWidget *ChineseColorPage;
    QGridLayout *gridLayout;
    QFrame *frame;
    QWidget *TODOPage;
    QVBoxLayout *verticalLayout;
    QWidget *ToDoWidget;
    QGridLayout *gridLayout_3;
    QWidget *tolisttitleWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QListView *ToDoList;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QToolBar *toolBar;

    void setupUi(QMainWindow *foryouos)
    {
        if (foryouos->objectName().isEmpty())
            foryouos->setObjectName("foryouos");
        foryouos->resize(856, 643);
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font.setPointSize(10);
        foryouos->setFont(font);
        ChineseColor = new QAction(foryouos);
        ChineseColor->setObjectName("ChineseColor");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/photo/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        ChineseColor->setIcon(icon);
        Mainaction = new QAction(foryouos);
        Mainaction->setObjectName("Mainaction");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/photo/Tools.png"), QSize(), QIcon::Normal, QIcon::Off);
        Mainaction->setIcon(icon1);
        Mainaction->setMenuRole(QAction::MenuRole::NoRole);
        ToDoaction = new QAction(foryouos);
        ToDoaction->setObjectName("ToDoaction");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/photo/-to-do.png"), QSize(), QIcon::Normal, QIcon::Off);
        ToDoaction->setIcon(icon2);
        ToDoaction->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(foryouos);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        Main_Widget = new QWidget(centralwidget);
        Main_Widget->setObjectName("Main_Widget");
        horizontalLayout = new QHBoxLayout(Main_Widget);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sideBar = new QWidget(Main_Widget);
        sideBar->setObjectName("sideBar");
        sideBar->setMaximumSize(QSize(16777215, 16777215));
        sideBar->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background-color: rgb(228, 228, 228);\n"
"}"));
        gridLayout_2 = new QGridLayout(sideBar);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        ChineseColorBtn = new QToolButton(sideBar);
        ChineseColorBtn->setObjectName("ChineseColorBtn");
        ChineseColorBtn->setMinimumSize(QSize(76, 80));
        ChineseColorBtn->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244 */\n"
"QToolButton{   \n"
"	border-top: 3px outset transparent;\n"
"	border-bottom: 7px outset transparent;\n"
"	border-right: 3px outset transparent;\n"
"	border-left: 3px outset transparent;\n"
"    min-width: 70px;\n"
"    min-height: 70px;\n"
"	background-color: rgb(228, 228, 228);\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QToolButton:hover{\n"
"	background-color: rgb(205, 205, 205);\n"
"}\n"
"\n"
"/* \347\202\271\345\207\273\345\222\214\346\214\211\344\270\213 */\n"
"QToolButton:pressed,QToolButton:checked{\n"
"	border-left: 3px outset rgb(93, 95, 97);\n"
"	background-color: rgb(246, 246, 246);	\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: navy; /* make the default button prominent */\n"
"}\n"
"\n"
""));
        ChineseColorBtn->setIcon(icon);
        ChineseColorBtn->setIconSize(QSize(48, 48));
        ChineseColorBtn->setCheckable(true);
        ChineseColorBtn->setAutoExclusive(true);
        ChineseColorBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(ChineseColorBtn, 2, 0, 1, 1);

        ToDoactionBtn = new QToolButton(sideBar);
        ToDoactionBtn->setObjectName("ToDoactionBtn");
        ToDoactionBtn->setMinimumSize(QSize(76, 80));
        ToDoactionBtn->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244 */\n"
"QToolButton{   \n"
"	border-top: 3px outset transparent;\n"
"	border-bottom: 7px outset transparent;\n"
"	border-right: 3px outset transparent;\n"
"	border-left: 3px outset transparent;\n"
"    min-width: 70px;\n"
"    min-height: 70px;\n"
"	background-color: rgb(228, 228, 228);\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QToolButton:hover{\n"
"	background-color: rgb(205, 205, 205);\n"
"}\n"
"\n"
"/* \347\202\271\345\207\273\345\222\214\346\214\211\344\270\213 */\n"
"QToolButton:pressed,QToolButton:checked{\n"
"	border-left: 3px outset rgb(93, 95, 97);\n"
"	background-color: rgb(246, 246, 246);	\n"
"}\n"
""));
        ToDoactionBtn->setIcon(icon2);
        ToDoactionBtn->setIconSize(QSize(48, 48));
        ToDoactionBtn->setCheckable(true);
        ToDoactionBtn->setAutoExclusive(true);
        ToDoactionBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(ToDoactionBtn, 1, 0, 1, 1);

        MainactionBtn = new QToolButton(sideBar);
        MainactionBtn->setObjectName("MainactionBtn");
        MainactionBtn->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244 */\n"
"QToolButton{   \n"
"	border-top: 3px outset transparent;\n"
"	border-bottom: 7px outset transparent;\n"
"	border-right: 3px outset transparent;\n"
"	border-left: 3px outset transparent;\n"
"    min-width: 70px;\n"
"    min-height: 70px;\n"
"	background-color: rgb(228, 228, 228);\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QToolButton:hover{\n"
"	background-color: rgb(205, 205, 205);\n"
"}\n"
"\n"
"/* \347\202\271\345\207\273\345\222\214\346\214\211\344\270\213 */\n"
"QToolButton:pressed,QToolButton:checked{\n"
"	border-left: 3px outset rgb(93, 95, 97);\n"
"	background-color: rgb(246, 246, 246);	\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: navy; /* make the default button prominent */\n"
"}\n"
"\n"
""));
        MainactionBtn->setIcon(icon1);
        MainactionBtn->setIconSize(QSize(48, 48));
        MainactionBtn->setCheckable(true);
        MainactionBtn->setAutoExclusive(true);
        MainactionBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(MainactionBtn, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 288, QSizePolicy::Policy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);


        horizontalLayout->addWidget(sideBar);

        MainStackWidget = new QStackedWidget(Main_Widget);
        MainStackWidget->setObjectName("MainStackWidget");
        Main_Page = new QWidget();
        Main_Page->setObjectName("Main_Page");
        label = new QLabel(Main_Page);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 10, 401, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Harrington")});
        font1.setPointSize(36);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        groupBox = new QGroupBox(Main_Page);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(210, 140, 301, 361));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 127);"));
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainStackWidget->addWidget(Main_Page);
        ChineseColorPage = new QWidget();
        ChineseColorPage->setObjectName("ChineseColorPage");
        gridLayout = new QGridLayout(ChineseColorPage);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(ChineseColorPage);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        gridLayout->addWidget(frame, 0, 0, 1, 1);

        MainStackWidget->addWidget(ChineseColorPage);
        TODOPage = new QWidget();
        TODOPage->setObjectName("TODOPage");
        verticalLayout = new QVBoxLayout(TODOPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ToDoWidget = new QWidget(TODOPage);
        ToDoWidget->setObjectName("ToDoWidget");
        ToDoWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 1px solid #ccccd6;"));
        gridLayout_3 = new QGridLayout(ToDoWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        tolisttitleWidget = new QWidget(ToDoWidget);
        tolisttitleWidget->setObjectName("tolisttitleWidget");
        tolisttitleWidget->setStyleSheet(QString::fromUtf8("border: 0px solid #ccccd6;"));
        horizontalLayout_2 = new QHBoxLayout(tolisttitleWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_3 = new QPushButton(tolisttitleWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(40, 40));
        pushButton_3->setMaximumSize(QSize(40, 40));
        pushButton_3->setStyleSheet(QString::fromUtf8("image: url(:/photo/Tools.png);"));

        horizontalLayout_2->addWidget(pushButton_3);

        label_3 = new QLabel(tolisttitleWidget);
        label_3->setObjectName("label_3");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Harrington")});
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setItalic(true);
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("color:rgb(80, 121, 255);\n"
"border: 0px solid #ccccd6;\n"
""));

        horizontalLayout_2->addWidget(label_3);

        pushButton_2 = new QPushButton(tolisttitleWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(40, 40));
        pushButton_2->setMaximumSize(QSize(40, 40));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:1px solid #ccccd6;\n"
"image: url(:/photo/permission.png);"));

        horizontalLayout_2->addWidget(pushButton_2);


        gridLayout_3->addWidget(tolisttitleWidget, 0, 0, 1, 3);

        frame_2 = new QFrame(ToDoWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("border: 0px solid #ccccd6;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        ToDoList = new QListView(frame_2);
        ToDoList->setObjectName("ToDoList");
        ToDoList->setStyleSheet(QString::fromUtf8("border: 0px solid #ccccd6;"));

        verticalLayout_2->addWidget(ToDoList);

        widget_2 = new QWidget(frame_2);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 40));
        widget_2->setStyleSheet(QString::fromUtf8("border: 1px solid #ccccd6;\n"
"background-color: rgb(0, 170, 127);"));
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(0, 0));
        pushButton->setMaximumSize(QSize(50, 50));
        pushButton->setStyleSheet(QString::fromUtf8("border: 0px solid #ccccd6;\n"
"border-top-right-radius:0px;\n"
"border-bottom-right-radius:0px;"));
        QIcon icon3(QIcon::fromTheme(QString::fromUtf8("QIcon::ThemeIcon::DocumentOpenRecent")));
        pushButton->setIcon(icon3);

        horizontalLayout_4->addWidget(pushButton);

        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setStyleSheet(QString::fromUtf8("border: 0px solid #ccccd6;\n"
"border-top-left-radius:0px;\n"
"border-bottom-left-radius:0px;"));

        horizontalLayout_4->addWidget(lineEdit);


        verticalLayout_2->addWidget(widget_2);


        gridLayout_3->addWidget(frame_2, 1, 0, 1, 1);


        verticalLayout->addWidget(ToDoWidget);

        MainStackWidget->addWidget(TODOPage);

        horizontalLayout->addWidget(MainStackWidget);


        horizontalLayout_3->addWidget(Main_Widget);

        foryouos->setCentralWidget(centralwidget);
        toolBar = new QToolBar(foryouos);
        toolBar->setObjectName("toolBar");
        foryouos->addToolBar(Qt::RightToolBarArea, toolBar);

        toolBar->addAction(Mainaction);
        toolBar->addAction(ToDoaction);
        toolBar->addAction(ChineseColor);

        retranslateUi(foryouos);

        MainStackWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(foryouos);
    } // setupUi

    void retranslateUi(QMainWindow *foryouos)
    {
        foryouos->setWindowTitle(QCoreApplication::translate("foryouos", "foryouos", nullptr));
        ChineseColor->setText(QCoreApplication::translate("foryouos", "\344\270\255\345\233\275\344\274\240\347\273\237\350\211\262", nullptr));
        Mainaction->setText(QCoreApplication::translate("foryouos", "\351\246\226\351\241\265", nullptr));
#if QT_CONFIG(tooltip)
        Mainaction->setToolTip(QCoreApplication::translate("foryouos", "\350\277\233\345\205\245\351\246\226\351\241\265", nullptr));
#endif // QT_CONFIG(tooltip)
        ToDoaction->setText(QCoreApplication::translate("foryouos", "\344\273\243\345\212\236\344\272\213\351\241\271", nullptr));
#if QT_CONFIG(tooltip)
        ToDoaction->setToolTip(QCoreApplication::translate("foryouos", "\344\273\243\345\212\236\344\272\213\351\241\271", nullptr));
#endif // QT_CONFIG(tooltip)
        ChineseColorBtn->setText(QCoreApplication::translate("foryouos", "\344\274\240\347\273\237\350\211\262", nullptr));
        ToDoactionBtn->setText(QCoreApplication::translate("foryouos", "ToList", nullptr));
        MainactionBtn->setText(QCoreApplication::translate("foryouos", "\351\246\226\351\241\265", nullptr));
        label->setText(QCoreApplication::translate("foryouos", "Botton", nullptr));
        groupBox->setTitle(QCoreApplication::translate("foryouos", "\346\234\252\345\256\214\346\210\220\344\273\273\345\212\241", nullptr));
        pushButton_3->setText(QCoreApplication::translate("foryouos", "\351\246\226", nullptr));
        label_3->setText(QCoreApplication::translate("foryouos", "Better to do than to say!", nullptr));
        pushButton_2->setText(QString());
        pushButton->setText(QString());
        toolBar->setWindowTitle(QCoreApplication::translate("foryouos", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class foryouos: public Ui_foryouos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORYOUOS_H
