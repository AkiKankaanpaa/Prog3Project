#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include "startupwindow.h"
#include <QImage>
#include <QGraphicsRectItem>
#include "playerbus.h"
#include "actor.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <istream>
#include <pedestrian.h>
#include <QTimer>
#include <QKeyEvent>

#include <gamestatistics.h>
#include <utility>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include <time.h>
#include <algorithm>

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

    void end_game();

public slots:
    void create_game();

private slots:
    void tick_handler();

private:
    void spawn_pedestrians(int amount);
    void read_coordinates(int current_level = 1);
    void insert_coordinates(std::string x_line);
    void randomize_pedestrians();

    void check_pedestrian_collision();
    std::pair<int, int> determine_bus_movement();

    void reduce_rage(int amount);
    void increase_rage(int amount);

    Ui::MainWindow *ui;
    StartupWindow *startup_;

    QGraphicsScene *scene_;
    QGraphicsScene *ragescene_;
    QGraphicsRectItem *player_;
    QGraphicsRectItem *ragemeter_;
    PlayerBus *bus_;

    std::vector<Pedestrian*> list_of_pedestrians_;

    QTimer* tick_timer_;
    int current_tick_;
    direction queued_direction;

    Gamestatistics* gamestats_;

    int ragetime_;

    bool game_running_;
};



#endif // MAINWINDOW_H
