#ifndef NORMALUNIT_H
#define NORMALUNIT_H
#include "unit.h"
#include <stdio.h>
#include <cstring>


class NormalUnit :public Unit{

friend class Game;

private:
    int training_time;
    bool upgrade();

public:
    NormalUnit(class Map*,class Player*);
    string getStatus();

};

#endif // NORMALUNIT_H
