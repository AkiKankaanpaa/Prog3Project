#include "highscorewindow.h"
#include "ui_highscorewindow.h"

Highscorewindow::Highscorewindow(QWidget *parent, std::vector<std::pair<std::string, int>>* scores) :
    QWidget(parent),
    ui(new Ui::Highscorewindow),
    scores_(scores)
{ 
    ui->setupUi(this);
    createScorePairs();
}

Highscorewindow::~Highscorewindow()
{
    delete ui;
}

void Highscorewindow::createScorePairs()
{
    ui->firstname->setText(QString::fromStdString(scores_->at(0).first));
    ui->firstpoints->setText(QString::number(scores_->at(0).second));

    ui->secondname->setText(QString::fromStdString(scores_->at(1).first));
    ui->secondpoints->setText(QString::number(scores_->at(1).second));

    ui->thirdname->setText(QString::fromStdString(scores_->at(2).first));
    ui->thirdpoints->setText(QString::number(scores_->at(2).second));

    ui->fourthname->setText(QString::fromStdString(scores_->at(3).first));
    ui->fourthpoints->setText(QString::number(scores_->at(3).second));

    ui->fifthname->setText(QString::fromStdString(scores_->at(4).first));
    ui->fifthpoints->setText(QString::number(scores_->at(4).second));

    ui->sixthname->setText(QString::fromStdString(scores_->at(5).first));
    ui->sixthpoints->setText(QString::number(scores_->at(5).second));

    ui->seventhname->setText(QString::fromStdString(scores_->at(6).first));
    ui->seventhpoints->setText(QString::number(scores_->at(6).second));

    ui->eighthname->setText(QString::fromStdString(scores_->at(7).first));
    ui->eighthpoints->setText(QString::number(scores_->at(7).second));

    ui->ninthname->setText(QString::fromStdString(scores_->at(8).first));
    ui->ninthpoints->setText(QString::number(scores_->at(8).second));

    ui->tenthname->setText(QString::fromStdString(scores_->at(9).first));
    ui->tenthpoints->setText(QString::number(scores_->at(9).second));

}
