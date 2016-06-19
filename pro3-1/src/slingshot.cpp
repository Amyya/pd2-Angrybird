#include "slingshot.h"

slingshot::slingshot(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_size = QSize(w,h);

    b2BodyDef bodydef;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    paint();
}
