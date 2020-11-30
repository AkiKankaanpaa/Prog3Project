#include <QtTest>
#include "gamestatistics.h"

// add necessary includes here

class testgamestatistics : public QObject
{
    Q_OBJECT

private slots:
    void test_case1();
    void test_case2();
};


void testgamestatistics::test_case1()
{
    Gamestatistics stats(0);
    QVERIFY(stats.return_points() == 0);
}

void testgamestatistics::test_case2()
{
    Gamestatistics stats(0);
    stats.change_points(100);
    QVERIFY(stats.return_points() == 100);
}

QTEST_APPLESS_MAIN(testgamestatistics)

#include "tst_gamestatistics.moc"
