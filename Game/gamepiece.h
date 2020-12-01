#ifndef GAMEPIECE_H
#define GAMEPIECE_H


#include "actor.h"

/**
 * @brief The piecetype enum: used to determine which type of piece the Gamepiece is
 */
enum piecetype {MASKLESS, MASKED, POLICE, POWERUP};

/**
 * @brief The Gamepiece class: This class works as the collectable squares within the gameboard
 * that may be collected. They come in four different types which grant different amounts
 * of points, rage and different bonuses.
 */
class Gamepiece : public Actor
{
public:
    /**
     * @brief Gamepiece: Constructor
     * @param gametoken: QGraphicsRectItem pointer, works as the gamepiece on the gameboard.
     * @param legal_coordinates: Pointer of std::map<int, std::vector<int>>, has the int x values
     * to correspond with vectors with legal y-values. Owned by Actor.
     * @param type: piecetype of the specific instance of Gamepiece.
     */
    Gamepiece(QGraphicsRectItem* gametoken, std::map<int,
              std::vector<int>>* legal_coordinates, piecetype type);

    /**
      * @brief ~Gamepiece: Destructor
      */
    ~Gamepiece();

    /**
     * @brief returnPiecetype: returns the piecetype value from piecetype_
     * @return piecetype enum, object's piecetype
     */
    piecetype returnPiecetype() {return piecetype_;};

private:
    piecetype piecetype_;
};

#endif // GAMEPIECE_H
