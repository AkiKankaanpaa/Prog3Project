#include "actor.h"

Actor::Actor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates):
    legal_coordinates_(coordinates),gametoken_(gametoken)

{

}

Actor::~Actor()
{
    ;
}

bool Actor::canMove(direction dir)
{
    auto current_coordinates = returnCoordinates();

    if(dir == RIGHT){
        current_coordinates.first += 10;
    } else if(dir == LEFT) {
        current_coordinates.first -= 10;
    } else if(dir == UP){
        current_coordinates.second -= 10;
    } else {
        current_coordinates.second += 10;
    }

    auto y_vec = legal_coordinates_->at(current_coordinates.first);
    if (std::count(y_vec.begin(), y_vec.end(), current_coordinates.second)){
        return true;
    }
    return false;

}

std::pair<int, int> Actor::returnCoordinates()
{
    return std::pair<int, int>(static_cast<int>(gametoken_->x()), static_cast<int>(gametoken_->y()));
}

QGraphicsRectItem *Actor::returnSelf()
{
    return gametoken_;
}

void Actor::move(direction dir, int amount)
{
    if(dir == RIGHT){
        gametoken_->setPos(gametoken_->x() + amount, gametoken_->y());
    } else if(dir == LEFT) {
        gametoken_->setPos(gametoken_->x() - amount, gametoken_->y());
    } else if(dir == UP){
        gametoken_->setPos(gametoken_->x(), gametoken_->y() - amount);
    } else {
        gametoken_->setPos(gametoken_->x(), gametoken_->y() + amount);
    }
}

