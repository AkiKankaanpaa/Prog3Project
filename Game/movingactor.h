#ifndef MOVINGACTOR_H
#define MOVINGACTOR_H

#include "actor.h"

/**
 * @brief The direction enum: used to determine the possible directions an actor may move to.
 * Default value for the Bus is RIGHT.
 */
enum direction {RIGHT, LEFT, UP, DOWN};

class MovingActor : public Actor
{
public:
    MovingActor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates);
    virtual ~MovingActor();

    /**
     * @brief canMove
     * @param dir
     * @return
     */
    bool canMove(direction dir);
    void move(direction dir, int amount);

    /**
     * @brief setDirection: Sets the direction in which the bus will next move.
     * @param dir: direction enum, is set within the current_direction_ private variable as the
     * current moving direction. Choices are at 90 degree angles.
     */
    void setDirection(direction dir) {current_direction_ = dir;};

    /**
     * @brief returnDirection: Returns the current direction of the actor
     * @return current_direction_: direction enum, returns the current direction the moving actor
     * is moving
     */
    direction returnDirection() {return current_direction_;};

private:
    // current moving direction
    direction current_direction_;
};

#endif // MOVINGACTOR_H
