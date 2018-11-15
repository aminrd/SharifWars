#ifndef MONEYMAKER_H
#define MONEYMAKER_H
#include "building.h"
#include <stdio.h>
#include <cstring>

class MoneyMaker :public Building {

private:
    int income;

public:
    MoneyMaker(class Map*,class Player*);
    bool upgrade();
    int getIncome();
    string getStatus();

};

#endif // MONEYMAKER_H
