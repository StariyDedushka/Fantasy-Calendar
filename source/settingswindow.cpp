#include "include/settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}


void SettingsWindow::on_cb_months_currentIndexChanged(int index)
{
    emit cb_months_currentIndexChanged(index);
}


void SettingsWindow::on_sb_dpm_valueChanged(int days)
{
    emit sb_dpm_valueChanged(days, ui->cb_months->currentText());
}


void SettingsWindow::on_cb_days_currentIndexChanged(int index)
{
    emit cb_days_currentIndexChanged(index);
}


void SettingsWindow::on_cb_days_editTextChanged(const QString &arg1)
{
    emit cb_days_editTextChanged(ui->cb_days->currentIndex(), arg1);
}


void SettingsWindow::on_cb_months_editTextChanged(const QString &arg1)
{
    emit cb_months_editTextChanged(ui->cb_months->currentIndex(), arg1);
}


void SettingsWindow::on_sb_secPerMin_valueChanged(int arg1)
{
    emit sb_secPerMin_valueChanged(arg1);
}


void SettingsWindow::on_sb_minPerHour_valueChanged(int arg1)
{
    emit sb_minPerHour_valueChanged(arg1);
}


void SettingsWindow::on_sb_hourPerDay_valueChanged(int arg1)
{
    emit sb_hourPerDay_valueChanged(arg1);
}


void SettingsWindow::on_cb_eventGroups_currentIndexChanged(int index)
{
    emit cb_eventGroups_currentIndexChanged(index);
}


void SettingsWindow::on_cb_eventGroups_editTextChanged(const QString &arg1)
{
    emit cb_eventGroups_editTextChanged(ui->cb_eventGroups->currentIndex(), arg1);
}


void SettingsWindow::on_btn_setColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red, this, "Выбор цвета", QColorDialog::ShowAlphaChannel);
    emit colorSelected(color);
}



void SettingsWindow::on_cb_configs_currentIndexChanged(int index)
{
    emit cb_configs_currentIndexChanged(ui->cb_configs->currentText());
}


void SettingsWindow::on_cb_configs_editTextChanged(const QString &arg1)
{
    emit cb_configs_editTextChanged(ui->cb_configs->currentIndex(), arg1);
}


void SettingsWindow::on_btn_loadConfig_clicked()
{
    emit btn_loadConfig_clicked(ui->cb_configs->currentText());
}


void SettingsWindow::on_btn_saveConfig_clicked()
{
    emit btn_saveConfig_clicked(ui->cb_configs->currentText());
}


void SettingsWindow::on_btn_apply_clicked()
{

}


void SettingsWindow::on_btn_cancel_clicked()
{

}


void SettingsWindow::on_cb_months_currentTextChanged(const QString &arg1)
{

}


void SettingsWindow::on_cb_days_currentTextChanged(const QString &arg1)
{

}


void SettingsWindow::on_cb_eventGroups_currentTextChanged(const QString &arg1)
{

}


void SettingsWindow::on_cb_configs_currentTextChanged(const QString &arg1)
{

}


void SettingsWindow::on_btn_addDay_clicked()
{
    emit btn_addDay_clicked();
}

