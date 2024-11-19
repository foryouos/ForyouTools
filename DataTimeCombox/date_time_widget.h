#ifndef DATE_TIME_WIDGET_H
#define DATE_TIME_WIDGET_H

#include <QWidget>

namespace Ui
{
	class DateTimeWidget;
}

class DateTimeWidget : public QWidget
{
Q_OBJECT

public:
	explicit DateTimeWidget(QWidget* parent = nullptr);
	~DateTimeWidget();

	void setDateTime(const QDateTime& dt);

protected:
	void showEvent(QShowEvent *event) override;

private:
	void initPage();
	void updateDays(int current);

signals:
	void signal_cancel();
	void signal_dateTime(const QDateTime&);
	void signal_dateTime(const QDate&, const QTime&);

private:
	Ui::DateTimeWidget* ui;
    QVariantList m_dayList;
    QVariantList m_yearList;
};

#endif // DATE_TIME_WIDGET_H
