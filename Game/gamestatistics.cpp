#include "gamestatistics.h"

Gamestatistics::Gamestatistics(difficulty chosen_difficulty) :
    current_points_(0), ran_over_maskwearers_(0), ran_over_maskrefusers_(0)
{

}

Gamestatistics::~Gamestatistics()
{

}

void Gamestatistics::change_points(int change)
{
    current_points_ += change;
}

int Gamestatistics::return_points()
{
    return current_points_;
}
