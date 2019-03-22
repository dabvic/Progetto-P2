#ifndef CONTAINER_H
#define CONTAINER_H

#include <Drops.h>
class Drop;

class Container{
private:
    class nodo{
    public:
        ~nodo();
        nodo* next;
        Drop* obj;
    };

    nodo* current;
    nodo* first;

public:
  Container();
  Drop* Instantiate();
  nodo* Create(nodo*, int);
  unsigned int spawnSpeed;

};

#endif // CONTAINER_H
