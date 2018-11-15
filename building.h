#ifndef BUILDING_H
#define BUILDING_H
#include "gameobject.h"

class Building :public GameObject{

protected:
    int width;
    int height;
    int construction_time;
    double construction_progress;
    int upgrade_cost;

public:
    Building(Map*);
    int getWidth();
    int getHeight();
    int getConstructionTime();
    int getCostUpgrde();
    double getConstructionProgress();
    void setConstructionProgress(double);
    void setCostUpgrade(int);
    void sell();
    ~Building();

};

#endif // BUILDING_H
