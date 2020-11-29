#ifndef GAMESTATISTICS_H
#define GAMESTATISTICS_H

#include "interfaces/istatistics.hh"

enum difficulty{ITYD, HMP, UV, USE};

class Gamestatistics : public Interface::IStatistics
{
public:
    Gamestatistics(difficulty chosen_diff);
    ~Gamestatistics();
    void change_points(int change);
    int return_points();

    void passengerDied(int num){};
    void morePassengers(int num){};
    void nysseRemoved(){};
    void newNysse(){};
    void nysseLeft(){};

private:
    int current_points_;
    int ran_over_maskwearers_;
    int ran_over_maskrefusers_;
};

#endif // GAMESTATISTICS_H
