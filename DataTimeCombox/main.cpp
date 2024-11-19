#include "mainwindow.h"
#include <QApplication>

#include<QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/datetime/datetime.qss");
    QString style;
    if (qss.open(QFile::ReadOnly))
    {
        style = QLatin1String(qss.readAll());

        qss.close();
    }
    a.setStyleSheet(style);
    MainWindow w;
    w.show();

    return a.exec();
}
