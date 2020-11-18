#include "startupwindow.h"
#include "ui_startupwindow.h"

StartupWindow::StartupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->difficultyBox->addItem("I'm Too Young to Die");
    ui->difficultyBox->addItem("Hurt Me Plenty");
    ui->difficultyBox->addItem("Ultra Violence");
    ui->difficultyBox->addItem("US Election");
}

StartupWindow::~StartupWindow()
{
    delete ui;
}

void StartupWindow::on_startButton_clicked()
{
    if (ui->nameBox->text() != "") {
        ;
    } else {
        ErrorBox *nameerror = new ErrorBox(this, "No name entered.");
        nameerror->show();
    }
}
