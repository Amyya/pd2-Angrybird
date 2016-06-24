#include "black_bird.h"

Black_bird::Black_bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, radius, timer, pixmap, world, scene)
{
    Radius = radius;  //半徑才傳的進skill
    setcolor(1);
}

void Black_bird::skill(){
    g_pixmap.setPixmap(QPixmap(":/image/pajarito5.png").scaled(250,250));
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(Radius*15,Radius*15);
    this->getBody().SetLinearVelocity(b2Vec2(this->getBody().GetLinearVelocity().x * 3, this->getBody().GetLinearVelocity().y * 3));
}
