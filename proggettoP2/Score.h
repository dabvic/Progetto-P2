
#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QFont>
#include <qdebug.h>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
     void increase(unsigned int);
     void increaseMultiplier(double);
     void resetMultiplier();
     unsigned int GetScore() const;
     double getMultiplier() const;
     void UpdateText();
private:
    unsigned int score;
    double multiplier;
};

#endif // SCORE_H

