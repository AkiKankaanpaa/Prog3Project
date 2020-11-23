#include "playerbus.h"

PlayerBus::PlayerBus(QGraphicsRectItem* bus)
{
    player_ = bus;
}

bool PlayerBus::currently_on(QPointF point)
{
    if (player_->contains(point)) {
        return true;
    } else {
        return false;
    }
}

void PlayerBus::move(direction dir)
{
    if(dir == RIGHT){
        player_->setPos(player_->x() + 10, player_->y());
    } else if(dir == LEFT) {
        player_->setPos(player_->x() - 10, player_->y());
    } else if(dir == UP){
        player_->setPos(player_->x(), player_->y() - 10);
    } else {
        player_->setPos(player_->x(), player_->y() + 10);
    }
}
