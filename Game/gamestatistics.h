#ifndef GAMESTATISTICS_H
#define GAMESTATISTICS_H

#include <QDebug>
#include "interfaces/istatistics.hh"

enum difficulty{EXTREMELY_EASY, EASY, NOT_EASY, UNEASY};

class Gamestatistics : public Interface::IStatistics
{
public:
    Gamestatistics(int pedestrian_amount, difficulty chosen_difficulty);
    ~Gamestatistics();

    int return_points() {return current_points_;};
    void change_points(int change) {current_points_ += change;};

    int return_rage() {return current_rage_;};
    int change_rage(int change);

    int rage_decay();

    void morePassengers(int num) {current_passengers_ += num;};
    void passengerDied(int num) {current_passengers_ -= num;};
    int returnPassengers() {return current_passengers_;};

    void reset_remaining_pedestrians(int maximum){remaining_pedestrians_ = maximum;};
    void pedestrian_removed(){--remaining_pedestrians_;}
    int return_pedestrians() {return remaining_pedestrians_;};

    void newNysse(){++total_nysses_;};
    int returnTotalNysses(){return total_nysses_;};
    void nysseRemoved() {++lost_nysses_;};
    int returnRemovedNysses(){return lost_nysses_;};
    void nysseLeft() {++remaining_nysses_;};
    int returnLostNysses() {return remaining_nysses_;};

private:
    int current_points_;
    int current_rage_;
    int current_passengers_;

    int rage_decay_amount_;
    int remaining_pedestrians_;

    int total_nysses_;
    int remaining_nysses_;
    int lost_nysses_;

};

#endif // GAMESTATISTICS_H
