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
#include <QGraphicsItem>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <istream>
#include <pedestrian.h>

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

enum difficulty{ITYD, HMP, UV, USE};

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

public slots:
    void create_game();

private slots:
    void on_downButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_upButton_clicked();

private:
    void spawn_pedestrians(int amount);
    void read_coordinates(int current_level = 1);
    void insert_coordinates(std::string x_line);
    void randomize_pedestrians();
    void check_pedestrian_collision();

    Ui::MainWindow *ui;
    StartupWindow *startup_;
    QGraphicsScene *scene_;
    QGraphicsRectItem *player_;
    std::vector<Pedestrian*> list_of_pedestrians_;
    PlayerBus *bus_;
};



#endif // MAINWINDOW_H
