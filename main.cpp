#include "mainwindow.h"
#include <QStyle>
#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

       // Установка стиля WindowsXP
       QApplication::setStyle(QStyleFactory::create("WindowsXP"));

       // Создание и отображение вашего главного окна или виджета
       MainWindow w;
       w.show();

       return a.exec();
}
