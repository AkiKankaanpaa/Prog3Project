#ifndef PLAYERBUS_H
#define PLAYERBUS_H
#include <QGraphicsRectItem>
#include "actor.h"

class PlayerBus:public Actor
{
public:
    PlayerBus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);

private:
    QGraphicsRectItem* player_;
};

#endif // PLAYERBUS_H
