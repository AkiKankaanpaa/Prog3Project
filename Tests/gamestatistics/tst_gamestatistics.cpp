#include <QtTest>
#include "gamestatistics.h"

// add necessary includes here

class gamestatistics : public QObject
{
    Q_OBJECT

public:
    gamestatistics();
    ~gamestatistics();

private slots:
    void test_case1();

};

gamestatistics::gamestatistics()
{

}

gamestatistics::~gamestatistics()
{

}

void gamestatistics::test_case1()
{

}

QTEST_APPLESS_MAIN(gamestatistics)

#include "tst_gamestatistics.moc"
