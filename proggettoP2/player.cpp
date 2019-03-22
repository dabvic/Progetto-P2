#include "Player.h"


#include <Game.h>

#include <Drops.h>

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
   moveLeft=false;
   moveRight=false;

    // set graphic
   setPixmap(QPixmap(":/images/player.png").scaled(QSize(200, 200), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    connect(Game::timerGeneral ,SIGNAL(timeout()),this,SLOT(checkCollisions()));
    connect(Game::timerGeneral ,SIGNAL(timeout()),this,SLOT(movePlayer()));
}
/*
// movimento giocatore con i tasti versione semplice ma delay, da rivedere!
void Player::keyPressEvent(QKeyEvent *event){
    if(Game::timerGeneral->isActive()==false)// impedisci movimenti se il timer e' fermo(pausa, end game ecc)
        return;
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        setPos(x()-20,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
        setPos(x()+20,y());
    }
}
*/


// movimento giocatore con i tasti

void Player::keyReleaseEvent(QKeyEvent *event){
    if(Game::timerGeneral->isActive()==false)// impedisci movimenti se il timer e' fermo(pausa, end game ecc)
        return;
    if (event->key() == Qt::Key_Left){
        moveLeft=false;
    }
    else if (event->key() == Qt::Key_Right){
       moveRight=false;
    }
}

void Player::keyPressEvent(QKeyEvent *event){
    if(Game::timerGeneral->isActive()==false)// impedisci movimenti se il timer e' fermo(pausa, end game ecc)
        return;
    if (event->key() == Qt::Key_Left){
        moveLeft=true;
        moveRight=false;
    }
    else if (event->key() == Qt::Key_Right){
       moveRight=true;
       moveLeft=false;
    }
}

void Player:: movePlayer(){
    if(moveLeft)
    {
        if (pos().x() > 0)
        setPos(x()-20,y());
    }
    else if(moveRight){
        if (pos().x() + 200 < 800)
        setPos(x()+20,y());
    }
}

void Player:: checkCollisions(){

    // lista di tutti gli oggetti che collidono con il giocatore
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){

            Drop* dp = dynamic_cast<Drop*>((colliding_items[i]));//scarto se non drop
            if(dp)
            {
                //invoco collision relativo al oggetto (polimorfismo)
                dp->Collision();

                //elimino l'oggetto
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];// non piu' necessario quindi elimino subito

            }
        }


}
