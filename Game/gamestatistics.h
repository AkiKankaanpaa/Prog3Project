#ifndef GAMESTATISTICS_H
#define GAMESTATISTICS_H

#include <QDebug>
#include "interfaces/istatistics.hh"

/**
 * @brief The difficulty enum: Used to contain all possible difficulties
 */
enum difficulty {EXTREMELY_EASY, EASY, NOT_EASY, UNEASY};
/**
 * @brief The Gamestatistics class: This class contains everything regarding to points
 * and the functions to manage them.
 */
class Gamestatistics : public Interface::IStatistics
{
public:
    /**
     * @brief Gamestatistics
     */
    Gamestatistics();
    ~Gamestatistics();
    /**
     * @brief returnPoints: returns the current points in the current game
     * @return int current_points_: contains the amount of points in the current game
     */
    int returnPoints() {return current_points_;};
    /**
     * @brief changePoints: changes the current_points_ by the value given to the param
     * @param change: int that determines the amount that gets added to current_points_
     */
    void changePoints(int change) {current_points_ += change;};
    /**
     * @brief returnTotalPoints: Returns the total points earned through all of the
     * rounds that the game has been played on that session
     * @return int total_points_: amount of points earned through all of the rounds
     */
    int returnTotalPoints() {return total_points_;};
    /**
     * @brief changeTotalPoints: Adds int change to total_poins_ counter
     * @param change: amount that gets added to total_points_
     */
    void changeTotalPoints(int change) {total_points_ += change;};
    /**
     * @brief returnRage: Returns the amount of rage left
     * @return int current_rage_: amount of rage currently
     */
    int returnRage() {return current_rage_;};
    /**
     * @brief changeRage: Adds rage to current_rage_, checks that the value cant go
     * over 900
     * @param change: amount that gets added to current_rage_
     * @return int current_rage_: returns the current_rage_ after addition
     */
    int changeRage(int change);
    /**
     * @brief rageDecay: decreases current_rage_ by the amount determined by the
     * game difficulty
     * @return int: return remaining amount of rage
     */
    int rageDecay();
    /**
     * @brief morePassengers: adds passangers to the current_passager_ count
     * @param num: amount of passangers to be added
     */
    void morePassengers(int num) {current_passengers_ += num;};
    /**
     * @brief passengerDied: decreases passangers from the current_passager_ count
     * @param num: amount of passangers to be removed
     */
    void passengerDied(int num) {current_passengers_ -= num;};
    /**
     * @brief returnPassengers: returns the amount of passangers that the player has
     * picked up and that are still alive
     * @return int current_passagers_: the amount of passangers
     */
    int returnPassengers() {return current_passengers_;};
    /**
     * @brief doesDiseaseSpread: randomly rolls individually on all passangers on the
     * bus to see if they get infected and die. If they happen to die it also calls
     * passangerDied function with the amount
     */
    void doesDiseaseSpread();
    /**
     * @brief resetCurrentPassengers: Sets the current_passengers_ count to 0
     */
    void resetCurrentPassengers() {current_passengers_ = 0;};
    /**
     * @brief resetRemainingPedestrians: sets remaining_pedestrians_ to desired value
     * @param maximum: value to set the remaining_pedestrians_ to
     */
    void resetRemainingPedestrians(int maximum) {remaining_pedestrians_ = maximum;};
    /**
     * @brief removePedestrian: decreases remaining_pedestrians_ count by one
     */
    void removePedestrian() {--remaining_pedestrians_;}
    /**
     * @brief returnRemainingPedestrians: returns the amount of pedestrians left in
     * the game
     * @return int remaining_pedestrians_: the amount of pedestrians left
     */
    int returnRemainingPedestrians() {return remaining_pedestrians_;};
    /**
     * @brief newNysse: increments one nysse to total_nysses_ counter
     */
    void newNysse() {++total_nysses_;};
    /**
     * @brief returnTotalNysses: returns the amount of nysses(rounds) used
     * @return int total_nysses_: contains the amount of rounds played
     */
    int returnTotalNysses() {return total_nysses_;};
    /**
     * @brief nysseRemoved: increments one to the lost_nysses_ counter which tracks
     * the amounts of games lost
     */
    void nysseRemoved() {++lost_nysses_;};
    /**
     * @brief returnRemovedNysses: returns the amounts of games lost
     * @return int lost_nysses_: amount of games lost
     */
    int returnRemovedNysses() {return lost_nysses_;};
    /**
     * @brief nysseLeft: increments one to the remaining_nysses_ counter which tracks
     * the amount of games won
     */
    void nysseLeft() {++remaining_nysses_;};
    /**
     * @brief returnLostNysses: returns the amount of games won
     * @return int remaining_nysses_: amount of games won
     */
    int returnLostNysses() {return remaining_nysses_;};
    /**
     * @brief setGameDifficulty: Sets game difficulty which determines how much rage
     * decays on each tick
     * @param dif: contains difficulty
     */
    void setGameDifficulty(difficulty dif);

private:
    /**
     * @brief current_points_: tracks the points on the current round
     */
    int current_points_;
    /**
     * @brief current_rage_: tracks the rage on the current round
     */
    int current_rage_;
    /**
     * @brief current_passengers_: tracks the amount of passangers in the bus on the
     * current round
     */
    int current_passengers_;
    /**
     * @brief rage_decay_amount_: determines the amount of rage lost on each tick
     */
    int rage_decay_amount_;
    /**
     * @brief remaining_pedestrians_: tracks the amount of objects left on the map
     */
    int remaining_pedestrians_;
    /**
     * @brief total_nysses_: tracks the amount of rounds played
     */
    int total_nysses_;
    /**
     * @brief remaining_nysses_: tracks teh amount of rounds won
     */
    int remaining_nysses_;
    /**
     * @brief lost_nysses_: tracks the amount of rounds lost
     */
    int lost_nysses_;
    /**
     * @brief total_points_: tracks the total amount of points acumalated on all
     * rounds
     */
    int total_points_;
};

#endif // GAMESTATISTICS_H
