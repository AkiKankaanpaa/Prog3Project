#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QDialog>
#include "errorbox.h"

namespace Ui {
class StartupWindow;
}

class StartupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartupWindow(QWidget *parent = nullptr);
    ~StartupWindow();

signals:
    void difficulty_signal(int difficulty);

private slots:
    void on_startButton_clicked();

private:
    Ui::StartupWindow *ui;
};

#endif // STARTUPWINDOW_H
