#include "movingactor.h"

MovingActor::MovingActor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates):
    Actor(gametoken, coordinates), current_direction_(RIGHT)
{

}

MovingActor::~MovingActor()
{

}

bool MovingActor::canMove(direction dir)
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

    auto y_vec = returnLegalCoordinates()->at(current_coordinates.first);
    if (std::count(y_vec.begin(), y_vec.end(), current_coordinates.second)){
        return true;
    }
    return false;
}

void MovingActor::move(direction dir, int amount)
{
    if(dir == RIGHT){
        returnSelf()->setPos(returnSelf()->x() + amount, returnSelf()->y());
    } else if(dir == LEFT) {
        returnSelf()->setPos(returnSelf()->x() - amount, returnSelf()->y());
    } else if(dir == UP){
        returnSelf()->setPos(returnSelf()->x(), returnSelf()->y() - amount);
    } else {
        returnSelf()->setPos(returnSelf()->x(), returnSelf()->y() + amount);
    }
}
