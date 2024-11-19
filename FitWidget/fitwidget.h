#ifndef FITWIDGET_H
#define FITWIDGET_H

#include <QWidget>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QDateTime>

// QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui {
class FitWidget;
}
QT_END_NAMESPACE

class FitWidget : public QWidget
{
    Q_OBJECT

public:
    FitWidget(QWidget *parent = nullptr);
    ~FitWidget();
public slots:
    // 向表格中 添加数据
    void Add_Fit_Data(QDateTime time,float width,float km);

private slots:
    // 体重数据表格 初始化
    void Fit_Chart_Init();
    void CreateBMIAxisWithColorRanges();
    void on_Add_Data_clicked();

public:
    void resizeEvent(QResizeEvent* event) override;  // 大小重述事件
private:
    Ui::FitWidget *ui;

    float m_height = 1.69f;  // 假设身高为1.70m，可以根据需求修改或传入
    // chart 图形
    QChartView* m_view = nullptr;
    QChart *m_chart = nullptr;
    QLineSeries *m_line = nullptr;  // 体重折线图
    QLineSeries *m_lineKM = nullptr;  // 体重折线图

    QDateTimeAxis  *m_axisX = nullptr;

};
#endif // FITWIDGET_H
