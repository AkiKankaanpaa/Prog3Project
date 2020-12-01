#ifndef ACTOR_H
#define ACTOR_H

#include <QGraphicsRectItem>
#include <QDebug>
#include <vector>
#include <algorithm>


/**
 * @brief The Actor class in inherited by all of the actors.
 *
 *  The class provides methods on returning information on each individual object who
 * inherits from this class.
 */
class Actor
{
public:
    /**
     * @brief Actor: Constructor
     * @param gametoken: QGraphicsRectItem pointer, works as the gamepiece on the gameboard.
     * @param coordinates: Pointer of std::map<int, std::vector<int>>, has the int x values
     * to correspond with vectors with legal y-values.
     */
    Actor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates);

    /**
     * @brief ~Actor: Destructor
     */
    virtual ~Actor();

    /**
     * @brief returnCoordinates: Returns the coordinates as a pair <x, y>
     * @return pair<x, y>, returns as int after static_cast
     */
    std::pair<int, int> returnCoordinates();

    /**
     * @brief returnSelf: Returns the QGraphicsRectItem pointer which represents the entity on the
     * gameboard
     * @return QGraphicsRectItem pointer,
     */
    QGraphicsRectItem* returnSelf() {return gametoken_;};

    /**
     * @brief returnLegalCoordinates: Returns the std::map<int, std::vector<int>> pointer which is used
     * for various moving methods by moving actors
     * @return std::map<int, std::vector<int>>, legal coordinates
     */
    std::map<int, std::vector<int>>* returnLegalCoordinates() {return legal_coordinates_;};

private:
    // Legal Coordinates as x vector<y>
    std::map<int, std::vector<int>>* legal_coordinates_;

    // This entity's QGraphicsRectItem
    QGraphicsRectItem* gametoken_;

};

#endif // ACTOR_H
