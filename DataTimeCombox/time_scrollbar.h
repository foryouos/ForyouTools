#ifndef TIME_SCROLLBAR_H
#define TIME_SCROLLBAR_H

#include "date_time_defines.h"
#include <QWidget>
#include<QPainter>

class TimeScrollBar : public QWidget
{
    Q_OBJECT
public:

public:
    explicit TimeScrollBar(QWidget *parent = 0);
    ~TimeScrollBar();

public:
    int value() const
	{ 
		return m_value;
	}

    void setValue(int val)
	{ 
		m_value = val;
		update();
	}

    void setStep(int step) 
	{
		m_step = step;
	}

    void setDevice(int device)
	{
		m_device = device;
	}

    void setScrollType(DateTime::ScrollBarDirection direction)
	{
		m_direction = direction;
	}

    inline void setRang(int min, int max)
    {
        m_min = min;
		m_max = max;
        m_value = m_value > max ? max : m_value;
		m_value = m_value < min ? min : m_value;
    }

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:

    void paintBackground(QPainter* pPainter);
    void paintLine(QPainter* pPainter);
    void paintText(QPainter* pPainter, int val, int offset, int fontSize);

signals:
    void signal_valueChanged(int value);

private:
	int m_value{ 0 };
	int m_offset{ 0 };	
	int m_max{ 0 };       
    int m_min{ 0 };       
    int m_mousePos{ 0 };
    int m_device{ 5 };
    int m_step{ 1 };  
	DateTime::ScrollBarDirection  m_direction{ DateTime::VERTICAL };
};

#endif // TIME_SCROLLBAR_H
