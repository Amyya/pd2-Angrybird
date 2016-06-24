#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

#include <QSize>
#include <QPushButton>
#include <QBrush>
#include <QImage>
#include <math.h>
#include <QGraphicsPixmapItem>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <pig.h>
#include <obstacle.h>
#include <button.h>
#include <yellow_bird.h>
#include <black_bird.h>
#include <blue_bird.h>
#include <slingshot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* event);

    void restart();
    void initial();
    void deletepig();

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void move();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QTimer timerpig;
    QList<Bird *> birdList;
    QTimer *movetimer;
    QGraphicsPixmapItem * slingslot;
    pig *pig_one;
    pig *pig_two;

    int click, birdsitua, birdskill, color, nobird;   //birdsitua 0:initial 1:click 2:pulling 3:flying
    float mousepress_x, mousepress_y, mouserelease_x, mouserelease_y, inisite_x, inisite_y;
    QMouseEvent * mouseEvent;
    int pigonelife = 1;
    int pigtwolife = 1;
    double sitep1, sitep2;
};

#endif // MAINWINDOW_H
