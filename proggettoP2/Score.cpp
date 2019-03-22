#include "Score.h"


Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;
    multiplier=1;

    // draw the text
    UpdateText();
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

//aumento del punteggio di ammount e il relativo aumento graffico
void Score::increase(unsigned int ammount){
    score+=(ammount*multiplier);
    UpdateText();
}
void Score::increaseMultiplier(double ammount){
    multiplier+=ammount;
    UpdateText();
}


//reset dovuto alla colisione con una bomb e il relativo update graffico
void Score::resetMultiplier()
{
    if(multiplier>1)
    {
    multiplier=1;
    UpdateText();
    }
}


//getter
unsigned int Score::GetScore() const{
    return score;
}

double Score::getMultiplier() const{
    return multiplier;
}

//update graffico dello score
void Score:: UpdateText(){
    setPlainText(QString( "Score: ")+QString::number(score)+QString( "\n")+QString::number(multiplier)+QString( "x")); // Score: 1
}


