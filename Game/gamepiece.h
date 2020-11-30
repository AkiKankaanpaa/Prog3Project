#ifndef GAMEPIECE_H
#define GAMEPIECE_H


#include "actor.h"

enum piecetype {MASKLESS, MASKED, POLICE, POWERUP};

class Gamepiece : public Actor
{
public:
    Gamepiece(QGraphicsRectItem* gametoken, std::map<int, std::vector<int>>* legal_coordinates, piecetype type);
    ~Gamepiece();
    piecetype return_piecetype() {return piecetype_;};

private:
    piecetype piecetype_;
};

#endif // GAMEPIECE_H
