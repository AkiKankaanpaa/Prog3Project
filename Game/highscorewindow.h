#ifndef HIGHSCOREWINDOW_H
#define HIGHSCOREWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QDebug>

namespace Ui {
class Highscorewindow;
}

class Highscorewindow : public QWidget
{
    Q_OBJECT

public:
    explicit Highscorewindow(QWidget *parent = nullptr, std::map<std::string, int>* scores = nullptr);
    ~Highscorewindow();

private:
    Ui::Highscorewindow *ui;
    std::vector<std::pair<std::string, int> > createScorePairs(std::map<std::string, int>* scoremap);

    std::map<std::string, int>* scoremap_;
    std::vector <std::pair<QLabel*, QLabel*>> label_vec_;
};

#endif // HIGHSCOREWINDOW_H
