#include "startupwindow.h"
#include "ui_startupwindow.h"

StartupWindow::StartupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->difficultyBox->addItem("Extremely Easy");
    ui->difficultyBox->addItem("Easy");
    ui->difficultyBox->addItem("Not So Easy");
    ui->difficultyBox->addItem("Uneasy");
}

StartupWindow::~StartupWindow()
{
    delete ui;
}

void StartupWindow::on_startButton_clicked()
{
    if (ui->nameBox->text() != "") {
        accept();
        emit difficultySignal(ui->difficultyBox->currentIndex());
    } else {
        ErrorWindow *nameerror = new ErrorWindow(this, "No name entered.");
        nameerror->show();
    }
}
