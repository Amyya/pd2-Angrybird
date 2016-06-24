#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)  //x, y in BOX2D, radius:radius of bird
{
    setcolor(0);
    // Set pixmap of red bird
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);  //transform origin point from upper left to midpoint
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;   //moveable item <->static
    bodydef.bullet = true;   //present it's high speed and not to run through
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;   //circle
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;   //characteristic of physic
    fixturedef.shape = &bodyshape;   //#17
    fixturedef.density = BIRD_DENSITY;  //use to calculate weight
    fixturedef.friction = BIRD_FRICTION;   //摩擦力
    fixturedef.restitution = BIRD_RESTITUTION;  //彈力
    g_body->SetAngularDamping(3);  //減速讓他不要轉太快
    g_body->CreateFixture(&fixturedef);
    g_body->SetGravityScale(0); //物體受到重力的程度,1就是現在重力場


    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));   //renew picture position

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)   //速度
{
    g_body->SetLinearVelocity(velocity);
}

int Bird::getcolor() const   //判斷是不是紅鳥
{
    return bird_color;
}

int Bird::setcolor(int i)   //0則為紅鳥
{
    bird_color = i ;
}

void Bird::skill(){

}

