#ifndef GAME_H
#define GAME_H
#include <vector>
#include "player.h"
#include "map.h"
#include <QLabel>
using namespace std;

class Game{

private:
    vector <Player*> players;
    vector <class GameObject*> game_objects;
    vector <class Building*> buildings;
    vector <class Unit*> units;
    Map *map;
    static Game* instance;
    bool Build_Unit(class Player* player, class Building* building);
    Game(){ }

public:
    static Game* getInstance();
    void SetGameObject();
    void newGame(vector <class Player*> ,class  Map*);
    vector<class Player*> getPlayers();
    vector<class GameObject*> getObjects();
    vector<class Building*> getBuildings();
    vector<class Unit*> getUnits();
    bool constructBuilding(class Player* player, int buildingType, int row,int col, QLabel*);
    bool constructZombie(class Player*);
    bool constructUnit(class Player*,class Building*, QLabel*);
    class Map* getMap();
    void advanceGame();
    ~Game();

};

#endif // GAME_H
