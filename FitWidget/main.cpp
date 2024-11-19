#include "fitwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FitWidget w;
    w.show();
    return a.exec();
}
