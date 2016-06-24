#ifndef BLUE_BIRD_H
#define BLUE_BIRD_H

#include "bird.h"

class Blue_bird : public Bird
{
public:
    Blue_bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void skill();
};

#endif // BLUE_BIRD_H
