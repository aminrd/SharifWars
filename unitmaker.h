#ifndef UNITMAKER_H
#define UNITMAKER_H
#include "building.h"
#include "QLabel"
#include <cstring>
#include <cstdio>

class UnitMaker :public Building {

private:
    int training_time;
    double training_progress;
    int queuecount;
    int unitType;

public:
    UnitMaker(class Map*,class Player*, int);
    int getTrainingTime();
    bool trainUnit(QLabel*);
    double getTrainingProgress();
    int queueCount();
    void setTrainingTime(int);
    void setTrainingProgress(double);
    virtual int getUnitType();
    bool upgrade();
    void setQueueCount(int);
    string getStatus();
};

#endif // UNITMAKER_H
