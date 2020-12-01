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

/**
 * @brief The gamestate enum: Used to determine which pixmap to use for the gameboard
 */
enum gamestate {RUNNING, VICTORY, RAGE, CRASH, GNOMED};

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class: This class controls the heart of the game, owns all of the actor-type
 * entities as well as controls all of the timers
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow: Constructor
     * @param parent: none
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
      * @brief ~MainWindow(): Destructor
      */
    ~MainWindow();

    /**
     * @brief keyPressEvent: overriden from the basemethod, this method takes the user's
     * key strokes and interprets them to act on the gameboard through the Bus-type player_
     * @param event: Keypress of any sort
     */
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    /**
     * @brief createGame: Initializes a game and it's values, differently depending on if it is
     * the first game or not
     * @param chosen_difficulty: the difficulty setting chosen by the user
     */
    void createGame(int chosen_difficulty);

private slots:
    /**
     * @brief tickHandler: Handles all movement of all entities that are capable of it.
     */
    void tickHandler();

private:
    /**
     * @brief readCoordinates: Reads the coordinates from the tamperecoordinates.txt and creates
     * the legal_coordinates_ map, which is used to determine legal movement on the gameboard
     */
    void readCoordinates();

    /**
     * @brief insertCoordinates: Used by the readCoordinates function
     * @param x_line: one line from the tamperecoordinates.txt
     */
    void insertCoordinates(std::string x_line);

    /**
     * @brief spawnGamepieces: Randomly spawns Gamepiece-type entities based on the parameters
     * determined by the chosen_difficulty, spreads them out, as well as adds pointers to them
     * vector list_of_gamepieces_
     * @param chosen_difficulty
     * @return
     */
    int spawnGamepieces(difficulty chosen_difficulty);

    void setDifficultySettings(difficulty chosen_difficulty);

    void checkPedestrianCollision();

    void endGame(gamestate condition);

    std::map<int, std::vector<int>>* legal_coordinates_;

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
