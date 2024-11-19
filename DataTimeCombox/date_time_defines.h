#ifndef DATE_TIME_DEFINS_H
#define DATE_TIME_DEFINS_H
#pragma once

#include <QString>
#include <QMap>
#include <QColor>

#define SUPPORT_C11 0

namespace DateTime
{
	const int JANUARY = 1;
	const int FEBRUARY = 2;
	const int MARCH = 3;
	const int APRIL = 4;
	const int MAY = 5;
	const int JUNE = 6;
	const int JULY = 7;
	const int AUGUST = 8;
	const int SEPTEMBER = 9;
	const int OCTOBER = 10;
	const int NOVEMBER = 11;
	const int DECEMBER = 12;

	const QString JANUARY_TEXT = QString::fromLocal8Bit("1��");
	const QString FEBRUARY_TEXT = QString::fromLocal8Bit("2��");
	const QString MARCH_TEXT = QString::fromLocal8Bit("3��");
	const QString APRIL_TEXT = QString::fromLocal8Bit("4��");
	const QString MAY_TEXT = QString::fromLocal8Bit("5��");
	const QString JUNE_TEXT = QString::fromLocal8Bit("6��");
	const QString JULY_TEXT = QString::fromLocal8Bit("7��");
	const QString AUGUST_TEXT = QString::fromLocal8Bit("8��");
	const QString SEPTEMBER_TEXT = QString::fromLocal8Bit("9��");
	const QString OCTOBER_TEXT = QString::fromLocal8Bit("10��");
	const QString NOVEMBER_TEXT = QString::fromLocal8Bit("11��");
	const QString DECEMBER_TEXT = QString::fromLocal8Bit("12��");

	const int BACK_CROUND = 20;
	const int LINE = 21;
	const int CURRENT_TEXT = 22;
	const int DISABLE_TEXT = 23;

	const QColor BACK_CROUND_COLOR = QColor("#FFFFFF");
	const QColor LINE_COLOR = QColor("#0092FF");
	const QColor CURRENT_TEXT_COLOR = QColor("#363636");
	const QColor DISABLE_TEXT_COLOR = QColor("#CDC9C9");

#if SUPPORT_C11	//�Ͱ汾�ı�������֧�ֳ�ʼ���б�ֱ�ӳ�ʼ������ʽ

	static QMap<int, QString>& month()
	{
		static QMap<int, QString> map
		{
			{JANUARY,	JANUARY_TEXT},
			{FEBRUARY,	FEBRUARY_TEXT},
			{MARCH,		MARCH_TEXT},
			{APRIL,		APRIL_TEXT},
			{MAY,		MAY_TEXT},
			{JUNE,		JUNE_TEXT},
			{JULY,		JULY_TEXT},
			{AUGUST,	AUGUST_TEXT},
			{SEPTEMBER, SEPTEMBER_TEXT},
			{OCTOBER,	OCTOBER_TEXT},
			{NOVEMBER,	NOVEMBER_TEXT},
			{DECEMBER,	DECEMBER_TEXT},
		};
		return map;
	}

	static QMap<int, QColor>& color()
	{
		static QMap<int, QColor> map
		{
			{BACK_CROUND,	BACK_CROUND_COLOR},
			{LINE,			LINE_COLOR},
			{CURRENT_TEXT,	CURRENT_TEXT_COLOR},
			{DISABLE_TEXT,	DISABLE_TEXT_COLOR},
		};
		return map;
	}

#else
	static QMap<int, QString> map;
	static QMap<int, QString>& month()
	{
		return map;
	}
	static QMap<int, QColor> mapColor;
	static QMap<int, QColor>& color()
	{
		return mapColor;
	}

	class MapInsert
	{
	public:
		static void initMonth()
		{
			map.insert(JANUARY, JANUARY_TEXT);
			map.insert(FEBRUARY, FEBRUARY_TEXT);
			map.insert(MARCH, MARCH_TEXT);
			map.insert(APRIL, APRIL_TEXT);
			map.insert(MAY, MAY_TEXT);
			map.insert(JUNE, JUNE_TEXT);
			map.insert(JULY, JULY_TEXT);
			map.insert(AUGUST, AUGUST_TEXT);
			map.insert(SEPTEMBER, SEPTEMBER_TEXT);
			map.insert(OCTOBER, OCTOBER_TEXT);
			map.insert(NOVEMBER, NOVEMBER_TEXT);
			map.insert(DECEMBER, DECEMBER_TEXT);
		}
		static void initColor()
		{
			mapColor.insert(BACK_CROUND, BACK_CROUND_COLOR);
			mapColor.insert(LINE, LINE_COLOR);
			mapColor.insert(CURRENT_TEXT, CURRENT_TEXT_COLOR);
			mapColor.insert(DISABLE_TEXT, DISABLE_TEXT_COLOR);
		}
	};

#endif

	enum DISPLAY_STATUS	//������ʵ״̬
	{
		INVAILD = 0,
		NON_CURRENY_MONTH,
		CURRENT_MONTH,
		CURRENT_DAY,
		SELECT_DAY,

		CURRENT_YEAR = 10,
		OTHER
	};

	enum DAY_TYPE	//��������
	{
		WEEKEND = 1,
		WORKDAY,
	};

	enum DAY_OF_MONTH	//����������һ����
	{
		PREV_MONTH_DAY = 1,
		NEXT_MONTH_DAY,
		CURRENT_MONTH_DAY
	};

	enum SCROLLBAR_DIRECTION	//ʱ��������ķ���
	{
		VERTICAL = 1,
		HORIZONTAL
	};

	Q_DECLARE_FLAGS(DayDisplay, DISPLAY_STATUS)
	Q_DECLARE_OPERATORS_FOR_FLAGS(DayDisplay)

	Q_DECLARE_FLAGS(DayType, DAY_TYPE)
	Q_DECLARE_OPERATORS_FOR_FLAGS(DayType)

	Q_DECLARE_FLAGS(DayMonth, DAY_OF_MONTH)
	Q_DECLARE_OPERATORS_FOR_FLAGS(DayMonth)

	Q_DECLARE_FLAGS(ScrollBarDirection, SCROLLBAR_DIRECTION)
	Q_DECLARE_OPERATORS_FOR_FLAGS(ScrollBarDirection)
}

#endif // DATE_TIME_DEFINS_H
