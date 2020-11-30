#include "errorwindow.h"
#include "ui_errorwindow.h"

ErrorWindow::ErrorWindow(QWidget *parent, QString errorstring) :
    QDialog(parent),
    ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);
    ui->errorLabel->setText(errorstring);
}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}



void ErrorWindow::on_okButton_clicked()
{
    close();
}
