#include "include/settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(Settings *settings, QWidget *parent)
    : QWidget(parent)
    , m_settings(settings)
    , ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    setupConnections();
}

void SettingsWindow::setupConnections()
{
    connect(this, &SettingsWindow::cb_configs_currentIndexChanged, m_settings, &Settings::configs_currentIndexChanged);
    connect(this, &SettingsWindow::sb_dpm_valueChanged, m_settings, &Settings::dpm_valueChanged);
    connect(this, &SettingsWindow::btn_addConfig_clicked, m_settings, &Settings::btn_addConfig_clicked);
    connect(this, &SettingsWindow::btn_removeConfig_clicked, m_settings, &Settings::btn_removeConfig_clicked);
    connect(m_settings, &Settings::configRemoved, this, &SettingsWindow::on_configRemoved);
    connect(this, &SettingsWindow::sb_secPerMin_valueChanged, m_settings, &Settings::secPerMin_valueChanged);
    connect(this, &SettingsWindow::sb_minPerHour_valueChanged, m_settings, &Settings::minPerHour_valueChanged);
    connect(this, &SettingsWindow::sb_hourPerDay_valueChanged, m_settings, &Settings::hourPerDay_valueChanged);
    connect(this, &SettingsWindow::cb_eventGroups_currentIndexChanged, m_settings, &Settings::eventGroups_currentIndexChanged);
    connect(this, &SettingsWindow::colorSelected, m_settings, &Settings::colorSelected);
    connect(this, &SettingsWindow::btn_loadConfig_clicked, m_settings, &Settings::loadConfig_clicked);
    connect(this, &SettingsWindow::btn_saveConfig_clicked, m_settings, &Settings::saveConfig_clicked);
    connect(this, &SettingsWindow::btn_apply_clicked, m_settings, &Settings::apply_clicked);
    connect(this, &SettingsWindow::btn_cancel_clicked, m_settings, &Settings::cancel_clicked);
    connect(this, &SettingsWindow::btn_addDay_clicked, m_settings, &Settings::addDay_clicked);
}

void SettingsWindow::on_cb_months_currentIndexChanged(int index)
{
    emit cb_months_currentIndexChanged(ui->cb_months->currentText());
}


void SettingsWindow::on_sb_dpm_valueChanged(int days)
{
    emit sb_dpm_valueChanged(days, ui->cb_months->currentText());
}


void SettingsWindow::on_cb_days_currentIndexChanged(int index)
{
    emit cb_days_currentIndexChanged(ui->cb_days->currentText());
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
    emit cb_eventGroups_currentIndexChanged(ui->cb_eventGroups->currentText());
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

void SettingsWindow::on_btn_addDay_clicked()
{
    emit btn_addDay_clicked();
}


void SettingsWindow::on_lineEdit_configName_editingFinished()
{

}


void SettingsWindow::on_btn_removeMonth_clicked()
{

}


void SettingsWindow::on_btn_addMonth_clicked()
{

}


void SettingsWindow::on_btn_removeDay_clicked()
{

}


void SettingsWindow::on_btn_removeConfig_clicked()
{
    LOG(INFO, logger, QString("Emitted remove config signal; index: <%1>, name: <%2>")
                              .arg(ui->cb_configs->currentIndex())
                              .arg(ui->cb_configs->currentText()));

    emit btn_removeConfig_clicked(std::pair<int, QString>(ui->cb_configs->currentIndex(), ui->cb_configs->currentText()));
}

void SettingsWindow::on_configRemoved(int i)
{
    if(i >= 0 && i < ui->cb_configs->count())
    {
        ui->cb_configs->removeItem(i);
        LOG(INFO, logger, QString("Removed item at index %1 from combobox").arg(i));
    }
    else
    {
        LOG(WARN, logger, QString("Invalid index %1 for combobox removal").arg(i));
    }
}

void SettingsWindow::on_btn_addConfig_clicked()
{
    QString configName = ui->lineEdit_configName->text();
    if(configName.isEmpty()) return;

    ui->cb_configs->addItem(configName);
    int index = ui->cb_configs->findText(configName); // Находим актуальный индекс
    emit btn_addConfig_clicked(std::pair<int, QString>(index, configName));
}
