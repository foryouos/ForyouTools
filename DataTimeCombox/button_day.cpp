#include "button_day.h"
#include <QStyle>
ButtonDay::ButtonDay(QWidget* parent) : QPushButton(parent)
{

}

ButtonDay::ButtonDay(int id, QWidget* parent) : QPushButton(parent), m_id(id)
{

}

ButtonDay::~ButtonDay()
{

}

void ButtonDay::setRole(const DateTime::DayDisplay& role)
{
	m_role = role;

	QString property = "";
	if (role.testFlag(DateTime::NON_CURRENY_MONTH))
	{
		property = "no-current-month-day";
	}
	if (role.testFlag(DateTime::CURRENT_MONTH))
	{
		property = type().testFlag(DateTime::WEEKEND) ? "weekend" : "workday";
	}
	if (role.testFlag(DateTime::CURRENT_DAY))
	{
		property = "current-day";
	}
	if (role.testFlag(DateTime::SELECT_DAY) || role.testFlag(DateTime::CURRENT_YEAR))
	{
		property = "select-day";
	}
	if (role.testFlag(DateTime::OTHER))
	{
		property = "workday";
	}

	setProperty("type", property);

	style()->unpolish(this);
	style()->polish(this);
}