#ifndef BOOKING_H
#define BOOKING_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QHeaderView>

namespace Ui {
class Booking;
}

class Booking : public QDialog
{
    Q_OBJECT

public:
    explicit Booking(QWidget *parent = nullptr);
    void SetHeader(QSqlTableModel *headermodel);
    ~Booking();

private:
    Ui::Booking *ui;
    QSqlDatabase    db;
    QSqlRelationalTableModel *model;

private slots:
    void on_Add_clicked();
    void on_Delete_clicked();
    void on_SubmitDelete_clicked();
    void on_SubmitAdd_clicked();
    void on_Count_clicked();
};

#endif // BOOKING_H
