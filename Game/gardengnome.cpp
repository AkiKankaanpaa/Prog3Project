#include "gardengnome.h"

GardenGnome::GardenGnome(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates):
    MovingActor(gametoken, legal_coordinates)
{
    // Used by the runAwayIfCan method for a random seed
    srand(time(0));
}

void GardenGnome::run_away_if_can()
{
    // If can move in the player's direction, moves there
    if(canMove(returnDirection())){
        move(returnDirection(), 10);
    // Otherwise move in a random direction if possible
    } else {
        int random_dir = rand() % 4;
        if(canMove((direction)random_dir)){
            move((direction)random_dir, 10);
        }
    }
}
