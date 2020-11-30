#include "gamestatistics.h"

Gamestatistics::Gamestatistics(int maskrefuser_amount) :
    current_points_(0), current_rage_(150), current_passengers_(0),
    remaining_maskrefusers_(maskrefuser_amount), started_games_(0), won_games_(0), lost_games_(0)
{

}

Gamestatistics::~Gamestatistics()
{

}

