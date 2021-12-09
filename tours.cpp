#include "tours.h"
#include "ui_tours.h"
#include "comboboxitemdelegate.h"
#include "checkboxdelegate.h"

Tours::Tours(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tours)
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
    CheckBoxDelegate *delegate = new CheckBoxDelegate();
    model->setTable("Tour_Spr");
    SetHeader(model);
    model->setRelation(2, QSqlRelation("ClassBron_Spr", "id", "Name"));
    auto *eqCa = new ComboBoxItemDelegate(ui->tableView, "Name", "ClassBron_Spr");
    ui->tableView->setItemDelegateForColumn(2, eqCa);
    model->setRelation(3, QSqlRelation("HotelClass_Spr", "id", "Name"));
    auto *eqCb = new ComboBoxItemDelegate(ui->tableView, "Name", "HotelClass_Spr");
    ui->tableView->setItemDelegateForColumn(3, eqCb);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);     // Устанавливаем модель на TableView
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setItemDelegateForColumn(6, delegate);
    model->select(); // Делаем выборку данных из таблицы
}

Tours::~Tours()
{
    delete ui;
}

void Tours::SetHeader(QSqlTableModel *headermodel) {
    headermodel->setHeaderData(1, Qt::Horizontal, "Направление");
    headermodel->setHeaderData(2, Qt::Horizontal, "Тур Класс");
    headermodel->setHeaderData(3, Qt::Horizontal, "Класс отеля");
    headermodel->setHeaderData(4, Qt::Horizontal, "Кол-во людей");
    headermodel->setHeaderData(5, Qt::Horizontal, "Цена за сутки");
}

void Tours::on_Add_clicked() {
    qDebug() << model->insertRow(model->rowCount());
}

void Tours::on_Delete_clicked() {
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >= 0) {
        qDebug() << model->removeRow(selectedRow);
    } else {
        qDebug() << "No Row selected!";
    }
}

void Tours::on_Submit_clicked() {
    model->submitAll();
}
