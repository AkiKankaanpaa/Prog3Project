#ifndef PLAYERBUS_H
#define PLAYERBUS_H
#include <QGraphicsRectItem>


class PlayerBus
{
public:
    PlayerBus(QGraphicsRectItem* bus);
    enum direction {RIGHT, LEFT, UP, DOWN};
public slots:
    void move(int dir);

private:
    QGraphicsRectItem* player_;
};

#endif // PLAYERBUS_H
