#include "gardengnome.h"

GardenGnome::GardenGnome(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates):
    MovingActor(gametoken, legal_coordinates)
{
    srand(time(0));
}

void GardenGnome::runAwayIfCan()
{
    if(canMove(returnDirection())){
        move(returnDirection(), 10);
    } else {
        int random_dir = rand() % 4;
        if(canMove((direction)random_dir)){
            move((direction)random_dir, 10);
        }
    }
}
