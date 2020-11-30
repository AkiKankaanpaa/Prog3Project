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
    explicit Highscorewindow(QWidget *parent = nullptr, std::vector<std::pair<std::string, int>>* scores = nullptr);
    ~Highscorewindow();

private:
    Ui::Highscorewindow *ui;
    std::vector<std::pair<std::string, int>>* scores_;
    void createScorePairs();
};

#endif // HIGHSCOREWINDOW_H
