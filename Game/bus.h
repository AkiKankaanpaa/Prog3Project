#ifndef BUS_H
#define BUS_H
#include "movingactor.h"

/**
 * @brief The powerup enum: used to determine the current powerup. Default-value is NONE,
 * given in constuctor to Bus.
 */
enum powerup {NONE, RAGE_IMMUNITY, POINTS_MULTIPLIER, DISEASE_IMMUNITY};


/**
 * @brief The Bus class is used as the main-character within the game.
 *
 * The class provides methods on setting the continued direction of the Bus, as well as for
 * determining the spot the bus will travel to next with it current direction.
 */
class Bus : public MovingActor
{
public:
    /**
     * @brief Bus: Constructor
     * @param gametoken: Acts as the rectangular object that is seeable within the game
     * that represents the playable character. Owner by Actor
     * @param legal_coordinates: Pointer of std::map<int, std::vector<int>>, has the int x values
     * to correspond with vectors with legal y-values. Owned by Actor.
     */
    Bus(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);

    /**
     * @brief returnCurrentPowerup: Returns which powerup if any are active on the bus.
     * @return current_powerup_: powerup enum, current powerup in current_powerup_ is returned.
     */
    powerup returnCurrentPowerup() {return current_powerup_;};

    /**
     * @brief determineMovement: Returns the point the bus will next move to, in 10 pixel intervals.
     * @return current_coordinates: pair<int, int>, returns the next moving position
     *  in coordinates as pair<x, y>.
     */
    std::pair<int, int> determineMovement();
    void setCurrentPowerup(powerup);

private:
    // current active powerup, can and is by default NONE
    powerup current_powerup_;
};

#endif // BUS_H
