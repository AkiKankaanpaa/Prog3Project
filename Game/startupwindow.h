#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QDialog>
#include "errorwindow.h"

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
    void difficultySignal(int difficulty, QString name);

private slots:
    void on_startButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::StartupWindow *ui;
};

#endif // STARTUPWINDOW_H
