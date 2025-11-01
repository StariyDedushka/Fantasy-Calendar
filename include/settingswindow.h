#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include "ui_settings.h"
#include "settings.h"
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class SettingsWindow;
}
QT_END_NAMESPACE

class SettingsWindow : public QWidget
{
    Q_OBJECT
signals:
    void cb_months_currentIndexChanged(const QString &month);
    void sb_dpm_valueChanged(int arg1);
    void cb_days_currentIndexChanged(const QString &day);
    void cb_days_editTextChanged(const QString &newDay);
    void cb_months_editTextChanged(const QString &newMonth);
    void sb_secPerMin_valueChanged(int spm);
    void sb_minPerHour_valueChanged(int mph);
    void sb_hourPerDay_valueChanged(int hpd);
    void cb_eventGroups_currentIndexChanged(const QString &group);
    void cb_eventGroups_editTextChanged(const QString &newGroup);
    void colorSelected(QColor color);
    void pushButton_clicked();
    void cb_configs_currentIndexChanged(const QString &config);
    void cb_configs_editTextChanged(const QString &newConfig);
    void btn_loadConfig_clicked(const QString& config);
    void btn_saveConfig_clicked(const QString& config);
    void btn_apply_clicked();
    void btn_cancel_clicked();

private:
    Ui::SettingsWindow *ui;
    Settings *settings;
public:
    SettingsWindow(QWidget *parent = nullptr);
    void setGlobalTime(CustomDateTime *globalTime);
private slots:
    void on_cb_months_currentIndexChanged(int index);
    void on_sb_dpm_valueChanged(int arg1);
    void on_cb_days_currentIndexChanged(int index);
    void on_cb_days_editTextChanged(const QString &arg1);
    void on_cb_months_editTextChanged(const QString &arg1);
    void on_sb_secPerMin_valueChanged(int arg1);
    void on_sb_minPerHour_valueChanged(int arg1);
    void on_sb_hourPerDay_valueChanged(int arg1);
    void on_cb_eventGroups_currentIndexChanged(int index);
    void on_cb_eventGroups_editTextChanged(const QString &arg1);
    void on_btn_setColor_clicked();
    void on_cb_configs_currentIndexChanged(int index);
    void on_cb_configs_editTextChanged(const QString &arg1);
    void on_btn_loadConfig_clicked();
    void on_btn_saveConfig_clicked();
    void on_btn_apply_clicked();
    void on_btn_cancel_clicked();
};

#endif // SETTINGSWINDOW_H
