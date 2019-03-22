#include <Drops.h>


extern Game* game;
Drop::Drop()
{
    //stato iniziale dell'oggetto
    //SetSpeed();
    SetTimer();
    SetPosition();
    speed=0;
}


void Drop:: SetSpeed(){
    //velocita' dell'oggetto pseudorandomica
    speed=(rand()% 8) +4;
}

void Drop::IncreaseSpeed(unsigned int ammount)
{
    //aumento della velocita' dell'oggetto
    speed+=ammount;
}

void Drop::removeFromScene()
{
    scene()->removeItem(this);
}

void Drop:: SetTimer(){
    //connetto il timer allo slot Update() che simula la fisica, ovviamente tale slot puo' essere utilizzato per implementare funzionalita' che si ripetono a ogni tick del tmer
    connect(Game::timerGeneral ,SIGNAL(timeout()),this,SLOT(Update()));
}

Apple::Apple(): points(10)
{
}

// ultimo attributo di setGraphics serve a evitare l'effetto mipmap di Unity
void Apple:: SetGraphics(){
    // setto la rappresentazione graffica dell'oggetto Apple
    setPixmap(QPixmap(":/images/apple.png").scaled(QSize(100, 100), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(50,50);
}



void Bomb:: SetGraphics(){
    // setto la rappresentazione graffica dell'oggetto Bomb
    setPixmap(QPixmap(":/images/bomb.png").scaled(QSize(100, 100), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(50,50);
}
void Multiplier:: SetGraphics(){
    // setto la rappresentazione graffica dell'oggetto Multiplier
    setPixmap(QPixmap(":/images/multiplier.png").scaled(QSize(100, 100), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(50,50);
}

void Drop:: SetPosition(){
    //posizione randomica sull'asse x dell'oggetto, asse y costante in alto
    int random_number = rand() % 700;
    setPos(random_number, 0);
}

void Drop:: Update(){
    // muovi drop verso il basso per simulare la gravita'
    setPos(x(),y()+speed);

    // distruggi per evitare che scenda all'infinito quando supera il margine inferiore della scena
    if (pos().y() > 600){
        scene()->removeItem(this);
        delete this;
    }
}

void Apple:: Collision(){
    //apple si limita ad aumentare il puntegio
    game->score->increase(points);
}


void Bomb:: Collision(){
    //Bomb, oltre a togliere una vita, azera il moltiplicatore del puneggio
    game->score->resetMultiplier();

    //controllo se ho finito le vite, se vero invco il gameOver di game
    if(game->health->decrease()<=0)
    {
        game->GameOver();
    }
}

void Multiplier:: Collision(){
    //comportamento base di Apple a cui aggiungo un incremento del moltiplicatore
    Apple::Collision();
    game->score->increaseMultiplier(mult);
}


Multiplier:: Multiplier(): mult(0.2)
{

}





