#include "gamestatistics.h"

Gamestatistics::Gamestatistics(int pedestrian_amount, difficulty chosen_difficulty) :
    current_points_(0), current_rage_(900), current_passengers_(0),
    remaining_pedestrians_(pedestrian_amount), total_nysses_(0), remaining_nysses_(0), lost_nysses_(0)
{
    switch (chosen_difficulty)  {
        case EXTREMELY_EASY:
            rage_decay_amount_ = 1;
            break;

        case EASY:
            rage_decay_amount_ = 1;
            break;

        case NOT_EASY:
            rage_decay_amount_ = 2;
            break;

        case UNEASY:
            rage_decay_amount_ = 2;
            break;
        default:
            ;
    }
}

Gamestatistics::~Gamestatistics()
{

}

int Gamestatistics::change_rage(int change)
{
    if ((current_rage_ + change) > 900) {
        current_rage_ = 900;
    }
    else {
        current_rage_ += change;
    }
    return 160 - current_rage_/6;
}

int Gamestatistics::rage_decay()
{
    current_rage_ -= rage_decay_amount_;
    return 160 - current_rage_/6;
}

