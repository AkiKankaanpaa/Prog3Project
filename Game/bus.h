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
     * @brief Bus
     * @param gametoken: Acts as the rectangular object that is seeable within the game
     * that represents the playable character.
     * @param legal_coordinates: A pointer to a map, used by methods within the Actor
     * class to determine which direction
     */
    Bus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
    ~Bus();
    void setDirection(direction dir) {current_direction_ = dir;};
    direction returnDirection() {return current_direction_;};
    powerup returnCurrentPowerup() {return current_powerup_;};
    std::pair<int, int> determineMovement();

private:
    direction current_direction_;
    powerup current_powerup_;
};

#endif // BUS_H
