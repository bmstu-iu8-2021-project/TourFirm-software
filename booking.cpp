#include "booking.h"
#include "ui_booking.h"
#include "comboboxitemdelegate.h"
#include "dateeditdelegate.h"

Booking::Booking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Booking)
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
    model = new QSqlRelationalTableModel(this, db);
    model->setTable("Bron_Opers");
    SetHeader(model);
    ui->tableView->horizontalHeader()->setStyleSheet("background-color:lightgrey;");
    model->setRelation(3, QSqlRelation("StatusBron_Spr", "id", "Name"));
    auto *eqCb = new ComboBoxItemDelegate(ui->tableView, "Name", "StatusBron_Spr");
    ui->tableView->setItemDelegateForColumn(3, eqCb);
    model->setRelation(4, QSqlRelation("ClassBron_Spr", "id", "Name"));
    auto *eqCa = new ComboBoxItemDelegate(ui->tableView, "Name", "ClassBron_Spr");
    ui->tableView->setItemDelegateForColumn(4, eqCa);
    model->setRelation(2, QSqlRelation("Tour_Spr", "id", "Direction"));
    auto *eqCd = new ComboBoxItemDelegate(ui->tableView, "Direction", "Tour_Spr");
    ui->tableView->setItemDelegateForColumn(2, eqCd);
    model->setRelation(5, QSqlRelation("HotelClass_Spr", "id", "Name"));
    auto *eqCe = new ComboBoxItemDelegate(ui->tableView, "Name", "HotelClass_Spr");
    ui->tableView->setItemDelegateForColumn(5, eqCe);
    auto *pDateDelegateFrom = new DateEditDelegate(ui->tableView);
    ui->tableView->setItemDelegateForColumn(7, pDateDelegateFrom);
    auto *pDateDelegateTo = new DateEditDelegate(ui->tableView);
    ui->tableView->setItemDelegateForColumn(8, pDateDelegateTo);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);     // Устанавливаем модель на TableView
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    model->select(); // Делаем выборку данных из таблицы
    ui->SubmitAdd->setEnabled(false);
    ui->SubmitDelete->setEnabled(false);
    ui->Count->setEnabled(false);
}

Booking::~Booking()
{
    delete ui;
}


void Booking::SetHeader(QSqlTableModel *headermodel) {
    headermodel->setHeaderData(1, Qt::Horizontal, "Клиент");
    headermodel->setHeaderData(2, Qt::Horizontal, "Направление");
    headermodel->setHeaderData(3, Qt::Horizontal, "Статус брони");
    headermodel->setHeaderData(4, Qt::Horizontal, "Класс брони");
    headermodel->setHeaderData(5, Qt::Horizontal, "Класс Отеля");
    headermodel->setHeaderData(6, Qt::Horizontal, "Цена за сутки");
    headermodel->setHeaderData(7, Qt::Horizontal, "Дата бронирования С");
    headermodel->setHeaderData(8, Qt::Horizontal, "Дата бронирования По");
}

void Booking::on_Add_clicked() {
    qDebug() << model->insertRow(model->rowCount());
    ui->SubmitAdd->setEnabled(true);
}

void Booking::on_Delete_clicked() {
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >= 0) {
        qDebug() << model->removeRow(selectedRow);
    } else {
        qDebug() << "No Row selected!";
    }
    ui->SubmitDelete->setEnabled(true);
    ui->SubmitAdd->setEnabled(false);
}

void Booking::on_SubmitDelete_clicked() {
    int selectedRow = ui->tableView->currentIndex().row();
    QString str = model->index(selectedRow,1).data().toString();
    QSqlQuery query;
    if(!query.next()) {
        query.prepare( "SELECT Count FROM Client_Spr WHERE Name=:Name");
        query.bindValue(":Name", str);
        query.exec();
    }
    int counter;
    if(query.next()) {
        counter = query.value(0).toInt();
    }
    if (counter > 0) {
        if(!query.next()) {
            query.prepare( "UPDATE Client_Spr SET Count = Count-1 WHERE Name=:Name");
            query.bindValue(":Name", str);
            query.exec();
        }
    }
    model->submitAll();
    ui->SubmitDelete->setEnabled(false);
}

void Booking::on_SubmitAdd_clicked() {
    int selectedRow = ui->tableView->currentIndex().row();
    QString str = model->index(selectedRow,1).data().toString();
    QSqlQuery query;
    //"SELECT * FROM Client_Spr WHERE Name='"+str+"'"
    if(!query.next()) {
        query.prepare( "SELECT * FROM Client_Spr WHERE Name=:Name");
        query.bindValue(":Name", str);
        query.exec();
    }


    if (!query.next()) {
        query.prepare("INSERT INTO Client_Spr (id, Name, Count) "
                  "VALUES (:id, :Name, :Count)");
        query.bindValue(":Count", 1);
        query.bindValue(":Name", str);
        query.exec();
    } else {
        if(!query.next()) {
            query.prepare( "UPDATE Client_Spr SET Count = Count+1 WHERE Name=:Name");
            query.bindValue(":Name", str);
            query.exec();
        }
    }
    model->submitAll();
    ui->SubmitAdd->setEnabled(false);
    ui->Count->setEnabled(true);
}

void Booking::on_Count_clicked() {
    int selectedRow = ui->tableView->currentIndex().row();
    QString str = model->index(selectedRow,1).data().toString();
    QString id = model->index(selectedRow,0).data().toString();
    QSqlQuery query;
    QString direction = model->index(selectedRow,2).data().toString();
    QString classBron = model->index(selectedRow, 4).data().toString();
    QString hotelClass = model->index(selectedRow, 5).data().toString();
    qDebug() << direction;
    int index;
    int counter;
    int index_classBron;
    int index_hotelClass;
    query.exec("SELECT id FROM HotelClass_Spr WHERE Name='"+hotelClass+"'");
    if (query.next()) {
        index_hotelClass = query.value(0).toInt();
    }
    query.exec("SELECT id FROM ClassBron_Spr WHERE Name='"+classBron+"'");
    if (query.next()) {
        index_classBron = query.value(0).toInt();
    }

    query.prepare( "SELECT id FROM Tour_Spr WHERE Direction=:Direction");
    query.bindValue(":Direction", direction);
    query.exec();
    if (query.next()) {
        index = query.value(0).toInt();
        query.exec("SELECT COUNT(*) FROM Bron_Opers WHERE id_DirectionBron = '"+QString::number(index)+"'");
        if (query.next()) {
            counter = query.value(0).toInt();
            qDebug() << counter;
        }
    }
    query.exec("SELECT Coefficient FROM Coefficient_Spr WHERE '"+QString::number(counter)+"' >= left AND '"+QString::number(counter)+"' <= right");
    float coefficient;
    if (query.next()) {
        coefficient = query.value(0).toFloat();
        qDebug() << coefficient;
    }
    int day_price;
    query.prepare("SELECT Day_Price FROM Tour_Spr WHERE Direction=:Direction AND id_ClassBron=:id_ClassBron AND id_HotelClass=:id_HotelClass");
    query.bindValue(":Direction", direction);
    query.bindValue(":id_ClassBron", index_classBron);
    query.bindValue(":id_HotelClass", index_hotelClass);
    query.exec();
    if (query.next()) {
        day_price = query.value(0).toInt();
        qDebug() << day_price;
    }
    qDebug() << id;
    query.prepare("UPDATE Bron_Opers SET Total_Price='"+QString::number(coefficient*day_price)+"' WHERE id='"+id+"'");
    query.exec();
    model->submitAll();
    ui->Count->setEnabled(false);
}

