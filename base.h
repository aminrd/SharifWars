#ifndef BASE_H
#define BASE_H
#include "building.h"
#include <QString>
#include <cstring>

class Base :public Building{

private:


public:
    Base(class Map*,class Player*);
    bool upgrade();
    string getStatus();


};

#endif // BASE_H

