#ifndef GARDENGNOME_H
#define GARDENGNOME_H

#include "movingactor.h"

class GardenGnome : public MovingActor
{
public:
    GardenGnome(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
    void run_away_if_can();
};

#endif // GARDENGNOME_H
