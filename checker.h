#ifndef CHECKER_H
#define CHECKER_H
#include <vector>
#include <iostream>

using namespace std;


class Checker{

public:
    Checker();
    void Print_map(class Map*);
    void Print_money(vector<class Player*>);

};

#endif // CHECKER_H
