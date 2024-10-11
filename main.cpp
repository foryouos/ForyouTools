#include "foryouos.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    foryouos w;
    w.show();
    return a.exec();
}
