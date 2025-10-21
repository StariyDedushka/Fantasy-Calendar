#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include "ui_settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SettingsWindow;
}
QT_END_NAMESPACE

class SettingsWindow : public QWidget
{
    Q_OBJECT
private:
    Ui::SettingsWindow *ui;
public:
    SettingsWindow(QWidget *parent = nullptr);
};

#endif // SETTINGSWINDOW_H
