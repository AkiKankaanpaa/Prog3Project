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
     * @param gametoken: QGraphicsRectItem, works as the gamepiece on the gameboard.
     * @param coordinates
     */
    Actor(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* coordinates);
    virtual ~Actor();
    std::pair<int, int> returnCoordinates();
    QGraphicsRectItem* returnSelf() {return gametoken_;};
    std::map<int, std::vector<int>>* returnLegalCoordinates() {return legal_coordinates_;};

private:
    std::map<int, std::vector<int>>* legal_coordinates_;
    QGraphicsRectItem* gametoken_;

};

#endif // ACTOR_H
