#ifndef HIGHSCOREWINDOW_H
#define HIGHSCOREWINDOW_H

#include <QWidget>

namespace Ui {
class Highscorewindow;
}

class Highscorewindow : public QWidget
{
    Q_OBJECT

public:
    explicit Highscorewindow(QWidget *parent = nullptr);
    ~Highscorewindow();

private:
    Ui::Highscorewindow *ui;
};

#endif // HIGHSCOREWINDOW_H
