#include "fitwidget.h"
#include "ui_fitwidget.h"

FitWidget::FitWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FitWidget)
{
    ui->setupUi(this);
    // 创建表格 初始化
    this->Fit_Chart_Init();

    // ui->DataTimeCombox

}

FitWidget::~FitWidget()
{
    delete ui;
}

void FitWidget::Add_Fit_Data(QDateTime time, float weight,float km)
{
    // 计算 BMI，BMI = 体重(kg) / 身高(m)^2
    float bmi = weight / (m_height * m_height);
    // 转换日期为时间戳（毫秒级）
    qreal x = static_cast<qreal>(time.toMSecsSinceEpoch());
    // 为体重数据添加点
    m_line->append(x, weight);
    m_lineKM->append(x, km);
    // qDebug()<<"添加数据为:"<<time<<bmi<<weight;
    // 更新图表（如果需要）
    // 获取 x 轴的当前范围
    // 检查 m_axisX 是否已初始化
    if (!m_axisX->min().isValid() || !m_axisX->max().isValid()) {
        // 如果 x 轴范围无效，初始化为当前时间范围
        qDebug()<<"数据为空:设置时间:"<<time;
        m_axisX->setRange(time, time);
    }
    else
    {
        QDateTime minDate = QDateTime::fromString("2024-01-01", "yyyy-MM-dd");
        QDateTime maxDate = m_axisX->max();
        // 更新 x 轴的最小最大范围
        if (time < minDate)
        {
            m_axisX->setRange(time, maxDate);  // 如果新数据时间比最小时间小，更新最小范围
        }
        else if (time > maxDate)
        {
            m_axisX->setRange(minDate, time);  // 如果新数据时间比最大时间大，更新最大范围
        }
    }
    m_view->chart()->update();  // 强制更新图表

}

void FitWidget::Fit_Chart_Init()
{
    // 创建图标视图 QChartView
    m_view=new QChartView(ui->LineWidget);
    // m_view->resize(QSize(800,600));
    // 创建图标 QChart
    m_chart=new QChart();
    m_chart->setTheme(QChart::ChartTheme::ChartThemeLight);
    // 将图标设置给图标视图
    m_view->setChart(m_chart);

    // 设置图标 标题
    // m_chart->setTitle("健康数据管理");
    // 设置X 轴
    // 生成日期时间数据，假设开始日期为 2024-01-01
    QDateTime startDate = QDateTime::fromString("2024-01-01", "yyyy-MM-dd");
    QDateTime EndDate = QDateTime::fromString("2025-01-01", "yyyy-MM-dd");
    m_axisX = new QDateTimeAxis;
    m_axisX->setFormat("yyyy-MM-dd"); // 设置日期显示格式（年-月-日）
    m_axisX->setTitleText("日期"); // 设置轴标题
    m_axisX->setTitleBrush(Qt::red); // 设置轴标题的颜色
    m_axisX->setGridLineColor(Qt::green); // 设置网格线的颜色
    m_axisX->setGridLineVisible(false); // 设置网格线是否显示
    qDebug()<<"startDate:"<<startDate;
    m_axisX->setRange(startDate,EndDate);
    // axisX->setTickCount(5); // 设置刻度的个数
    //axisX->setMinorTickCount(2); // 设置子刻度的个数
    m_axisX->setMinorGridLineVisible(false); // 设置子刻度对应的网格线是否显示
    //通过设置画笔来设置轴的颜色和粗细
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    m_axisX->setLinePen(pen);
    //把X轴添加到Qhart的底部，同样一个轴对象只能添加进去一次，再次添加就不生效
    m_chart->addAxis(m_axisX, Qt::AlignBottom);

    // 创建 左 Y轴
    QValueAxis * axisY = new QValueAxis();
    axisY->setGridLineColor(Qt::blue);
    axisY->setTitleText("体重(KG)");
    axisY->setRange(0, 200);
    axisY->setTickCount(11);
    axisY->setLabelFormat("%d");
    axisY->setGridLineVisible(false);
    m_chart->addAxis(axisY, Qt::AlignLeft);

    // 创建右 Y 轴（BMI数据）
    QValueAxis* axisYRight = new QValueAxis();
    axisYRight->setGridLineColor(Qt::blue);
    axisYRight->setTitleText("运动量(KM)");
    axisYRight->setRange(0, 15);
    axisYRight->setTickCount(11);
    axisYRight->setLabelFormat("%d");
    axisYRight->setGridLineVisible(false);
    m_chart->addAxis(axisYRight, Qt::AlignRight);


    // 创建折线图（体重 数据）
    m_line = new QLineSeries(this);
    m_line->setColor(QColor(44, 150, 120)); // 设置系列的颜色
    m_line->setPointsVisible(true); // 显示数据点
    m_line->setName("体重变化图"); // 设置图例的名称

    pen.setWidth(2);
    pen.setColor(Qt::green);
    m_line->setPen(pen);


    // 创建折线图（BMI 数据）
    m_lineKM = new QLineSeries(this);
    m_lineKM->setColor(QColor(150, 44, 120)); // 可以改变为不同的颜色
    m_lineKM->setPointsVisible(true);
    m_lineKM->setName("每日运动量");
    pen.setWidth(2);
    pen.setColor(Qt::red);
    m_lineKM->setPen(pen);

    // 给折线系列添加 BMI 数据点
    // 合并数据，使用 QPair 结构同时保存体重和身高的点
    QVector<QPair<QDateTime, QPair<float, float>>> dataPoints = {
        {startDate, {120, 7.5}}, // 2024-01-01
        {startDate.addDays(20), {135, 7.5}}, // 2024-01-21
        {startDate.addDays(30), {138, 7.5}}, // 2024-01-31
        {startDate.addDays(40), {134, 7.5}}, // 2024-02-10
        {startDate.addDays(60), {130, 7.5}}  // 2024-03-01
    };
    // 单循环遍历数据点
    for (const auto& dataPoint : dataPoints)
    {
        qreal weight = dataPoint.second.first;
        this->Add_Fit_Data(dataPoint.first,weight,dataPoint.second.second);
    }

    //把系列添加到QChart中
    m_chart->addSeries(m_line);
    m_chart->addSeries(m_lineKM);

    m_line->attachAxis(axisY);
    m_lineKM->attachAxis(axisYRight);
    m_line->attachAxis(m_axisX);
    m_lineKM->attachAxis(m_axisX);

    // this->CreateBMIAxisWithColorRanges();
}
void FitWidget::on_Add_Data_clicked()
{
    // 获取用户输入的体重
    float weight = ui->weight->text().toFloat();
    // 获取用户输入的运动量
    float km = ui->KM->text().toFloat();
    // 2024-11-19 16:46:45
    QDateTime time =  QDateTime::fromString(ui->DataTimeCombox->currentText(), "yyyy-MM-dd HH:mm:ss");
    qDebug()<<"添加的时间:"<<time<<"添加的重量:"<<weight;
    if(time.isValid() && weight>=0 && km>=0)
    {
        this->Add_Fit_Data(time,weight,km);
    }
    else
    {
        qDebug()<<"健康数据警告:"<<" 添加的健康数据有误,请检查有效输入";
    }

}


void FitWidget::CreateBMIAxisWithColorRanges()
{
    // 获取 chart 的 scene，用来绘制矩形
    QGraphicsScene* scene = m_chart->scene();

    // 定义颜色区间：过轻、正常、过重
    QRectF underweightRect(0, 0, 60, 100);  // 过轻区间 (BMI < 18.5)
    QRectF normalWeightRect(0, 100, 60, 100);  // 正常区间 (18.5 <= BMI < 24.9)
    QRectF overweightRect(0, 200, 60, 100);  // 过重区间 (BMI >= 24.9)

    // 创建矩形背景区域并设置颜色
    QGraphicsRectItem* underweightArea = new QGraphicsRectItem(underweightRect);
    underweightArea->setBrush(QBrush(QColor(255, 204, 204)));  // 过轻区间为浅红色
    underweightArea->setPen(Qt::NoPen);  // 不绘制边框
    scene->addItem(underweightArea);

    QGraphicsRectItem* normalArea = new QGraphicsRectItem(normalWeightRect);
    normalArea->setBrush(QBrush(QColor(204, 255, 204)));  // 正常区间为浅绿色
    normalArea->setPen(Qt::NoPen);
    scene->addItem(normalArea);

    QGraphicsRectItem* overweightArea = new QGraphicsRectItem(overweightRect);
    overweightArea->setBrush(QBrush(QColor(255, 255, 204)));  // 过重区间为浅黄色
    overweightArea->setPen(Qt::NoPen);
    scene->addItem(overweightArea);

    // 为每个区间设置文本标签
    QGraphicsTextItem* underweightLabel = new QGraphicsTextItem("Underweight (BMI < 18.5)");
    underweightLabel->setPos(65, 50);
    underweightLabel->setDefaultTextColor(Qt::black);
    underweightLabel->setFont(QFont("Arial", 10));
    scene->addItem(underweightLabel);

    QGraphicsTextItem* normalLabel = new QGraphicsTextItem("Normal (18.5 - 24.9)");
    normalLabel->setPos(65, 150);
    normalLabel->setDefaultTextColor(Qt::black);
    normalLabel->setFont(QFont("Arial", 10));
    scene->addItem(normalLabel);

    QGraphicsTextItem* overweightLabel = new QGraphicsTextItem("Overweight (BMI >= 25)");
    overweightLabel->setPos(65, 250);
    overweightLabel->setDefaultTextColor(Qt::black);
    overweightLabel->setFont(QFont("Arial", 10));
    scene->addItem(overweightLabel);
}

void FitWidget::resizeEvent(QResizeEvent *event)
{
    m_view->resize(ui->LineWidget->size());  // 重述大小
    m_view->setContentsMargins(0,0,0,0);
    event->accept();
}



