#include "playerbus.h"

PlayerBus::PlayerBus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates): Actor(gametoken, legal_coordinates),
    current_direction_(RIGHT)
{
    ;
}

PlayerBus::~PlayerBus()
{
    ;
}

void PlayerBus::set_direction(direction dir)
{
    current_direction_ = dir;
}

direction PlayerBus::return_direction()
{
    return current_direction_;
}

std::pair<int, int> PlayerBus::determine_movement()
{
    std::pair<int, int> current_coordinates = return_coordinates();

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
