#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ColorWidget;
}
QT_END_NAMESPACE

class ColorWidget : public QWidget
{
    Q_OBJECT

public:
    ColorWidget(QWidget *parent = nullptr);
    ~ColorWidget();

private:
    Ui::ColorWidget *ui;
};
#endif // COLORWIDGET_H
