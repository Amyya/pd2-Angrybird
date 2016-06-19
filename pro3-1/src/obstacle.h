#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define OBSTACLE_DENSITY 5.0f
#define OBSTACLE_FRICTION 0.2f
#define OBSTACLE_RESTITUTION 0.5f

class Obstacle: public GameItem
{
public:
    Obstacle(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // OBSTACLE_H
