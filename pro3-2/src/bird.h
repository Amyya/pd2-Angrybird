#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f   //摩擦
#define BIRD_RESTITUTION 0.5f   //彈力

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);   //加速度
    virtual void skill();
    int getcolor() const;
    int setcolor(int i);
private:
    int bird_color;
};

#endif // BIRD_H
