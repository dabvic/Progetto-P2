#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <qfont.h>

class Game;

class Health: public QGraphicsTextItem{
public:
    Health(QGraphicsItem * parent=0);
    int decrease();
    int getHealth();
    void gameOver();
private:
    int health;
};



#endif // HEALTH_H

