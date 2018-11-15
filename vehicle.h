#ifndef VEHICLE_H
#define VEHICLE_H
#include "unit.h"
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

class Vehicle :public Unit{

friend class Game;

private:
    int capacity;
    vector<Unit*> units;
    int units_count;
    int training_time;
    bool upgrade();

public:
    Vehicle(class Map*,class Player*);
    int getCapacity();
    vector<Unit*> getUnits();
    void unload();
    bool addUnit(Unit*);
    string getStatus();
};

#endif // VEHICLE_H
