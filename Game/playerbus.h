#ifndef PLAYERBUS_H
#define PLAYERBUS_H
#include <QGraphicsRectItem>
#include "actor.h"

class PlayerBus : public Actor
{
public:
    PlayerBus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
    ~PlayerBus();
    void set_direction(direction dir);
    direction return_direction();
    std::pair<int, int> determine_movement();

private:
    direction current_direction_;
};

#endif // PLAYERBUS_H
