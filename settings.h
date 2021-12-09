#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;

private slots:
    // Слот обработчик клика кнопки для установки тёмного оформления
    void on_darkPushButton_clicked();
    // Слот обработчик клика кнопки для установки светлого оформления
    void on_lightPushButton_clicked();
};

#endif // SETTINGS_H
