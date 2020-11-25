#include "actor.h"

Actor::Actor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates)
{
    gametoken_ = gametoken;
    legal_coordinates_ = coordinates;
}

bool Actor::can_move(direction dir)
{
    auto current_coordinates = return_coordinates();

    qDebug() << "here2";

    if(dir == RIGHT){
        current_coordinates.first += 10;
    } else if(dir == LEFT) {
        current_coordinates.first -= 10;
    } else if(dir == UP){
        current_coordinates.second += 10;
    } else {
        current_coordinates.second -= 10;
    }

    qDebug() << QString::number(current_coordinates.first) << QString::number(current_coordinates.second);

    auto y_vec = legal_coordinates_->at(current_coordinates.first);



//    for (std::map<int, std::vector<int>>::iterator it = legal_coordinates_->begin(); it != legal_coordinates_->end(); ++it)
//    {
//        qDebug() << QString::number(it->first);
//    }
    qDebug() << "kys5";
    return true;

}

std::pair<int, int> Actor::return_coordinates()
{
    return std::pair<int, int>(static_cast<int>(gametoken_->x()), static_cast<int>(gametoken_->y()));
}

std::map<int, std::vector<int> >& Actor::return_map()
{
    return *legal_coordinates_;
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

