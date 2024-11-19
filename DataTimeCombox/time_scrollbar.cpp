#include "time_scrollbar.h"
#include <QMouseEvent>
#include <QDebug>
#include <QWheelEvent>
TimeScrollBar::TimeScrollBar(QWidget *parent) : QWidget(parent)
{
#if SUPPORT_C11
#else
    DateTime::MapInsert::initColor();
#endif
    this->setFixedSize(parent->size());
}

TimeScrollBar::~TimeScrollBar()
{

}

void TimeScrollBar::wheelEvent(QWheelEvent *event)
{
    // 获取滚轮的水平和垂直位移
    int delta = event->angleDelta().y();  // 获取y轴的滚轮滚动量（垂直滚动）

    // 如果是水平滚动，则获取x轴滚动量
    if (m_direction == DateTime::HORIZONTAL) {
        delta = event->angleDelta().x();
    }
    // delta单位是1/8度
    int degrees = delta / 8;
    int step = degrees / 15;
    int target = m_direction == DateTime::VERTICAL ? this->height() : this->width();
    m_offset = target / m_device * step;
    update();
}

void TimeScrollBar::mousePressEvent(QMouseEvent *event)
{
    m_mousePos = m_direction == DateTime::VERTICAL ? event->pos().y() : event->pos().x();
    update();
}

void TimeScrollBar::mouseMoveEvent(QMouseEvent *event)
{
    int mousePos = m_direction == DateTime::VERTICAL ? event->pos().y() : event->pos().x();
 
    if(m_value == m_min && mousePos >= m_mousePos ||
       m_value == m_max && mousePos <= m_mousePos)
    {
        return;
    }
    int target = m_direction == DateTime::VERTICAL ? this->height() : this->width();
    int offset = mousePos - m_mousePos;

    if(offset > (target / m_device))	/*(target / m_device) 为一次偏移的最小值 */
    {
		offset = target / m_device;
    }
    else if(offset < -target / m_device)
    {
		offset = -target / m_device;
    }

    m_offset = offset;
    update();
}

void TimeScrollBar::mouseReleaseEvent(QMouseEvent *event)
{
    int target = m_direction == DateTime::VERTICAL ? this->height() : this->width();
    int offset = m_offset;

    /**计算鼠标的偏移量,根据显示字体的控件大小的一半来确定该偏移到那个值(正负表示偏移的方向)**/
    int nJudge = offset < 0 ? -(target / (m_device * 2)) : target / (m_device * 2);
    
	do 
	{
		if (offset < 0)
		{
			m_offset = offset < nJudge ? 0 : -target / m_device;
			break;
		}
		m_offset = offset < nJudge ? 0 : target / m_device;
	} while (false);

    update();
}

void TimeScrollBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    if(m_min == m_max)
    {
        return;
    }

    /**在绘制界面之前我们需要通过偏移量来计算当前值，毕竟我们的目的是得到值，而不是看着界面做沉思状**/
    int target = m_direction == DateTime::VERTICAL ? this->height() : this->width();
    int offset = m_offset;
    
	do 
	{
		if (offset >= (target / m_device) && m_value > m_min)
		{
			m_mousePos += target / m_device;
			offset -= target / m_device;
			this->setValue(m_value - m_step);
			break;
		}
		else if (offset <= -target / m_device && m_value < m_max)
		{
			m_mousePos -= target / m_device;
			offset += target / m_device;
			this->setValue(m_value + m_step);
		}

	} while (false);

    if(value() == m_max || value() == m_min)
    {
        offset = 0;
    }
    m_offset = offset;

    paintBackground(&painter);
    paintLine(&painter);

    int nFontSize = 15;	
    paintText(&painter, m_value, offset, nFontSize);

    for (int index = 1; index <= m_device / 2; ++index)
    {
        nFontSize -= 2;
        if (m_value - m_step * index >= m_min)
        {
            paintText(&painter, m_value - m_step * index, offset - target / m_device * index, nFontSize);
        }

        if (m_value + m_step * index <= m_max)
        {
            paintText(&painter, m_value + m_step * index, offset + target / m_device * index, nFontSize);
        }
    }

    emit signal_valueChanged(value());
}

void TimeScrollBar::paintBackground(QPainter *pPainter)
{
    pPainter->save();
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(DateTime::color().value(DateTime::BACK_CROUND));
    pPainter->drawRect(rect());
    pPainter->restore();
}

void TimeScrollBar::paintLine(QPainter *pPainter)
{
    int width = this->width();
    int height = this->height();

    pPainter->save();
    pPainter->setBrush(Qt::NoBrush);

    QPen pen = pPainter->pen();
    pen.setWidth(1);
    pen.setColor(DateTime::color().value(DateTime::LINE));
    pen.setCapStyle(Qt::RoundCap);
    pPainter->setPen(pen);

    /**绘制线条需要指定线条的起始坐标, 对于不同类型的滚动屏，坐标也有不同的数值**/

    for(int index = 2; index < 4; ++index)
    {
        /**对于垂直滚动屏来说，线条的Y值是不变的，同理对于水平的滚动屏来说，线条的X值是不变的**/
        int posX = m_direction == DateTime::VERTICAL ? 0 : width / 5 * index;
        int posY = m_direction == DateTime::VERTICAL ? height / 5 * index : 0;
        int endPosX = m_direction == DateTime::VERTICAL ? height : posX;
        int endPosY = m_direction == DateTime::VERTICAL ? posY : height;

        pPainter->drawLine(posX, posY, endPosX,  endPosY);
    }
    pPainter->restore();
}

void TimeScrollBar::paintText(QPainter *pPainter, int val, int offset, int fontSize)
{
    pPainter->save();

    int width = this->width();
    int height = this->height();

	QFont font = QFont("Helvetica", fontSize);

	int target = m_direction == DateTime::VERTICAL ? this->height() : this->width();
    //font.setPixelSize((target / 2 - qAbs(offset)) / m_device);	//通过界面自适应的字体会显大，因此使用了固定的字体大小
	
    QColor nColor = offset == 0 ? DateTime::color().value(DateTime::CURRENT_TEXT) : DateTime::color().value(DateTime::DISABLE_TEXT);
    QPen pen = pPainter->pen();
    pen.setColor(nColor);
    pPainter->setPen(pen);
    pPainter->setBrush(Qt::NoBrush);
    pPainter->setFont(font);

	QString text = val < 10 ? QString("0%1").arg(val) : QString::number(val);
    if(m_direction == DateTime::HORIZONTAL)
    {
        // int textWidth = pPainter->fontMetrics().width(val);
        // 传递 QString 类型给 horizontalAdvance
        int textWidth = pPainter->fontMetrics().horizontalAdvance(text);

        int initX = width / 2 + offset - textWidth / 2;
        pPainter->drawText(QRect(initX, 0, 15, height), Qt::AlignCenter, text);
        //pPainter->drawText(QRect(initX, 0, textWidth, height), Qt::AlignCenter, QString::number(nValue));
        pPainter->restore();
    }
	else if (m_direction == DateTime::VERTICAL)
	{
		int textHeight = pPainter->fontMetrics().height();
		int initY = height / 2 + offset - textHeight / 2;
		pPainter->drawText(QRect(0, initY, width, textHeight), Qt::AlignCenter, text);
		pPainter->restore();
	}  
}
