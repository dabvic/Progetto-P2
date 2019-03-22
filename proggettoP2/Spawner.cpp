#include <Spawner.h>




Spawner:: Spawner(QGraphicsScene* sc): scene(sc){
    items=new Container();
    //items->Create();
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()), this,SLOT(spawn()));//collego lo slot al timer
    timer->start(1000);

}

//slot collegato al timer di questo oggetto, spawna nuovi Drop
void Spawner:: spawn(){

     scene->addItem(items->Instantiate());
}
