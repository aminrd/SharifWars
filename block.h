#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include "gameobject.h"
using namespace std;

class Block{

private:
    int row;
    int col;
    vector <GameObject*> objects;

public:
    Block();
    vector <GameObject*> getObjects();
    void addObject(GameObject*);
    void removeObject(GameObject*);
    int getRow();
    int getCol();
    bool getEmpty()const;
    bool Empty_Of_Building();
    void setEmpty();
    void setPlace(int,int);

};

#endif // BLOCK_H
