#include "errorbox.h"
#include "ui_errorbox.h"

ErrorBox::ErrorBox(QWidget *parent, QString errorstring) :
    QDialog(parent),
    ui(new Ui::ErrorBox)
{
    ui->setupUi(this);
    ui->errorLabel->setText(errorstring);
}

ErrorBox::~ErrorBox()
{
    delete ui;
}



void ErrorBox::on_okButton_clicked()
{
    close();
}
