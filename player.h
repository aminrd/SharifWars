#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <Qcolor>
#include <vector>
#include "GameObject.h"
#include <QString>
#include <cstring>
using namespace std;


struct Information{

    //----------------------------------------team name
    QString team_name;

    //----------------------------------------base building
    QString base_name;
    int base_cost;
    int base_upgrade_cost;
    int base_time_constructoin;
    int base_max_health;
    int base_attack_damage;
    int base_attack_range;
    int base_attack_delay;

    //----------------------------------------defence building
    QString defence_name;
    int defence_cost;
    int defence_upgrade_cost;
    int defence_time_constructoin;
    int defence_max_health;
    int defence_attack_damage;
    int defence_attack_range;
    int defence_attack_delay;

    //----------------------------------------money maker building
    QString moneyMaker_name;
    int moneyMaker_cost;
    int moneyMaker_upgrade_cost;
    int moneyMaker_time_constructoin;
    int moneyMaker_max_health;
    int moneyMaker_attack_damage;
    int moneyMaker_attack_range;
    int moneyMaker_attack_delay;
    int moneyMaker_income;

    //----------------------------------------unit maker building
    QString unitMaker_name;
    int unitMaker_cost;
    int unitMaker_upgrade_cost;
    int unitMaker_time_constructoin;
    int unitMaker_max_health;
    int unitMaker_attack_damage;
    int unitMaker_attack_range;
    int unitMaker_attack_delay;
    int unitMaker_type;

    //----------------------------------------super unit maker
    QString super_unitMaker_name;
    int super_unitMaker_cost;
    int super_unitMaker_upgrade_cost;
    int super_unitMaker_time_constructoin;
    int super_unitMaker_max_health;
    int super_unitMaker_attack_damage;
    int super_unitMaker_attack_range;
    int super_unitMaker_attack_delay;
    int super_unitMaker_type;

    //----------------------------------------vehicle unit maker builing
    QString vehicle_unitMaker_name;
    int vehicle_unitMaker_cost;
    int vehicle_unitMaker_upgrade_cost;
    int vehicle_unitMaker_time_constructoin;
    int vehicle_unitMaker_max_health;
    int vehicle_unitMaker_attack_damage;
    int vehicle_unitMaker_attack_range;
    int vehicle_unitMaker_attack_delay;
    int vehicle_unitMaker_type;

    //----------------------------------------normal unit
    QString normal_name;
    int normal_cost;
    int normal_time_constructoin;
    int normal_max_health;
    int normal_attack_damage;
    int normal_attack_range;
    int normal_attack_delay;
    int normal_speed;

    //----------------------------------------super unit
    QString super_name;
    int super_cost;
    int super_time_constructoin;
    int super_max_health;
    int super_attack_damage;
    int super_attack_special_damage;
    int super_attack_range;
    int super_attack_delay;
    int super_speed;
    int super_max_mana;
    int super_regenition;

    //----------------------------------------vehicle unit
    QString vehicle_name;
    int vehicle_cost;
    int vehicle_time_constructoin;
    int vehicle_max_health;
    int vehicle_attack_damage;
    int vehicle_attack_range;
    int vehicle_attack_delay;
    int vehicle_speed;
    int vehicle_capacity;

};


class Player{

private:
    QString name;
    QColor color;
    vector <class GameObject*> player_object;
    vector <class Building*> player_building;
    vector <class Unit*> player_unit;
    vector <class Block*> area;
    vector <class UnitMaker*> player_unitMaker;
    class Map* map;
    int money;
    int my_height;
    int my_width;
    int my_x;
    int my_y;
    int team_ID;
    int Player_ID;

public:
    Information information;
    Player();
    Player(QString name, int team, int startingMoney, int _Player_ID, vector<class Block*>);
    int getPlayerID();
    QString getName();
    int getTeam() const;
    int getMoney();
    void setMoney(int);
    void setMap(class Map*);
    vector <class UnitMaker*> getUnitMaker();
    vector <class Building*> getPlayerBuilding();
    vector <class Unit*> getPlayerUnit();
    vector<class Block*> getPlayerArea();
    vector<class GameObject*> getPlayerObject();
    void addUnit(class Unit*);
    void addBuilding(class Building*);
    void setArea(int _x,int _y, int _width, int _height);
    void dead_Object(class GameObject*);


};

#endif // PLAYER_H
