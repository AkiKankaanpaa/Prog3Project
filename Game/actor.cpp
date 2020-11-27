#include "actor.h"

Actor::Actor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates):
    legal_coordinates_(coordinates),gametoken_(gametoken)

{

}

bool Actor::can_move(direction dir)
{
    auto current_coordinates = return_coordinates();

    qDebug() << "here2";

    if(dir == RIGHT){
        current_coordinates.first += 10;
        qDebug() << "moving right";
    } else if(dir == LEFT) {
        current_coordinates.first -= 10;
        qDebug() << "moving left";
    } else if(dir == UP){
        current_coordinates.second -= 10;
        qDebug() << "moving up";
    } else {
        current_coordinates.second += 10;
        qDebug() << "moving down";
    }

    qDebug() << QString::number(current_coordinates.first) << QString::number(current_coordinates.second);
    auto y_vec = legal_coordinates_->at(current_coordinates.first);
    if (std::count(y_vec.begin(), y_vec.end(), current_coordinates.second)){
        return true;
    }
    return false;

}

std::pair<int, int> Actor::return_coordinates()
{
    return std::pair<int, int>(static_cast<int>(gametoken_->x()), static_cast<int>(gametoken_->y()));
}

QGraphicsRectItem *Actor::return_self()
{
    return gametoken_;
}

void Actor::move(direction dir)
{
    if(dir == RIGHT){
        gametoken_->setPos(gametoken_->x() + 10, gametoken_->y());
    } else if(dir == LEFT) {
        gametoken_->setPos(gametoken_->x() - 10, gametoken_->y());
    } else if(dir == UP){
        gametoken_->setPos(gametoken_->x(), gametoken_->y() - 10);
    } else {
        gametoken_->setPos(gametoken_->x(), gametoken_->y() + 10);
    }
}

