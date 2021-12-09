#ifndef REGULAR_H
#define REGULAR_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QHeaderView>
#include "QSqlQueryModel"

namespace Ui {
class regular;
}

class regular : public QDialog
{
    Q_OBJECT

public:
    explicit regular(QWidget *parent = nullptr);
    void SetHeader(QSqlTableModel *headermodel);
    ~regular();

private:
    Ui::regular *ui;
    QSqlDatabase    db;
    QSqlQueryModel *model;
};

#endif // REGULAR_H
