#include "mainwindow.h"
#include "secondwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SecondWindow w;
    w.setWindowTitle("Authorization");
    w.show();
    return a.exec();
}
