#ifndef TODOLISTWIDGET_H
#define TODOLISTWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
QT_BEGIN_NAMESPACE
namespace Ui {
class ToDoListWidget;
}
QT_END_NAMESPACE

class ToDoListWidget : public QWidget
{
    Q_OBJECT

public:
    ToDoListWidget(QWidget *parent = nullptr);
    ~ToDoListWidget();

private slots:
    // 任务清单任务栏初始化
    void ToDoList_Side_Init();
    // 调用呈现ToList任务清单侧边栏的控制
    void ToDoListDetail_Side_DisPlay_Control(bool display);

private:
    Ui::ToDoListWidget *ui;
    QPropertyAnimation *ToListpropertyAnimation = nullptr;

    int G_ToListDetail_Slide_Width = 0; // 存储 详细侧边栏的初始宽度

    //全局 ToList 详细栏状态
    bool G_ToListDetail_Slide_Status = true;
};
#endif // TODOLISTWIDGET_H
