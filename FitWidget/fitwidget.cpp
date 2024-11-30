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
    // 初始化获取 Mysql
    m_sql = new SQLThread;
    QStringList drivers = m_sql->Get_All_Sql_Driver();
    foreach(QString driver,drivers)
    {
        qDebug()<<"支持的SQL驱动:"<<driver;
    }
    m_sql->Connect_Sql_Data(DBSQL::SQLite3,"FitSQLData");

}

FitWidget::~FitWidget()
{
    delete ui;
}

void FitWidget::Add_Fit_Data(QDateTime time, float weight,float km)
{
    // 计算 BMI，BMI = 体重(kg) / 身高(m)^2
    float bmi = (weight/2) / (m_height * m_height);
    // 转换日期为时间戳（毫秒级）
    qreal x = static_cast<qreal>(time.toMSecsSinceEpoch());
    // 为体重数据添加点
    // 检查并替换体重数据点
    bool weightReplaced = false;
    for (int i = 0; i < m_line->count(); ++i) {
        if (m_line->at(i).x() == x) {
            m_line->replace(i, x, weight);
            weightReplaced = true;
            break;
        }
    }
    if (!weightReplaced) {
        m_line->append(x, weight); // 如果没有找到，添加新数据点
    }

    // 检查并替换公里数数据点
    bool kmReplaced = false;
    for (int i = 0; i < m_lineKM->count(); ++i) {
        if (m_lineKM->at(i).x() == x) {
            m_lineKM->replace(i, x, km);
            kmReplaced = true;
            break;
        }
    }
    if (!kmReplaced) {
        m_lineKM->append(x, km); // 如果没有找到，添加新数据点
    }

    // 更新图表（如果需要）
    // 获取 x 轴的当前范围 检查 m_axisX 是否已初始化
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
    m_Exercise += km;
    if((m_Aver_Weight - 0.0) < 0.1)
    {
        m_Aver_Weight = weight;
    }
    else
    {
        m_Aver_Weight = (m_Aver_Weight + weight)/2;
    }
    m_view->chart()->update();  // 强制更新图表
    // 更新统计数据
    ui->ALL_KM->setText(QString::number(m_Exercise)+" KM");
    ui->Aver_Weight->setText(QString::number(m_Aver_Weight));
    ui->BMI->setText(QString::number(bmi));
    //判断BMI值 来 健康水平进行判断
    QString obesityStatus;
    if (bmi < 18.5) {
        obesityStatus = "体重过轻";
    } else if (bmi >= 18.5 && bmi <= 23.9) {
        obesityStatus = "正常体重";
    } else if (bmi >= 24 && bmi <= 27.9) {
        obesityStatus = "超重";
    } else if (bmi >= 28) {
        obesityStatus = "肥胖";
    }
    // 打印 BMI 值和对应的肥胖状态
    ui->HealthStatus->setText(obesityStatus);

}

void FitWidget::Fit_Chart_Init()
{
    // 创建图标视图 QChartView
    m_view=new QChartView(ui->LineWidget);
    m_view->setRubberBand(QChartView::HorizontalRubberBand);

    // m_view->resize(QSize(800,600));
    // 创建图标 QChart
    m_chart=new QChart();
    m_chart->setTheme(QChart::ChartTheme::ChartThemeLight);
    // 设置外边距 可以使外面的空白大大减少
    QMargins m(-10,-10,-10,-10);
    m_chart->setMargins(m);
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
    // m_chart->createDefaultAxes();

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
    // TODO:从数据库中获取数据

    m_dataPoints[startDate] = {120, 7.5};  // 2024-01-01
    m_dataPoints[startDate.addDays(100)] = {135, 7.5};  // 2024-01-21
    m_dataPoints[startDate.addDays(30)] = {138, 7.5};  // 2024-01-31
    m_dataPoints[startDate.addDays(40)] = {134, 7.5};  // 2024-02-10
    m_dataPoints[startDate.addDays(60)] = {130, 7.5};  // 2024-03-01
    // 单循环遍历数据点
    // 单循环遍历数据点
    for (const auto& dataPoint : m_dataPoints.toStdMap())
    {
        qreal weight = dataPoint.second.first;  // 正确，访问 QPair 的 first 部分
        qreal km = dataPoint.second.second;  // 正确，访问 QPair 的 second 部分
        m_dataPoints.find(dataPoint.first);
        this->Add_Fit_Data(dataPoint.first, weight, km);  // 使用 QDateTime 和两个 float

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
    //TODO: 合法数据 同步数据库
    // 获取用户输入的体重
    float weight = ui->weight->text().toFloat();
    // 获取用户输入的运动量
    float km = ui->KM->text().toFloat();
    // 2024-11-19 16:46:45
    QDateTime time =  QDateTime::fromString(ui->DataTimeCombox->currentText(), "yyyy-MM-dd HH:mm:ss");
    // 需要重新构建 数据 将原有的数据加入到 如果时间加入之前的数据 折线图会 倒回去 并没有按照时间顺序
    if(time.isValid() && weight>=0 && km>=0)
    {
        m_dataPoints[time] = {weight, km};

        // 可以使用replace 即不再需要 使用clear 提高效率
        m_Aver_Weight = 0.0;
        m_Exercise = 0.0;
        m_line->clear();
        m_lineKM->clear();

        for (const auto& dataPoint : m_dataPoints.toStdMap())
        {
            qreal weight = dataPoint.second.first;  // 正确，访问 QPair 的 first 部分
            qreal km = dataPoint.second.second;  // 正确，访问 QPair 的 second 部分
            m_dataPoints.find(dataPoint.first);
            this->Add_Fit_Data(dataPoint.first, weight, km);  // 使用 QDateTime 和两个 float
        }

    }
    else
    {
        qDebug()<<"健康数据警告:"<<" 添加的健康数据有误,请检查有效输入";
        QMessageBox::warning(this,"数据警告","输入的健康数据不合法,请重新输入");
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
    m_view->resize(ui->CenterWidget->size());  // 重述大小
    m_view->setContentsMargins(0,0,0,0);
    event->accept();
}



