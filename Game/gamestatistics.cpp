#include "gamestatistics.h"

Gamestatistics::Gamestatistics() :
    current_points_(0), current_rage_(900), current_passengers_(0), total_nysses_(0),
    remaining_nysses_(0), lost_nysses_(0), total_points_(0)
{

}

Gamestatistics::~Gamestatistics()
{
    srand(time(0));
}

int Gamestatistics::changeRage(int change)
{
    if ((current_rage_ + change) > 900) {
        current_rage_ = 900;
    }
    else {
        current_rage_ += change;
    }
    return 160 - current_rage_/6; //rage is divided by 6 to make the rage bar last longer
}

int Gamestatistics::rageDecay()
{
    current_rage_ -= rage_decay_amount_;
    return 160 - current_rage_/6; //rage is divided by 6 to make the rage bar last longer
}

void Gamestatistics::doesDiseaseSpread()
{
    int dead_passengers = 0;
    for (int i = 0; i < current_passengers_; ++i) {
        if ((1 + rand() % 10) < 3) {
            ++dead_passengers;
        }
    }
    passengerDied(dead_passengers);
}

void Gamestatistics::setGameDifficulty(difficulty dif)
{
    switch (dif)  {
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

