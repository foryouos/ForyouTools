#include "colorwidget.h"
#include "ui_colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ColorWidget)
{
    ui->setupUi(this);
}

ColorWidget::~ColorWidget()
{
    delete ui;
}
