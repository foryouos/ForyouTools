#ifndef BUTTON_DAY_H
#define BUTTON_DAY_H

#include "date_time_defines.h"
#include <QPushButton>
#include <QMouseEvent>

class ButtonDay : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY(int id READ id WRITE setId DESIGNABLE true)
	Q_PROPERTY(QVariant data READ data WRITE setData DESIGNABLE true)


public:
	//using 关键字是在C++11之后出现的，有些版本是不支持的，所以这边我们不使用
	//using QPushButton::QPushButton;

	explicit ButtonDay(QWidget *parent = 0);
	explicit ButtonDay(int id, QWidget *parent = 0);
	~ButtonDay();

	int id() const
	{
		return m_id;
	}

	void setId(int id)
	{
		m_id = id;
	}

	DateTime::DayDisplay role() const
	{
		return m_role;
	}

	void setRole(const DateTime::DayDisplay& role);

	DateTime::DayType type() const
	{
		return m_type;
	}

	void setType(const DateTime::DayType& type)
	{
		m_type = type;
	}

	DateTime::DayMonth month() const
	{
		return m_month;
	}

	void setMonth(const DateTime::DayMonth& month)
	{
		m_month = month;
	}
	
	QVariant data() const
	{
		return m_data;
	}

	void setData(const QVariant& data)
	{
		m_data = data;
	}

private:

	int m_id{ -1 };
	QVariant m_data{ QVariant() };
	DateTime::DayDisplay m_role{ DateTime::CURRENT_DAY };
	DateTime::DayType m_type{ DateTime::WORKDAY };
	DateTime::DayMonth m_month{ DateTime::CURRENT_MONTH_DAY };
};

#endif // BUTTON_DAY_H
