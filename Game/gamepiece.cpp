#include "gamepiece.h"

Gamepiece::Gamepiece(QGraphicsRectItem* gametoken,
        std::map<int, std::vector<int>>* legal_coordinates, piecetype piecetype):
        Actor(gametoken, legal_coordinates), piecetype_(piecetype)
{

}


Gamepiece::~Gamepiece()
{
    ;
}
