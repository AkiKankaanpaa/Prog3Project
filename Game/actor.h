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
    ~Actor();
    bool canMove(direction dir);
    std::pair<int, int> returnCoordinates();
    QGraphicsRectItem* returnSelf();

public slots:
    void move(direction dir, int amount);

private:
    std::map<int, std::vector<int>>* legal_coordinates_;
    QGraphicsRectItem* gametoken_;
};

#endif // ACTOR_H
