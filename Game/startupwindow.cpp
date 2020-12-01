#include "startupwindow.h"
#include "ui_startupwindow.h"

StartupWindow::StartupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupWindow)
{
    ui->setupUi(this);

    // removes the helper questionmark from the top right
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Adding difficulties
    ui->difficultyBox->addItem("Extremely Easy");
    ui->difficultyBox->addItem("Easy");
    ui->difficultyBox->addItem("Not Easy");
    ui->difficultyBox->addItem("Uneasy");
}

StartupWindow::~StartupWindow()
{
    delete ui;
}

void StartupWindow::on_startButton_clicked()
{
    // If the name line-edit is not empty, starts the game
    if (ui->nameBox->text() != "") {
        accept();
        emit difficultySignal(ui->difficultyBox->currentIndex(), ui->nameBox->text());
    // Otherwise, makes a popup error
    } else {
        ErrorWindow *nameerror = new ErrorWindow(this, "No name entered.");
        nameerror->show();
    }
}

void StartupWindow::on_cancelButton_clicked()
{
    emit rejected();
}
