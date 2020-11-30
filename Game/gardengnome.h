#ifndef GARDENGNOME_H
#define GARDENGNOME_H

#include "actor.h"

class GardenGnome : public Actor
{
public:
    GardenGnome(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
    void run_away_if_can();
    void setDirection(direction dir) {current_direction_ = dir;};
private:
    direction current_direction_;

};

#endif // GARDENGNOME_H
