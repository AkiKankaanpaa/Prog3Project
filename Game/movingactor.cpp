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


    // Switchcase adds 10 in the appropriate coordinate to match where the bus will be
    // after 10 ticks, the direction is checked from current_direction_
    switch (dir)  {

        case RIGHT: {
            current_coordinates.first += 10;
            break;
        }
        case LEFT: {
            current_coordinates.first -= 10;
            break;
        }
        case UP: {
            current_coordinates.second -= 10;
            break;
        }
        case DOWN: {
            current_coordinates.second += 10;
            break;
        }

        default:
            ;
    }
    // Retrieve the y_vector from the to be x-value of the next destination
    auto y_vec = returnLegalCoordinates()->at(current_coordinates.first);
    // If found within the vector, return true, otherwise false
    if (std::count(y_vec.begin(), y_vec.end(), current_coordinates.second)){
        return true;
    }
    return false;
}

void MovingActor::move(direction dir, int amount)
{
    // Switchcase add amount to correct direction to change the location
    // of the QGraphicsRectItem
    switch (dir)  {

        case RIGHT: {
            returnSelf()->setPos(returnSelf()->x() + amount, returnSelf()->y());
            break;
        }
        case LEFT: {
            returnSelf()->setPos(returnSelf()->x() - amount, returnSelf()->y());
            break;
        }
        case UP: {
            returnSelf()->setPos(returnSelf()->x(), returnSelf()->y() - amount);
            break;
        }
        case DOWN: {
            returnSelf()->setPos(returnSelf()->x(), returnSelf()->y() + amount);
            break;
        }

        default:
            ;
    }
}
