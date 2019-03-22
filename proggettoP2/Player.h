#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

class Player:public QObject, public QGraphicsPixmapItem{
   Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
public slots:
    void checkCollisions();
    void movePlayer();
private:
    bool moveLeft, moveRight;

};

#endif // PLAYER_H

