#include "actor.h"

Actor::Actor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates):
    legal_coordinates_(coordinates),gametoken_(gametoken)
{

}

Actor::~Actor()
{

}

std::pair<int, int> Actor::returnCoordinates()
{
    return std::pair<int, int>(static_cast<int>(gametoken_->x()), static_cast<int>(gametoken_->y()));
}

