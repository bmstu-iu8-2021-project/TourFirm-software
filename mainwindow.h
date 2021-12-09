#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include "booking.h"
#include "tours.h"
#include "regular.h"
#include "settings.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    Booking *bookingwindow;
    Tours *tourswindow;
    Settings *settingswindow;

public slots:
    void on_Bron_clicked();
    void on_Regulars_clicked();
    void on_Tours_clicked();
    void on_Settings_clicked();
    void on_Quit_clicked();
};

#endif // MAINWINDOW_H
