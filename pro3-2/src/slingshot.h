#ifndef SLINGSHOT_H
#define SLINGSHOT_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define PIG_DENSITY 15.0f
#define PIG_FRICTION 0.2f
#define PIG_RESTITUTION 0.5f

class slingshot: public GameItem
{
public:
    slingshot(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // SLINGSHOT_H
