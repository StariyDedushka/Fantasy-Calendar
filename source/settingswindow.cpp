#include "include/settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}
