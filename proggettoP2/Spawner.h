#ifndef SPAWNER_H
#define SPAWNER_H

#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <Container.h>

class Container;

class Spawner: public QObject{
 Q_OBJECT
private:
     QTimer * timer;
     QGraphicsScene* scene;
     Container* items;


public slots:
    void spawn();

public:
    Spawner(QGraphicsScene*);
};

#endif // SPAWNER_H
