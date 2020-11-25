#ifndef ACTOR_H
#define ACTOR_H

#include <QGraphicsRectItem>
#include <QDebug>
#include <vector>
#include <algorithm>

enum direction {RIGHT, LEFT, UP, DOWN};

class Actor
{
public:
    Actor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates);
    bool can_move(direction dir);
    std::pair<int, int> return_coordinates();
    std::map<int, std::vector<int>>& return_map();

public slots:
    void move(direction dir);

private:
    QGraphicsRectItem* gametoken_;
    std::map<int, std::vector<int>>* legal_coordinates_;
};

#endif // ACTOR_H