#ifndef BLACK_BIRD_H
#define BLACK_BIRD_H

#include "bird.h"

class Black_bird : public Bird
{
public:
    Black_bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void skill();
private:
    float Radius;
};

#endif // BLACK_BIRD_H
