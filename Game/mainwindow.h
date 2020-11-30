#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamepiece.h"
#include "bus.h"
#include "gamestatistics.h"
#include "startupwindow.h"
#include "errorwindow.h"
#include "gardengnome.h"

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsRectItem>

#include <QTimer>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <utility>
#include <QDebug>

#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include <iostream>
#include <sstream>
#include <fstream>

enum gamestate {RUNNING, VICTORY, RAGE, CRASH};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::map<int, std::vector<int>>* legal_coordinates_;

    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void createGame(int chosen_difficulty, QString name);

private slots:
    void tickHandler();

private:
    void readCoordinates();
    void insertCoordinates(std::string x_line);
    void insertHighscores(std::string x_line);

    int spawnGamepieces(difficulty chosen_difficulty);

    void setDifficultySettings(difficulty chosen_difficulty);

    void checkPedestrianCollision();

    void endGame(gamestate condition);

    Ui::MainWindow *ui;
    StartupWindow *startup_;

    QGraphicsScene *gamescene_;

    QGraphicsScene *ragescene_;
    QGraphicsRectItem *ragemeter_;

    std::map<gamestate, QPixmap>* gameimages_;

    Bus *player_;
    GardenGnome *gnome_;
    std::vector<Gamepiece*> list_of_gamepieces_;

    QTimer* tick_timer_;
    int current_tick_;
    direction queued_direction_;

    Gamestatistics* gamestats_;

    bool game_running_;
};



#endif // MAINWINDOW_H
