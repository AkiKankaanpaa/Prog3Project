#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "actor.h"

class Pedestrian : public Actor
{
public:
    Pedestrian(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
private:
    QGraphicsRectItem* pedestrian_;
};

#endif // PEDESTRIAN_H
