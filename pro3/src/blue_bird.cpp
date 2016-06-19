#include "blue_bird.h"
#include "bird.h"

Blue_bird::Blue_bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, radius, timer, pixmap, world, scene)
{
    setcolor(1);
}

void Blue_bird::skill(){
   this->getBody().SetLinearVelocity(b2Vec2(0,-100));
}
