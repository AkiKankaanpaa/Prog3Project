#include <QtTest>
#include "gamestatistics.h"

// add necessary includes here

class testgamestatistics : public QObject
{
    Q_OBJECT

private slots:
    void testGamestatisticsCreationValues();

    void testChangePoints();

    void testChangeRagePositiveOver900();
    void testChangeRageNegative();
    void testChangeRagePositive();

    void testRageDecay();

    void testMorePassengers();
    void testPassengerDied();

    void testResetingAndRemovingRemainingPedestrians();

    void testStartingNewNysse();
    void testRemovingNysse();
    void testNysseLeaving();
};



void testgamestatistics::testGamestatisticsCreationValues()
{
    Gamestatistics stats;
    QVERIFY(stats.returnRage() == 900);
    QVERIFY(stats.returnPoints() == 0);
}

void testgamestatistics::testChangePoints()
{
    Gamestatistics stats;
    stats.changePoints(100);
    QVERIFY(stats.returnPoints() == 100);
}

void testgamestatistics::testChangeRagePositiveOver900()
{
    Gamestatistics stats;
    QCOMPARE(stats.changeRage(900), int(160 - 900/6));
}

void testgamestatistics::testChangeRageNegative()
{
    Gamestatistics stats;
    QCOMPARE(stats.changeRage(-100), int(160 - 800/6));
}

void testgamestatistics::testChangeRagePositive()
{
    Gamestatistics stats;
    stats.changeRage(-300);
    QCOMPARE(stats.changeRage(100), int(160 - 700/6));
}

void testgamestatistics::testRageDecay()
{
    Gamestatistics stats;
    stats.rageDecay();
    stats.rageDecay();
    stats.rageDecay();
    stats.rageDecay();
    stats.rageDecay();
    QCOMPARE(stats.returnRage(), 895);
}

void testgamestatistics::testMorePassengers()
{
    Gamestatistics stats;
    stats.morePassengers(3);
    QCOMPARE(stats.returnPassengers(), 3);
}

void testgamestatistics::testPassengerDied()
{
    Gamestatistics stats;
    stats.morePassengers(5);
    stats.passengerDied(2);
    QCOMPARE(stats.returnPassengers(), 3);
}

void testgamestatistics::testResetingAndRemovingRemainingPedestrians()
{
    Gamestatistics stats;
    stats.resetRemainingPedestrians(10);
    QCOMPARE(stats.returnRemainingPedestrians(), 10);
    stats.removePedestrian();
    QCOMPARE(stats.returnRemainingPedestrians(), 9);
    stats.removePedestrian();
    stats.removePedestrian();
    stats.removePedestrian();
    QCOMPARE(stats.returnRemainingPedestrians(), 6);
}

void testgamestatistics::testStartingNewNysse()
{
    Gamestatistics stats;
    stats.newNysse();
    QCOMPARE(stats.returnTotalNysses(), 1);
    stats.newNysse();
    stats.newNysse();
    stats.newNysse();
    QCOMPARE(stats.returnTotalNysses(), 4);
}

void testgamestatistics::testRemovingNysse()
{
    Gamestatistics stats;
    stats.nysseRemoved();
    QCOMPARE(stats.returnRemovedNysses(), 1);
    stats.nysseRemoved();
    stats.nysseRemoved();
    stats.nysseRemoved();
    QCOMPARE(stats.returnRemovedNysses(), 4);
}

void testgamestatistics::testNysseLeaving()
{
    Gamestatistics stats;
    stats.nysseLeft();
    QCOMPARE(stats.returnLostNysses(), 1);
    stats.nysseLeft();
    stats.nysseLeft();
    stats.nysseLeft();
    QCOMPARE(stats.returnLostNysses(), 4);
}

QTEST_APPLESS_MAIN(testgamestatistics)

#include "tst_gamestatistics.moc"
