#include "moneymaker.h"
#include "player.h"
#include "iostream"
#include "map.h"

using namespace std;

MoneyMaker::MoneyMaker(Map* _map,Player * player) :Building(_map){
    gameObjectType=2;
    height=3;
    width=4;

    this->name=player->information.moneyMaker_name;
    this->cost=player->information.moneyMaker_cost;
    this->upgrade_cost=player->information.moneyMaker_upgrade_cost;
    this->construction_time=player->information.moneyMaker_time_constructoin;
    this->max_health=player->information.moneyMaker_max_health;
    this->attack_damage=player->information.moneyMaker_attack_damage;
    this->attack_range=player->information.moneyMaker_attack_range;
    this->attack_delay=player->information.moneyMaker_attack_delay;
    this->income=player->information.moneyMaker_income;

    health=max_health;
}

int MoneyMaker::getIncome(){
    return income;
}

bool MoneyMaker::upgrade(){


	if(level>=3)
		return false;

	if(player->getMoney() < player->information.moneyMaker_upgrade_cost)
		return false;

	level++;
	player->setMoney( - player->information.moneyMaker_upgrade_cost);
	income+= income /4;
	return true;

}

string MoneyMaker::getStatus(){
    char status[100];
    sprintf(status,"this is money maker build with %d income",income);
    return status;
}


