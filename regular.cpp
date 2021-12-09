#include "regular.h"
#include "ui_regular.h"

regular::regular(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regular)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("Tours");
    db.setDatabaseName("C:/example/" "DataBase.db");
    if (!db.open()) {
        qDebug() << db.lastError().text();
    } else {
        qDebug() << "Success!";
    }
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT Name FROM Client_Spr WHERE Count > 4");
    model->setHeaderData(0, Qt::Horizontal, tr("Клиент"));
    ui->tableView->setModel(model);
    ui->tableView->show();
}


regular::~regular()
{
    delete ui;
}
