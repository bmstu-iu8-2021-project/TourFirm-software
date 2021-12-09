#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bookingwindow = new Booking(this);
    tourswindow = new Tours(this);
    settingswindow = new Settings(this);
    QColor color(255, 127, 50);
    ui->label->setStyleSheet(QString("color: %1").arg(color.name()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Bron_clicked() {
    bookingwindow->setWindowTitle("Booking");
    bookingwindow->show();

}

void MainWindow::on_Regulars_clicked() {
    regular *regularwindow = new regular(this);
    regularwindow->setWindowTitle("Regular Clients");
    regularwindow->show();
}

void MainWindow::on_Tours_clicked() {
    tourswindow->setWindowTitle("Tours");
    tourswindow->show();
}

void MainWindow::on_Settings_clicked() {
    settingswindow->setWindowTitle("Settings");
    settingswindow->show();
}

void MainWindow::on_Quit_clicked() {
    MainWindow::close();
}
