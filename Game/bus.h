#ifndef BUS_H
#define BUS_H
#include <QGraphicsRectItem>
#include "actor.h"

enum powerup {NONE, RAGE_IMMUNITY, POINTS_MULTIPLIER, DISEASE_IMMUNITY};


/**
 * @brief The Bus class is used as the main-character within the game.
 *
 * The class provides methods on setting the continued direction of the Bus, as well as for
 * determining the spot the bus will travel to next with it current direction.
 */
class Bus : public Actor
{
public:
    /**
     * @brief Bus: Constructor
     * @param gametoken: Acts as the rectangular object that is seeable within the game
     * that represents the playable character.
     * @param legal_coordinates: A pointer to a map, used by methods within the Actor
     * class to determine if the next position to which the bus is moving to is legal.
     */
    Bus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
    
    /**
     * @brief Bus~: Destructor 
     */
    ~Bus();
    
    /**
     * @brief setDirection: Sets the direction in which the bus will next move.
     * @param dir: Direction enum, is set within the current_direction_ private variable as the
     * current moving direction. Choices are at 90 degree angles.
     */
    void setDirection(direction dir) {current_direction_ = dir;};
    
    /**
     * @brief returnDirection
     * @return direction, returns the current moving direction of the bus.
     */
    direction returnDirection() {return current_direction_;};
    powerup returnCurrentPowerup() {return current_powerup_;};
    std::pair<int, int> determineMovement();

private:
    direction current_direction_;
    powerup current_powerup_;
};

#endif // BUS_H
