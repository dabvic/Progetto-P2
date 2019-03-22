#include "Health.h"
Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){

    health = 3; // buon senso vuole uno static int
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}
// metodo che riduce la vita del giocatore di 1
int Health::decrease(){
        health--;
        setPlainText(QString("Health: ") + QString::number(health));
        return health;


}
int Health::getHealth(){
    return health;
}

void Health::gameOver()
{

}
