#include "highscorewindow.h"
#include "ui_highscorewindow.h"

Highscorewindow::Highscorewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Highscorewindow)
{
    ui->setupUi(this);
}

Highscorewindow::~Highscorewindow()
{
    delete ui;
}
