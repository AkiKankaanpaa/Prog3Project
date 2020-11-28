#include "pedestrian.h"

Pedestrian::Pedestrian(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates, mask mask_status): Actor(gametoken, legal_coordinates),
     mask_status_(mask_status)
{
    ;
}

Pedestrian::~Pedestrian()
{
    ;
}

mask Pedestrian::return_maskstatus()
{
    return mask_status_;
}


