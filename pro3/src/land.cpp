#include "land.h"

Land::Land(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_size = QSize(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;   //多邊形
    bodyBox.SetAsBox(w,h);   //四邊形
    g_body->CreateFixture(&bodyBox,9.0f);  //9.0f is density

    scene->addItem(&g_pixmap);
    paint();
}
