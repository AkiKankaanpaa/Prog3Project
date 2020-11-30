#include "gardengnome.h"

GardenGnome::GardenGnome(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates):
    Actor(gametoken, legal_coordinates), current_direction_(RIGHT)
{
    srand(time(0));
}

void GardenGnome::run_away_if_can()
{
    if(canMove(current_direction_)){
        move(current_direction_, 10);
    } else {
        int random_dir = rand() % 4;
        if(canMove((direction)random_dir)){
            move((direction)random_dir, 10);
        }
    }
}
