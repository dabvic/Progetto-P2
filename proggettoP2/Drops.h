#ifndef DROPS_H
#define DROPS_H

#include <QTimer>
//#include <QGraphicsPixmapItem>
#include <QObject>
//#include <QGraphicsItem>
#include <Game.h>
#include <Score.h>
#include <Drops.h>

class Drop: public QObject, public QGraphicsPixmapItem{
     Q_OBJECT
    public:
     unsigned int speed;
     Drop();
     virtual void Collision()=0;
     virtual void SetGraphics()=0;
     void SetSpeed();
     void IncreaseSpeed( unsigned int);
     virtual void removeFromScene();
    private:
     virtual void SetTimer();

     virtual void SetPosition();
public slots:
     void Update();
};

class Bomb: public Drop{
    public:
     virtual void Collision();
     virtual void SetGraphics();
};

class Apple: public Drop{
    public:
    unsigned int points;
    Apple();
    virtual void Collision();

    virtual void SetGraphics();
    void AddPoints();
};

class Multiplier: public Apple{
    public:
    double mult;
    virtual void Collision();
    virtual void SetGraphics();

    Multiplier();
    void Multiply();
};

#endif // DROPS_
