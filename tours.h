#ifndef TOURS_H
#define TOURS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QHeaderView>
#include <QCheckBox>

#include <QDialog>

namespace Ui {
class Tours;
}

class Tours : public QDialog
{
    Q_OBJECT

public:
    explicit Tours(QWidget *parent = nullptr);
    void SetHeader(QSqlTableModel *headermodel);
    ~Tours();

private:
    Ui::Tours *ui;
    QSqlDatabase    db;
    QSqlRelationalTableModel *model;

private slots:
    void on_Add_clicked();
    void on_Delete_clicked();
    void on_Submit_clicked();
};

#endif // TOURS_H
