#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button.h"
#include <QMouseEvent>
#include <QEvent>
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);

    inisite_x = 8.0f;
    inisite_y = 8.0f;

    click = 0;
    birdsitua = 0;
    color = 0;
    nobird = 0;

    movetimer = new QTimer();
    connect(movetimer,SIGNAL(timeout()), this, SLOT(move()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/image/background.png")));
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));  //橫跟直的重力
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());   //size of BOX2D windowsize
    QSound *music =new QSound("angrybird.wav");
    music->play();

    initial();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);

    //create the restart button
    /*QPushButton *restartButton = new QPushButton;
    restartButton->setGeometry(QRect(QPoint(100,50),QSize(100, 100)));
    QPixmap pixmap(":/image/restart.jpg");
    QIcon ButtonIcon(pixmap);
    restartButton->setIcon(ButtonIcon);
    restartButton->setIconSize(pixmap.rect().size());
    scene->addWidget(restartButton);
    connect(restartButton,SIGNAL(clicked(bool)),this,SLOT(restart()));*/

}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!(*5)

    mouseEvent = (QMouseEvent *) event ;

    if(event->type() == QEvent::MouseButtonPress && nobird == 0)
       {
           if(birdsitua == 0){
               click = 1;
               mousepress_x = (mouseEvent->pos().x() - 23) / 800.0 * 32.0;
               mousepress_y = 18.0-((mouseEvent->pos().y() - 46) * 18 / 600.0);
               birdsitua = 1;   //點
               std::cout << birdsitua <<std::endl;
           }
           std::cout << "Press !" << std::endl ;
       }
       if(event->type()==QEvent::MouseMove && click>=1 && nobird == 0)
       {
           if(birdsitua==1 || birdsitua==2){   //點或拉
               float coor_x = (mouseEvent->pos().x() - 23) / 800.0 * 32.0;
               float coor_y = 18.0-( (mouseEvent->pos().y()-46) * 18 / 600.0);

               if( (coor_x - inisite_x)*(coor_x - inisite_x) + (coor_y - inisite_y)*(coor_y - inisite_y) <= 4){
                   birdList[color]->getBody().SetTransform( b2Vec2(coor_x, coor_y), 0);   //(site, angle)
               }
               birdsitua = 2;   //拉
           }
        std::cout << "Move !" << std::endl ;
       }
       if(event->type() == QEvent::MouseButtonRelease && nobird == 0)
       {
         if(birdsitua == 2){    //拉
             click = 0;
             mouserelease_x = ( mouseEvent->pos().x() - 23) / 800.0 * 32.0;
             mouserelease_y = 18.0 -( (mouseEvent->pos().y() - 46) * 18 / 600.0);
             float bird_x = birdList[color]->getBody().GetPosition().x;
             float bird_y = birdList[color]->getBody().GetPosition().y;

             birdList[color]->getBody().SetLinearVelocity(b2Vec2( (bird_x - inisite_x)*(-7), (bird_y - inisite_y)*(-7) ) );
             birdList[color]->getBody().SetGravityScale(1);

             if(birdList[color]->getcolor() == 0){
                movetimer->start(1000);
                birdsitua = 0 ;   //換
                std::cout << birdsitua <<std::endl;
             }
             else{
                 birdskill = 1;
                 birdsitua = 3;   //飛行中
                 std::cout << birdsitua <<std::endl;
             }
         }
         else if(birdsitua == 4){   //放技能
             movetimer->start(50);
             birdsitua = 0;
             std::cout << birdsitua <<std::endl;
         }
        std::cout << "Release !" << std::endl ;
        std::cout << color << std::endl ;
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if(event->key()==Qt::Key_Z && birdsitua==3 && birdskill==1){    //放開後飛行中還沒用技能
        std::cout << "skill" << std::endl ;
        birdList[color]->skill();
        std::cout << "skill2" << std::endl ;
        movetimer->start(1000);
        birdsitua = 0;   //放完技能
     }
    if(event->key()==Qt::Key_R){
        restart();
    }
    if(event->key()==Qt::Key_Q){
        quitGame();
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::move(){
     color += 1;
     if(color <= 3){
         birdList[color]->getBody().SetTransform(b2Vec2(8.0,7.0),0);
     }
     else{
         color = 0;
         nobird = 1;
     }
     movetimer->stop();
}

void MainWindow::initial(){
    // Create ground
    itemList.push_back(new Land(16,1.5,32,1.0,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));   //pop_back拉出來 x, y, width, height
    // Create bird (You can edit here)
    Bird *birdie = new Bird(8.0f,8.0f,0.70f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);   //position in BOX2D x, y, radius
    // Setting the Velocity
    itemList.push_back(birdie);
    birdList.push_back(birdie);

    yellow_bird *birdie_yellow = new yellow_bird(6.0f,2.50f,0.70f,&timer,QPixmap(":/image/1321329378-3367254444.png").scaled(height()/9.0,height()/9.0),world,scene);
    itemList.push_back(birdie_yellow);
    birdList.push_back(birdie_yellow);

    Black_bird *birdie_black = new Black_bird(4.0f,2.50f,0.85f,&timer,QPixmap(":/image/pajarito5.png").scaled(height()/9.0,height()/9.0),world,scene);
    itemList.push_back(birdie_black);
    birdList.push_back(birdie_black);

    Blue_bird *birdie_blue = new Blue_bird(2.0f,2.50f,0.90f,&timer,QPixmap(":/image/pajarito2.png").scaled(height()/9.0,height()/9.0),world,scene);
    itemList.push_back(birdie_blue);
    birdList.push_back(birdie_blue);

    //create pig
    pig *pig_one = new pig(18.0f,6.0f,0.87f,&timer,QPixmap(":/image/20150810032747230.png").scaled(height()/9.0,height()/9.0),world,scene);
    itemList.push_back(pig_one);
    pig *pig_two = new pig(24.0f,8.0f,0.90f,&timer,QPixmap(":/image/Pig_sneeze_copy.png").scaled(height()/9.0,height()/9.0),world,scene);
    itemList.push_back(pig_two);

    //create obstacle
    Obstacle *wood_one = new Obstacle(18.0f,2.5f,0.9999999f,&timer,QPixmap(":/image/AB Wood Board.png").scaled(height()/9.0,height()/9.0),world,scene);    //how to changethe usage of the circle into the square???
    itemList.push_back(wood_one);
    Obstacle *wood_two = new Obstacle(24.0f,2.5f,0.97f,&timer,QPixmap(":/image/INGAME_BLOCKS_WOOD_1square.png").scaled(height()/9.0,height()/9.0),world,scene);    //how to changethe usage of the circle into the square???
    itemList.push_back(wood_two);
    Obstacle *wood_three = new Obstacle(24.0f,5.5f,0.97f,&timer,QPixmap(":/image/INGAME_BLOCKS_WOOD_1square.png").scaled(height()/9.0,height()/9.0),world,scene);    //how to changethe usage of the circle into the square???
    itemList.push_back(wood_three);

    //create slingshot
    itemList.push_back(new slingshot(8,6,0.1,0.1,QPixmap(":/image/sling_shot_vector_by_birdalliance-d84p8sd.png").scaled(width()/17,height()/4.0),world,scene));
    scene->update();
}

void MainWindow::restart(){
    movetimer -> stop();
    timer.stop();

    click = 0;
    birdsitua = 0;
    birdskill = 0;
    color = 0;
    nobird = 0;

    foreach(Bird *birdie ,birdList){
        birdList.removeOne(birdie);
    }
    foreach(GameItem *item ,itemList){
        itemList.removeOne(item);
        delete item;
    }

    initial();

    scene->update();
    timer.start();
}
