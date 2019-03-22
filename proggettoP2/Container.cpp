#include <Container.h>


Container::Container():current(0), first(0), spawnSpeed(0){}


Container::nodo* Container:: Create(nodo* n, int size){

if(size==0)
    return 0;

//creazione del Drop* con un tipo dinamico pseudorandomico
    Drop* drop;
    n=new nodo();
    int number = rand() %3;
    switch (number)
    {
       case(0):
        drop = new Apple();
            break;

       case(1):
        drop = new Bomb();
        break;

       case(2):
        drop = new Multiplier();
            break;

       default:
        drop = new Apple();
    }

     n->obj=drop;
     n->next= Create(n->next, size-1);
     first=n;
     return n;

}

Drop* Container::Instantiate()
{
    if(!current)
    {
        current=new nodo();
        current=Create(current, 10);
        spawnSpeed++;
    }
    nodo*c=current;
    c->obj->SetGraphics();
    c->obj->SetSpeed();
    c->obj->IncreaseSpeed(spawnSpeed);

    current=c->next;

    return c->obj;

}



Container::nodo::~nodo()
{
    if(next)
        delete next;
}
