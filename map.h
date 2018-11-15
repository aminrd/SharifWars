#ifndef MAP_H
#define MAP_H
#include "block.h"
#include <vector>
using namespace std;

class Map{

private:
    int rowcount;
    int colcount;
    Block** map;

public:
    Map(int , int);
    void Eqaul(Map*);
    Block* getBlock(int row, int col);
    int GetRowcount();
    int GetColcount();
    ~Map();
};

#endif // MAP_H
