#ifndef ERRORBOX_H
#define ERRORBOX_H

#include <QDialog>

namespace Ui {
class ErrorBox;
}

class ErrorBox : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorBox(QWidget *parent = nullptr, QString errorstring = "");
    ~ErrorBox();

private slots:
    void on_okButton_clicked();

private:
    Ui::ErrorBox *ui;
};

#endif // ERRORBOX_H
