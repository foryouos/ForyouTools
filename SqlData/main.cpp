#include "sqldata.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SqlData w;
    w.show();
    return a.exec();
}
