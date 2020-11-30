#include "bus.h"

Bus::Bus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates):
    MovingActor(gametoken, legal_coordinates), current_powerup_(NONE)
{
    ;
}

std::pair<int, int> Bus::determineMovement()
{
    std::pair<int, int> current_coordinates = returnCoordinates();

    // Switchcase adds 10 in the appropriate coordinate to match where the bus will be
    // after 10 ticks, the direction is checked from current_direction_
    switch (returnDirection())  {
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

void Bus::setCurrentPowerup(powerup power)
{
    current_powerup_ = power;
}
