#include "highscorewindow.h"
#include "ui_highscorewindow.h"

Highscorewindow::Highscorewindow(QWidget *parent, std::map<std::string, int>* scores) :
    QWidget(parent),
    ui(new Ui::Highscorewindow)
{ 
    ui->setupUi(this);
    std::vector<std::pair<std::string, int> > scorepairs = createScorePairs(scores);
    label_vec_ = {{ui->firstname, ui->firstpoints}, {ui->secondname, ui->secondpoints},
                {ui->thirdname, ui->thirdpoints}, {ui->fourthname, ui->fourthpoints},
                {ui->fifthname, ui->fifthpoints}, {ui->sixthname, ui->sixthpoints},
                {ui->seventhname, ui->seventhpoints}, {ui->eighthname, ui->eighthpoints},
                {ui->ninthname, ui->ninthpoints}, {ui->tenthname, ui->tenthpoints}};
}

Highscorewindow::~Highscorewindow()
{
    delete ui;
}

bool compareScore(std::pair<std::string, int>& score_1,
         std::pair<std::string, int>& score_2)
{
    return score_1.second > score_2.second;
}

std::vector<std::pair<std::string, int>> Highscorewindow::createScorePairs(
        std::map<std::string, int>* scoremap)
{
    std::vector<std::pair<std::string, int> > score_pairs;

    for (auto& it : *scoremap) {
        score_pairs.push_back(it);
    }

    sort(score_pairs.begin(), score_pairs.end(), compareScore);
        qDebug() << "here";
//    auto it2 = label_vec_.begin();
//    if (score_pairs.size() == label_vec_.size()) {
//        for (auto it=score_pairs.begin(); it != score_pairs.end(); ++it) {
//            it2->first->setText(QString::fromStdString(it->first));
//            it2->second->setText(QString::number(it->second));
//            ++it2;
//        }


    ui->firstname->setText(QString::fromStdString(score_pairs.at(0).first));
    ui->firstpoints->setText(QString::number(score_pairs.at(0).second));

    ui->secondname->setText(QString::fromStdString(score_pairs.at(1).first));
    ui->secondpoints->setText(QString::number(score_pairs.at(1).second));

    ui->thirdname->setText(QString::fromStdString(score_pairs.at(2).first));
    ui->thirdpoints->setText(QString::number(score_pairs.at(2).second));

    ui->fourthname->setText(QString::fromStdString(score_pairs.at(3).first));
    ui->fourthpoints->setText(QString::number(score_pairs.at(3).second));

    ui->fifthname->setText(QString::fromStdString(score_pairs.at(4).first));
    ui->fifthpoints->setText(QString::number(score_pairs.at(4).second));

    ui->sixthname->setText(QString::fromStdString(score_pairs.at(5).first));
    ui->sixthpoints->setText(QString::number(score_pairs.at(5).second));

    ui->seventhname->setText(QString::fromStdString(score_pairs.at(6).first));
    ui->seventhpoints->setText(QString::number(score_pairs.at(6).second));

    ui->eighthname->setText(QString::fromStdString(score_pairs.at(7).first));
    ui->eighthpoints->setText(QString::number(score_pairs.at(7).second));

    ui->ninthname->setText(QString::fromStdString(score_pairs.at(8).first));
    ui->ninthpoints->setText(QString::number(score_pairs.at(8).second));

    ui->tenthname->setText(QString::fromStdString(score_pairs.at(9).first));
    ui->tenthpoints->setText(QString::number(score_pairs.at(9).second));

    return score_pairs;
}
