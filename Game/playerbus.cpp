#include "playerbus.h"

PlayerBus::PlayerBus(QGraphicsRectItem* bus)
{
    player_ = bus;
}

void PlayerBus::move(int dir)
{
    if(dir == RIGHT){
        player_->setPos(player_->x() + 10, player_->y());
    } else if(dir == LEFT) {
        player_->setPos(player_->x() - 10, player_->y());
    } else if(dir == UP){
        player_->setPos(player_->x(), player_->y() - 10);
    } else if(dir == DOWN){
        player_->setPos(player_->x(), player_->y() + 10);
    }
}
