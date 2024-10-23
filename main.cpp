#include "foryouos.h"

#include <QApplication>
#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    foryouos w;
    w.show();
#else
    QWidget window;
    window.resize(200, 150);
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(&window);
    window.setGraphicsEffect(effect);
    window.show();

    QPropertyAnimation *animation = new QPropertyAnimation(effect, "windowOpacity");
    animation->setDuration(2000); // 2 seconds
    animation->setStartValue(1.0); // Fully opaque
    animation->setEndValue(0.0); // Fully transparent
    animation->start();
#endif
    return a.exec();
}
