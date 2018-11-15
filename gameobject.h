#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <iostream>
#include <cstring>
#include <QString>
#include "place.h"
using namespace std;

class GameObject{

protected:
    int health;
    int max_health;
    int attack_damage;
    int attack_range;
    int attack_delay;
    int stoping_of_attack;
    int place_x;
    int place_y;
    int player_id;
    int cost;
    int level;
    int gameObjectType;
    class Map* map;
    class Player* player;
    GameObject* target_object;
    QString name;
    bool inVehicle;

public:
    GameObject(class Map*,int _place_x=0,int _place_y=0);
    class Block* getBlock();
    class Player* getPlayer();
    QString getName();
    int getMaxHealth();
    int getHealth();
    int getAttackDamage();
    int getAttackRange();
    int getAttackDelay();
    int getStopingAttack();
    int getCost();
    int getType();
    vector<class Block*> getBlocksInRange();
    int getLevel();
    virtual int getUnitType(){return 0;}
    virtual void moveToBlock(int, int){    }
    void setTargetObject(GameObject* object);
    GameObject* getTargetObject();
    virtual void stop();
    virtual string getStatus(){return "salam";}
    void setStopingAttack();
    virtual void setstopingSpecialAttack(){ }
    void setHealth(int);
    void setLevel(int);
    void setPlace(int,int);
    void SetPlayer(class Player*);
    bool ObjectIsRange(GameObject* object);
    virtual bool Attack(GameObject*);
    bool AttackPossible();
    void Damage(int);
    virtual void sell(){ }
    void Kill();
    void In_Vehicle(){ inVehicle=true;}
    void Out_Vehicle(){ inVehicle=false;}
    virtual vector <place> GetRoad(){vector <place> temp;return temp;  }
    virtual int getSpeed(){return 3;}
    virtual void unload(){ }
    virtual bool addUnit(class Unit*){return false;}
    virtual bool upgrade(){ return false;}
    virtual int getCapacity(){return 0;}
    void Move_Nearest_Block();
    ~GameObject();

};

#endif // GAMEOBJECT_H
