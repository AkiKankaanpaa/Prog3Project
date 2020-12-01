#ifndef GARDENGNOME_H
#define GARDENGNOME_H

#include "movingactor.h"

/**
 * @brief The GardenGnome class: A unique actor, which tries to avoid the player. If caught, will
 * immediately reward the player with a very large quantity of points and instantly wins them
 * the game.
 */
class GardenGnome : public MovingActor
{
public:
    /**
     * @brief GardenGnome: Constructor
     * @param gametoken: QGraphicsRectItem pointer, works as the gamepiece on the gameboard.
     * Owner by Actor.
     * @param legal_coordinates: Pointer of std::map<int, std::vector<int>>, has the int x values
     * to correspond with vectors with legal y-values. Owned by Actor.
     */
    GardenGnome(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates);
    /**
     * @brief run_away_if_can: The GardenGnome will run in the same direction as the player at a rapid
     * pace, and if they cannot, they instead attempt to run into one random direction
     */
    void runAwayIfCan();
};

#endif // GARDENGNOME_H
