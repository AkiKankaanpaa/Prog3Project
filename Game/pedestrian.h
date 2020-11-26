#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "actor.h"

enum mask {YES, NO};

class Pedestrian : public Actor
{
public:
    Pedestrian(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates, mask mask_status);
private:
    QGraphicsRectItem* pedestrian_;
    std::map<int, std::vector<int>>* legal_coordinates_;
    mask mask_status_;
};

#endif // PEDESTRIAN_H
