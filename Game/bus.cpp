#include "bus.h"

Bus::Bus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates):
    Actor(gametoken, legal_coordinates), current_direction_(RIGHT), current_powerup_(NONE)
{
    ;
}

Bus::~Bus()
{
    ;
}

std::pair<int, int> Bus::determineMovement()
{
    std::pair<int, int> current_coordinates = returnCoordinates();

    switch (current_direction_)  {
        case RIGHT:
            current_coordinates.first += 10;
            break;

        case LEFT:
            current_coordinates.first -= 10;
            break;

        case UP:
            current_coordinates.second -= 10;
            break;

        case DOWN:
            current_coordinates.second += 10;
            break;

        default:
            ;
    }
    return current_coordinates;
}
