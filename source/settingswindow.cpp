#include "include/settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    settings = Settings::getInstance();
}

void SettingsWindow::on_sb_dpw_valueChanged(int arg1)
{

}


void SettingsWindow::on_cb_months_currentIndexChanged(int index)
{

}


void SettingsWindow::on_sb_dpm_valueChanged(int arg1)
{

}


void SettingsWindow::on_cb_days_currentIndexChanged(int index)
{

}


void SettingsWindow::on_cb_days_editTextChanged(const QString &arg1)
{

}


void SettingsWindow::on_cb_months_editTextChanged(const QString &arg1)
{

}


void SettingsWindow::on_sb_secPerMin_valueChanged(int arg1)
{

}


void SettingsWindow::on_sb_minPerHour_valueChanged(int arg1)
{

}


void SettingsWindow::on_sb_hourPerDay_valueChanged(int arg1)
{

}


void SettingsWindow::on_cb_eventGroups_currentIndexChanged(int index)
{

}


void SettingsWindow::on_cb_eventGroups_editTextChanged(const QString &arg1)
{

}


void SettingsWindow::on_btn_setColor_clicked()
{

}



void SettingsWindow::on_cb_configs_currentIndexChanged(int index)
{

}


void SettingsWindow::on_cb_configs_editTextChanged(const QString &arg1)
{

}


void SettingsWindow::on_btn_loadConfig_clicked()
{

}


void SettingsWindow::on_btn_saveConfig_clicked()
{

}

void SettingsWindow::setGlobalTime(CustomDateTime *globalTime)
{
    settings->setGlobalTime(globalTime);
}
