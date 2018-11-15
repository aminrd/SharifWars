#ifndef UNIT_H
#define UNIT_H
#include "gameobject.h"
#include "place.h"
#include <vector>



using namespace std;

class Unit : public GameObject {

protected:
    int speed;
    class Block* block;
    vector <int> road_x;
    vector <int> road_y;
    vector <place> myRoad;
    void BfsHelper(int &,int, int, int ,int ,int**,int ,int ,vector<struct Parent_road> &);

public:
    Unit(class Map*);
    int getSpeed();
    void moveToBlock(Block* block);
    void moveToBlock(int row, int col);
    virtual void stop();
    vector <place> GetRoad();

};

#endif // UNIT_H
