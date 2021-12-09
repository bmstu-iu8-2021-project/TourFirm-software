#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QLineEdit>
#include <QStyleFactory>

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("Tours");
    db.setDatabaseName("C:/example/" "DataBase.db");
    db.open();
    ui->pass->setEchoMode(QLineEdit::Password);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_pushButton_clicked() {
    if(ui->login->text() == "" || ui->pass->text() == "")
        {
            QMessageBox::information(this,tr("Информация"), tr("Заполните все поля"));
            return;
        }


    QString strName = ui->login->text();
    QString hash = QString("%1").arg(QString(QCryptographicHash::hash(ui->pass->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    if (db.open()){
                 QSqlQuery query;
                 if(!query.next()) {
                     query.prepare( "SELECT * FROM Admin_Info WHERE Login=:Login AND Password=:Password");
                     query.bindValue(":Login", strName);
                     query.bindValue(":Password", hash);
                     query.exec();
                 }
                 if (query.next()) {
                 // авторизация прошла
                     QMessageBox::information(this, "Succesfull", "Успешная авторизация");
                     this->close();
                     MainWindow *window = new MainWindow(this);
                     window->setWindowTitle("Admin Panel");
                     window->show();
                     db.close();
                 } else {
                 // не прошла
                     QMessageBox::warning(this, "Error", "Неуспешная авторизация");
                 }
            }
}
