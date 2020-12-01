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
     * @param chosen_difficulty: Difficulty enum, determines the spawnrates of the different gamepieces
     * @return int game_end_amount, amount of both MASKLESS and MASKED entities created
     * recorded to Gamestatistics variable current_passengers_
     */
    int spawnGamepieces(difficulty chosen_difficulty);

    /**
     * @brief setDifficultySettings: Changes the current difficulty
     * @param chosen_difficulty: enum difficulty
     */
    void setDifficultySettings(difficulty chosen_difficulty);

    /**
     * @brief checkPedestrianCollision: checks whether or not the player_ would hit a gamepiece
     * entity, if they do, removes it from the field and gains points, rage, or a buff
     */
    void checkGamepieceCollision();

    /**
     * @brief endGame: resets some variables back to either default values, deleted all gamepiece
     * entities, changes the pixmap depending on the ending condition, stops the timer, and rewards end of game
     * points
     * @param condition: determines how the game was ended, and gives out end of game points as well as
     * records it as either a win or a loss of the player in the gamestats_ object.
     */
    void endGame(gamestate condition);

    // Legal Coordinates as x vector<y>
    std::map<int, std::vector<int>>* legal_coordinates_;

    Ui::MainWindow *ui;
    // Start of game setup window. Restarts this window by pressing r when game is not running
    StartupWindow *startup_;

    // The main game area and the entities within it are held within this scene
    QGraphicsScene *gamescene_;

    // Is used to display the rage meter in the top right
    QGraphicsScene *ragescene_;
    // Is the moving part and shows the current amount of rage visually to the user
    QGraphicsRectItem *ragemeter_;

    // Has the addresses of all of the required pixmaps
    std::map<gamestate, QPixmap>* gameimages_;

    // Holds the unique Bus pointer which acts as the player
    Bus *player_;

    // Holds the unique GardenGnome entity pointer
    GardenGnome *gnome_;

    // Holds all of the gamepieces whilst game is running
    std::vector<Gamepiece*> list_of_gamepieces_;

    // Timer used for movement of GardenGnome and Bus
    QTimer* tick_timer_;

    // Current_Tick_ is used to determine when it is legal for the bus to turn (they may queue
    // directions, but they are only updated every 10 pixels.
    int current_tick_;
    // Holds the current queued direction, made with KeyPressEvents
    direction queued_direction_;

    // Holds a large amount of data regarding the current game session / game
    Gamestatistics* gamestats_;

    // Bool of whether or not the game is running at the moment
    bool game_running_;
};



#endif // MAINWINDOW_H
