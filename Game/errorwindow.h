#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>

namespace Ui {
class ErrorWindow;
}

class ErrorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = nullptr, QString errorstring = "");
    ~ErrorWindow();

private slots:
    void on_okButton_clicked();

private:
    Ui::ErrorWindow *ui;
};

#endif // ERRORWINDOW_H
