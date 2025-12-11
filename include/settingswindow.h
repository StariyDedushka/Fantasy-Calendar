#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
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
    void cb_months_currentIndexChanged(quint16 id);
    void sb_dpm_valueChanged(int days, const QString& month);
    void cb_days_currentIndexChanged(quint16 id);
    void cb_days_editTextChanged(quint16 id, const QString &newName);
    void cb_days_currentTextChanged(quint16 id, const QString& newName);
    void btn_addDay_clicked();
    void btn_removeDay_clicked();

    void cb_months_editTextChanged(quint16 id, const QString &newName);
    void btn_addMonth_clicked();
    void btn_removeMonth_clicked();

    void sb_secPerMin_valueChanged(int spm);
    void sb_minPerHour_valueChanged(int mph);
    void sb_hourPerDay_valueChanged(int hpd);

    void cb_eventGroups_currentIndexChanged(quint16 id);
    void cb_eventGroups_editTextChanged(quint16 id, const QString &newGroup);
    void colorSelected(QColor color);

    void cb_configs_currentIndexChanged(const QString &config);
    void cb_configs_editTextChanged(quint16 id, const QString &newConfig);
    void btn_loadConfig_clicked(const QString& config);
    void btn_saveConfig_clicked(const QString& config);
    void btn_addConfig_clicked();
    void btn_removeConfig_clicked();

    void btn_apply_clicked();
    void btn_cancel_clicked();

private:
    Ui::SettingsWindow *ui;
public:
    SettingsWindow(QWidget *parent = nullptr);
    void setGlobalTime(CustomDateTime *globalTime);
private slots:
    void on_cb_days_currentIndexChanged(int index);
    void on_btn_addDay_clicked();
    void on_btn_removeDay_clicked();

    void on_cb_months_currentIndexChanged(int index);
    void on_btn_removeMonth_clicked();
    void on_btn_addMonth_clicked();
    void on_sb_dpm_valueChanged(int arg1);

    void on_sb_secPerMin_valueChanged(int arg1);
    void on_sb_minPerHour_valueChanged(int arg1);
    void on_sb_hourPerDay_valueChanged(int arg1);

    void on_cb_eventGroups_currentIndexChanged(int index);

    void on_btn_setColor_clicked();

    void on_cb_configs_currentIndexChanged(int index);
    void on_btn_loadConfig_clicked();
    void on_btn_saveConfig_clicked();
    void on_lineEdit_configName_editingFinished();
    void on_btn_removeConfig_clicked();
    void on_btn_addConfig_clicked();

    void on_btn_apply_clicked();
    void on_btn_cancel_clicked();

};

#endif // SETTINGSWINDOW_H
