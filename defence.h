#ifndef DEFENCE_H
#define DEFENCE_H
#include "building.h"
#include <vector>
#include <cstring>
#include <stdio.h>
using namespace std;

class Defence :public Building {

private:
    vector<class Unit*> units;
    int units_count;

public:
    int getCapacity();
	bool upgrade();
    Defence(class Map*,class Player*);
    vector<class Unit*> getUnits();
    bool addUnit(class Unit*);
    void unload();
    string getStatus();
    ~Defence();
};

#endif // DEFENCE_H
