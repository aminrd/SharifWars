#include "normalunit.h"
#include "player.h"
#include "iostream"

using namespace std;

NormalUnit::NormalUnit(Map* _map, Player* player) :Unit(_map){
    gameObjectType=4;

    this->name=player->information.normal_name;
    this->cost=player->information.normal_cost;
    this->training_time=player->information.normal_time_constructoin;
    this->max_health=player->information.normal_max_health;
    this->attack_damage=player->information.normal_attack_damage;
    this->attack_range=player->information.normal_attack_range;
    this->attack_delay=player->information.normal_attack_delay;
    this->speed=player->information.normal_speed;

    health=max_health;
}

bool NormalUnit::upgrade(){

    level++;
    max_health+= max_health /4;
    health+= health/4;
    attack_damage+= attack_damage/4;
    return true;

}

string NormalUnit::getStatus(){

    char status[100];
    if(myRoad.size()==0)
        sprintf(status,"this unit don't go any where");
    else
        sprintf(status,"this unit go to block (%d,%d)",myRoad[0].y,myRoad[0].x);

    return status;
}

