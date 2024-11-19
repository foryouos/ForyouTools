#include "date_time_widget.h"
#include "ui_date_time_widget.h"
#include "button_day.h"

#include <QMenu>

DateTimeWidget::DateTimeWidget(QWidget* parent) : QWidget(parent), ui(new Ui::DateTimeWidget)
{
	ui->setupUi(this);

	initPage();
}

DateTimeWidget::~DateTimeWidget()
{
	delete ui;
}

void DateTimeWidget::initPage()
{
#if SUPPORT_C11
#else
    DateTime::MapInsert::initMonth();
#endif
	setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

	auto pMenu = new QMenu(this);
	pMenu->setProperty("type", "month");
	ui->btnMonth->setMenu(pMenu);
	
	for (auto itor = DateTime::month().begin(); itor != DateTime::month().end(); ++itor)
	{
		auto pMonth = pMenu->addAction(itor.value(), this, [this] 
		{
			auto const pAction = qobject_cast<QAction*>(sender());
			if (Q_NULLPTR == pAction)
			{
				return;
			}
			ui->btnMonth->setText(pAction->text());
			ui->btnMonth->setData(DateTime::month().key(pAction->text()));

			updateDays(ui->dateEdit->date().day());
		});

		pMonth->setData(itor.key());
	}
	
	for (int index = 0; index < 42; ++index)
	{
		auto btn = new ButtonDay(index + 1);
		btn->setFixedSize(QSize(30, 30));
		ui->gridLayout->addWidget(btn, index / 7, index % 7);

		btn->setType(((index % 7 == 0) || (index % 7 == 6)) ? DateTime::WEEKEND : DateTime::WORKDAY);
		btn->setRole(DateTime::CURRENT_MONTH);

		m_dayList.append(QVariant::fromValue(static_cast<void*>(btn)));

		connect(btn, &QPushButton::clicked, this, [this]
		{
			for (const auto& pbt : m_dayList)
			{
				auto pb = static_cast<ButtonDay*>(pbt.value<void*>());
				if (Q_NULLPTR == pb)
				{
					continue;
				}

				if (pb->role().testFlag(DateTime::SELECT_DAY))
				{
					pb->setRole(DateTime::CURRENT_MONTH);
					break;
				}
			}
			auto const btn = qobject_cast<ButtonDay*>(sender());
			btn->setRole(DateTime::SELECT_DAY);

			if (btn->month().testFlag(DateTime::PREV_MONTH_DAY))
			{
				if (ui->btnMonth->data().toInt() == 1)
				{
					ui->btnMonth->setData(12);
					ui->btnYear->setData(ui->btnYear->data().toInt() - 1);
					ui->btnYear->setText(QString::fromLocal8Bit("%1定").arg(ui->btnYear->data().toInt()));
				}
				else
				{
					ui->btnMonth->setData(ui->btnMonth->data().toInt() - 1);
				}
				ui->btnMonth->setText(DateTime::month().value(ui->btnMonth->data().toInt()));
			}

			if (btn->month().testFlag(DateTime::NEXT_MONTH_DAY))
			{
				if (ui->btnMonth->data().toInt() == 12)
				{
					ui->btnMonth->setData(1);
					ui->btnYear->setData(ui->btnYear->data().toInt() + 1);
					ui->btnYear->setText(QString::fromLocal8Bit("%1定").arg(ui->btnYear->data().toInt()));
				}
				else
				{
					ui->btnMonth->setData(ui->btnMonth->data().toInt() + 1);
				}
				ui->btnMonth->setText(DateTime::month().value(ui->btnMonth->data().toInt()));
			}

			updateDays(btn->data().toInt());
		});
	}

	for (int index = 0; index < 20; ++index)
	{
		auto btn = new ButtonDay(index + 1);
		btn->setFixedSize(QSize(60, 30));
		ui->gridLayoutYears->addWidget(btn, index / 4, index % 4);
		btn->setData(ui->dateEdit->date().year() - 10 + index);
		btn->setText(QString::fromLocal8Bit("%1定").arg(btn->data().toInt()));
		btn->setRole(DateTime::OTHER);

		m_yearList.append(QVariant::fromValue(static_cast<void*>(btn)));
		connect(btn, &QPushButton::clicked, this, [this] 
		{
			for (const auto& pbt : m_yearList)
			{
				auto pb = static_cast<ButtonDay*>(pbt.value<void*>());
				if (Q_NULLPTR == pb)
				{
					continue;
				}

				if (pb->role().testFlag(DateTime::CURRENT_YEAR))
				{
					pb->setRole(DateTime::OTHER);
					break;
				}
			}

			auto const btn = qobject_cast<ButtonDay*>(sender());
			btn->setRole(DateTime::CURRENT_YEAR);
			ui->stackedWidget->setCurrentWidget(ui->wdgCalendar);
			ui->btnYear->setData(btn->data());
			ui->btnYear->setText(QString::fromLocal8Bit("%1定").arg(btn->data().toInt()));
			updateDays(ui->dateEdit->date().day());

			ui->btnMonth->setVisible(true);
			ui->btnPrev->setVisible(true);
			ui->btnNext->setVisible(true);
			ui->wdgConfirm->setVisible(true);
		});
	}

	connect(ui->btnYear, &QPushButton::clicked, this, [this] 
	{
		int index = 0;
		for (const auto& pbt : m_yearList)
		{
			auto btn = static_cast<ButtonDay*>(pbt.value<void*>());
			if (Q_NULLPTR == btn)
			{
				continue;
			}
						
			btn->setData(ui->btnYear->data().toInt() - 10 + index++);
			btn->setText(QString::fromLocal8Bit("%1定").arg(btn->data().toInt()));
			btn->setRole(ui->btnYear->data().toInt() == btn->data().toInt() ? DateTime::CURRENT_YEAR : DateTime::OTHER);
		}
		ui->stackedWidget->setCurrentWidget(ui->wdgYears);

		ui->btnMonth->setVisible(false);
		ui->btnPrev->setVisible(false);
		ui->btnNext->setVisible(false);
		ui->wdgConfirm->setVisible(false);
	});

	connect(ui->btnToday, &QPushButton::clicked, this, [this]
	{
		QDate dt = QDate::currentDate();
		ui->btnMonth->setData(dt.month());
		ui->btnYear->setData(dt.year());
		ui->btnMonth->setText(DateTime::month().value(dt.month()));
		ui->btnYear->setText(QString::fromLocal8Bit("%1定").arg(dt.year()));

		updateDays(dt.day());
	});

	connect(ui->btnNow, &QPushButton::clicked, this, [this] 
	{
		QTime time = QTime::currentTime();
		ui->timeEdit->setTime(time);
		ui->wdgHour->setValue(time.hour());
		ui->wdgMin->setValue(time.minute());
		ui->wdgSec->setValue(time.second());
	});

	connect(ui->btnConfirm, &QPushButton::clicked, this, [this] 
	{
		emit signal_dateTime(ui->dateEdit->date(), ui->timeEdit->time());
		
		QDateTime dt;
		dt.setDate(ui->dateEdit->date());
		dt.setTime(ui->timeEdit->time());
		emit signal_dateTime(dt);
	});

	connect(ui->btnCancel, &QPushButton::clicked, this, [this]
	{
		emit signal_cancel();
	});
	
	connect(ui->btnPrev, &QPushButton::clicked, this, [this]
	{
		if (ui->btnMonth->data().toInt() == 1)
		{
			ui->btnMonth->setData(12);
			ui->btnYear->setData(ui->btnYear->data().toInt() - 1);
			ui->btnYear->setText(QString::fromLocal8Bit("%1定").arg(ui->btnYear->data().toInt()));
		}
		else
		{
			ui->btnMonth->setData(ui->btnMonth->data().toInt() - 1);
		}
		ui->btnMonth->setText(DateTime::month().value(ui->btnMonth->data().toInt()));

		updateDays(ui->dateEdit->date().day());
	});

	connect(ui->btnNext, &QPushButton::clicked, this, [this]
	{
		if (ui->btnMonth->data().toInt() == 12)
		{
			ui->btnMonth->setData(1);
			ui->btnYear->setData(ui->btnYear->data().toInt() + 1);
			ui->btnYear->setText(QString::fromLocal8Bit("%1定").arg(ui->btnYear->data().toInt()));
		}
		else
		{
			ui->btnMonth->setData(ui->btnMonth->data().toInt() + 1);
		}
		ui->btnMonth->setText(DateTime::month().value(ui->btnMonth->data().toInt()));

		updateDays(ui->dateEdit->date().day());
	});

	QTime time = QTime::currentTime();

	ui->wdgHour->setRang(0, 23);
	ui->wdgHour->setValue(time.hour());

	ui->wdgMin->setRang(0, 60);
	ui->wdgMin->setValue(time.minute());

	ui->wdgSec->setRang(0, 60);
	ui->wdgSec->setValue(time.second());

	ui->timeEdit->setTime(time);

	connect(ui->wdgHour, &TimeScrollBar::signal_valueChanged, this, [this](int val)
	{
		QTime time = ui->timeEdit->time();
		time.setHMS(val, time.minute(), time.second());
		ui->timeEdit->setTime(time);
	});

	connect(ui->wdgMin, &TimeScrollBar::signal_valueChanged, this, [this](int val)
	{
		QTime time = ui->timeEdit->time();
		time.setHMS(time.hour(), val, time.second());
		ui->timeEdit->setTime(time);
	});

	connect(ui->wdgSec, &TimeScrollBar::signal_valueChanged, this, [this](int val)
	{
		QTime time = ui->timeEdit->time();
		time.setHMS(time.hour(), time.minute(), val);
		ui->timeEdit->setTime(time);
	});
}

void DateTimeWidget::showEvent(QShowEvent *event)
{
	ui->stackedWidget->setCurrentWidget(ui->wdgCalendar);
    if(!ui->wdgConfirm->isVisible())
    {
        ui->btnMonth->setVisible(false);
        ui->btnPrev->setVisible(false);
        ui->btnNext->setVisible(false);
        ui->wdgConfirm->setVisible(false);
    }
	QDate dt = QDate::currentDate();
	ui->btnMonth->setData(dt.month());
	ui->btnYear->setData(dt.year());
	ui->btnMonth->setText(DateTime::month().value(dt.month()));
	ui->btnYear->setText(QString::fromLocal8Bit("%1定").arg(dt.year()));

	updateDays(dt.day());
}

void DateTimeWidget::updateDays(int current)
{
	QDate dt = QDate(ui->btnYear->data().toInt(), ui->btnMonth->data().toInt(), 01);
	int days = dt.dayOfWeek();

	QDate prevDt = dt.addDays(-1);

	int offset = prevDt.day() - days + 1;
	for (int index = 0; index < days; ++index)
	{
		auto btn = static_cast<ButtonDay*>(m_dayList[index].value<void*>());
		btn->setText(QString::number(offset + index));
		btn->setData(offset + index);
		btn->setMonth(DateTime::PREV_MONTH_DAY);
		btn->setRole(DateTime::NON_CURRENY_MONTH);
	}

	QDate nextDt = dt.addMonths(1).addDays(-1);
	int count = nextDt.day() - dt.day() + 1;

	offset = 0;
	for (int index = days; index < count + days; ++index)
	{
		auto btn = static_cast<ButtonDay*>(m_dayList[index].value<void*>());
		btn->setText(QString::number(++offset));
		btn->setData(offset);
		btn->setMonth(DateTime::CURRENT_MONTH_DAY);
		btn->setRole(DateTime::CURRENT_MONTH);
	
		if (offset == current)
		{
			btn->setRole(DateTime::SELECT_DAY);
		}
	}

	offset = 0;
	for (int index = count + days; index < m_dayList.size(); ++index)
	{
		auto btn = static_cast<ButtonDay*>(m_dayList[index].value<void*>());
		btn->setText(QString::number(++offset));
		btn->setData(offset);
		btn->setMonth(DateTime::NEXT_MONTH_DAY);
		btn->setRole(DateTime::NON_CURRENY_MONTH);
	}
	ui->dateEdit->setDate(QDate(ui->btnYear->data().toInt(), ui->btnMonth->data().toInt(), current));

	QDate cdt = QDate::currentDate();
	if (ui->dateEdit->date().month() != cdt.month() || ui->dateEdit->date().year() != cdt.year())
	{
		return;
	}

	for (const auto& btn : m_dayList)
	{
		auto pb = static_cast<ButtonDay*>(btn.value<void*>());
		if (Q_NULLPTR == pb)
		{
			continue;
		}

		if (pb->month().testFlag(DateTime::CURRENT_MONTH_DAY) && !pb->role().testFlag(DateTime::SELECT_DAY) && pb->data().toInt() == cdt.day())
		{
			pb->setRole(DateTime::CURRENT_DAY);
			break;
		}
	}
}

void DateTimeWidget::setDateTime(const QDateTime& dt)
{
    ui->dateEdit->setDate(dt.date());
    ui->timeEdit->setTime(dt.time());
}
