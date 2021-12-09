#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->lightPushButton->setEnabled(false);
}

void Settings::on_darkPushButton_clicked()
{
    // Создаём палитру для тёмной темы оформления
    QPalette darkPalette;

    // Настраиваем палитру для цветовых ролей элементов интерфейса
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::black);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::black);
    darkPalette.setColor(QPalette::ToolTipText, Qt::black);
    darkPalette.setColor(QPalette::Text, Qt::red);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::black);
    darkPalette.setColor(QPalette::BrightText, Qt::black);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::red);

    // Устанавливаем данную палитру
    qApp->setPalette(darkPalette);
    ui->darkPushButton->setEnabled(false);
    ui->lightPushButton->setEnabled(true);
}

void Settings::on_lightPushButton_clicked()
{
    // Для возврата к светлой палитре достаточно
    // будет установить стандартную палитру из темы оформления
    qApp->setPalette(style()->standardPalette());
    ui->lightPushButton->setEnabled(false);
    ui->darkPushButton->setEnabled(true);
}

Settings::~Settings()
{
    delete ui;
}
