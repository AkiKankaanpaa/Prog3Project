#ifndef PLAYERBUS_H
#define PLAYERBUS_H
#include <QGraphicsRectItem>

enum direction {RIGHT, LEFT, UP, DOWN};

class PlayerBus
{
public:
    PlayerBus(QGraphicsRectItem* bus);
    bool currently_on(QPointF point);

public slots:
    void move(direction dir);

private:
    QGraphicsRectItem* player_;
};

#endif // PLAYERBUS_H
