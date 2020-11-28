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
