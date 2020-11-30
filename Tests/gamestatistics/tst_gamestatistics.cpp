#include <QtTest>
#include "gamestatistics.h"

// add necessary includes here

class testgamestatistics : public QObject
{
    Q_OBJECT

private slots:
    void test_gamestatistics_creation_values();

    void test_change_points();

    void test_change_rage_positive_over_900();
    void test_change_rage_negative();
    void test_change_rage_positive();

    void test_rage_decay();

    void test_morePassengers();
    void test_passengerDied();

    void test_reseting_and_removing_remaining_pedestrians();

    void test_starting_new_nysse();
    void test_removing_nysse();
    void test_nysse_leaving();
};



void testgamestatistics::test_gamestatistics_creation_values()
{
    Gamestatistics stats(0, EASY);
    QVERIFY(stats.return_rage() == 900);
    QVERIFY(stats.return_points() == 0);
}

void testgamestatistics::test_change_points()
{
    Gamestatistics stats(0, EASY);
    stats.change_points(100);
    QVERIFY(stats.return_points() == 100);
}

void testgamestatistics::test_change_rage_positive_over_900()
{
    Gamestatistics stats(0, EASY);
    QCOMPARE(stats.change_rage(900), int(160 - 900/6));
}

void testgamestatistics::test_change_rage_negative()
{
    Gamestatistics stats(0, EASY);
    QCOMPARE(stats.change_rage(-100), int(160 - 800/6));
}

void testgamestatistics::test_change_rage_positive()
{
    Gamestatistics stats(0, EASY);
    stats.change_rage(-300);
    QCOMPARE(stats.change_rage(100), int(160 - 700/6));
}

void testgamestatistics::test_rage_decay()
{
    Gamestatistics stats(0, EASY);
    stats.rage_decay();
    stats.rage_decay();
    stats.rage_decay();
    stats.rage_decay();
    stats.rage_decay();
    QCOMPARE(stats.return_rage(), 895);
}

void testgamestatistics::test_morePassengers()
{
    Gamestatistics stats(0, EASY);
    stats.morePassengers(3);
    QCOMPARE(stats.returnPassengers(), 3);
}

void testgamestatistics::test_passengerDied()
{
    Gamestatistics stats(0, EASY);
    stats.morePassengers(5);
    stats.passengerDied(2);
    QCOMPARE(stats.returnPassengers(), 3);
}

void testgamestatistics::test_reseting_and_removing_remaining_pedestrians()
{
    Gamestatistics stats(0, EASY);
    stats.reset_remaining_pedestrians(10);
    QCOMPARE(stats.return_pedestrians(), 10);
    stats.pedestrian_removed();
    QCOMPARE(stats.return_pedestrians(), 9);
    stats.pedestrian_removed();
    stats.pedestrian_removed();
    stats.pedestrian_removed();
    QCOMPARE(stats.return_pedestrians(), 6);
}

void testgamestatistics::test_starting_new_nysse()
{
    Gamestatistics stats(0, EASY);
    stats.newNysse();
    QCOMPARE(stats.returnTotalNysses(), 1);
    stats.newNysse();
    stats.newNysse();
    stats.newNysse();
    QCOMPARE(stats.returnTotalNysses(), 4);
}

void testgamestatistics::test_removing_nysse()
{
    Gamestatistics stats(0, EASY);
    stats.nysseRemoved();
    QCOMPARE(stats.returnRemovedNysses(), 1);
    stats.nysseRemoved();
    stats.nysseRemoved();
    stats.nysseRemoved();
    QCOMPARE(stats.returnRemovedNysses(), 4);
}

void testgamestatistics::test_nysse_leaving()
{
    Gamestatistics stats(0, EASY);
    stats.nysseLeft();
    QCOMPARE(stats.returnLostNysses(), 1);
    stats.nysseLeft();
    stats.nysseLeft();
    stats.nysseLeft();
    QCOMPARE(stats.returnLostNysses(), 4);
}

QTEST_APPLESS_MAIN(testgamestatistics)

#include "tst_gamestatistics.moc"
