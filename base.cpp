#include "base.h"
#include "map.h"
#include "building.h"
#include "player.h"
#include "iostream"
#include <cstdio>
#include <cstdlib>
using namespace std;

Base::Base(Map* _map , Player* player) : Building(_map){

    height=3;
    width=4;
    gameObjectType=0;

    //---------------------------------------------------------------set information
    this->name=player->information.base_name;
    this->cost=player->information.base_cost;
    this->upgrade_cost=player->information.base_upgrade_cost;
    this->construction_time=player->information.base_time_constructoin;
    this->max_health=player->information.base_max_health;
    this->attack_damage=player->information.base_attack_damage;
    this->attack_range=player->information.base_attack_range;
    this->attack_delay=player->information.base_attack_delay;

    health=max_health;
}

bool Base::upgrade(){

	if(level>=3)
		return false;

	if(player->getMoney() < player->information.base_upgrade_cost)
		return false;

	level++;
	player->setMoney(- player->information.base_upgrade_cost);
	max_health+= max_health /2;
	health += health/2;
	return true;

}

string Base::getStatus(){
    char status[100];
    sprintf(status,"this is Base building with %d health",health);
    return status;
}
