#include "yellow_bird.h"

yellow_bird::yellow_bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, radius, timer, pixmap, world, scene)
{
    setcolor(1);
}

void yellow_bird::skill(){
    this->getBody().SetLinearVelocity(b2Vec2(this->getBody().GetLinearVelocity().x * 3, this->getBody().GetLinearVelocity().y * 3));
}
