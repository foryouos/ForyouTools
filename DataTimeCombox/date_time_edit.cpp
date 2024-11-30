#include "date_time_edit.h"
#include "date_time_widget.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QDateTime>
#include <QFile>
DateTimeEdit::DateTimeEdit(QWidget *parent) : QComboBox(parent)
{
	initPage();
}

void DateTimeEdit::initPage()
{
	auto table = new QTableWidget;
	table->setMinimumHeight(592);
    //table->setMinimumWidth(280);
	table->verticalHeader()->setVisible(false);
	table->horizontalHeader()->setVisible(false);
	table->setColumnCount(1);
	table->setRowCount(1);

	auto cell = new DateTimeWidget;
    cell->setMinimumHeight(592);
    cell->setMinimumWidth(280);
    table->setCellWidget(0, 0, cell);

	this->setModel(table->model());
	this->setView(table);

	this->setEditable(true);
	this->setProperty("type", "datetime");

	connect(cell, static_cast<void(DateTimeWidget::*)(const QDateTime&)>(&DateTimeWidget::signal_dateTime), this, [this](const QDateTime& dt)
	{
		this->setEditText(dt.toString("yyyy-MM-dd hh:mm:ss"));
		this->hidePopup();
	});

	connect(cell, &DateTimeWidget::signal_cancel, this, [this]
	{
		hidePopup();
	});

    QFile qss(":/datetime/datetime.qss");
    QString style;
    if (qss.open(QFile::ReadOnly))
    {
        // style = QLatin1String(qss.readAll());
        style = qss.readAll();
        qss.close();
    }
    this->setStyleSheet(style);
}

void DateTimeEdit::setDateTime(const QDateTime& dt)
{
	this->setEditText(dt.toString("yyyy-MM-dd hh:mm:ss"));

	auto pTable = static_cast<QTableWidget*>(const_cast<QAbstractItemView*>(view()));
	auto pWidget = static_cast<DateTimeWidget*>(pTable->cellWidget(0, 0));

	pWidget->setDateTime(dt);
}

QDateTime DateTimeEdit::datetime() const
{
	return QDateTime::fromString(this->currentText(), "yyyy-MM-dd hh:mm:ss");
}
