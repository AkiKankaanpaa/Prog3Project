#ifndef BUS_H
#define BUS_H
#include <QGraphicsRectItem>
#include "actor.h"

class Bus : public Actor
{
public:
    Bus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
    ~Bus();
    void set_direction(direction dir);
    direction return_direction();
    std::pair<int, int> determine_movement();

private:
    direction current_direction_;
};

#endif // BUS_H
