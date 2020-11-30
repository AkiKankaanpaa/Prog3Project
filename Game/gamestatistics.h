#ifndef GAMESTATISTICS_H
#define GAMESTATISTICS_H

#include <QDebug>
#include "interfaces/istatistics.hh"

enum difficulty{EXTREMELY_EASY, EASY, NOT_EASY, UNEASY};

class Gamestatistics : public Interface::IStatistics
{
public:
    Gamestatistics(int maskrefuser_amount);
    ~Gamestatistics();

    int return_points() {return current_points_;};
    void change_points(int change) {current_points_ += change;};

    int return_rage() {return current_rage_;};
    void change_rage(int change) {current_rage_ += change;};

    void morePassengers(int num) {current_passengers_ += num;};
    void passengerDied(int num) {current_passengers_ -= num;};

    void reset_maskrefusers(int maximum){remaining_maskrefusers_ = maximum;};
    void maskrefuser_died(){--remaining_maskrefusers_;}

    void newNysse(){++started_games_;};
    void nysseRemoved() {++lost_games_;};
    void nysseLeft() {++won_games_;};

private:
    int current_points_;
    int current_rage_;
    int current_passengers_;

    int remaining_maskrefusers_;

    int started_games_;
    int won_games_;
    int lost_games_;

};

#endif // GAMESTATISTICS_H
