#ifndef BUS_H
#define BUS_H
#include <QGraphicsRectItem>
#include "actor.h"

enum powerup {RAGE_IMMUNITY, POINTS_MULTIPLIER, DISEASE_IMMUNITY};

class Bus : public Actor
{
public:
    Bus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
    ~Bus();
    void setDirection(direction dir);
    direction returnDirection();
    std::pair<int, int> determineMovement();

private:
    direction current_direction_;
};

#endif // BUS_H
