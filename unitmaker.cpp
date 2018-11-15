#include "unitmaker.h"
#include "player.h"
#include "iostream"
#include "map.h"

using namespace std;

UnitMaker::UnitMaker(Map* _map,Player* player, int Type) :Building(_map){
    gameObjectType=3;
    height=3;
    width=4;

    switch(Type){

    case 0:
        this->name=player->information.unitMaker_name;
        this->cost=player->information.unitMaker_cost;
        this->upgrade_cost=player->information.unitMaker_upgrade_cost;
        this->construction_time=player->information.unitMaker_time_constructoin;
        this->max_health=player->information.unitMaker_max_health;
        this->attack_damage=player->information.unitMaker_attack_damage;
        this->attack_range=player->information.unitMaker_attack_range;
        this->attack_delay=player->information.unitMaker_attack_delay;
        this->unitType=0;
        this->training_time=player->information.normal_time_constructoin;
        break;

    case 1:
        this->name=player->information.super_unitMaker_name;
        this->cost=player->information.super_unitMaker_cost;
        this->upgrade_cost=player->information.super_unitMaker_upgrade_cost;
        this->construction_time=player->information.super_unitMaker_time_constructoin;
        this->max_health=player->information.super_unitMaker_max_health;
        this->attack_damage=player->information.super_unitMaker_attack_damage;
        this->attack_range=player->information.super_unitMaker_attack_range;
        this->attack_delay=player->information.super_unitMaker_attack_delay;
        this->unitType=1;
        this->training_time=player->information.super_time_constructoin;
        break;

    case 2:
        this->name=player->information.vehicle_unitMaker_name;
        this->cost=player->information.vehicle_unitMaker_cost;
        this->upgrade_cost=player->information.vehicle_unitMaker_upgrade_cost;
        this->construction_time=player->information.vehicle_unitMaker_time_constructoin;
        this->max_health=player->information.vehicle_unitMaker_max_health;
        this->attack_damage=player->information.vehicle_unitMaker_attack_damage;
        this->attack_range=player->information.vehicle_unitMaker_attack_range;
        this->attack_delay=player->information.vehicle_unitMaker_attack_delay;
        this->unitType=2;
        this->training_time=player->information.vehicle_time_constructoin;
        break;

    }

    health=max_health;
    training_progress=0;
    queuecount=0;

}

int UnitMaker::getTrainingTime(){
    return training_time;
}

bool UnitMaker::trainUnit(QLabel* label){//add unit in queue
    if(queuecount>7){
        label->show();
        label->setText("The unit maker is full");
        return false;
    }
    else{
        queuecount++;
        int temp_cost=0;

        switch  (unitType){
            case 0:
                temp_cost=player->information.normal_cost;
                break;
            case 1:
                temp_cost=player->information.super_cost;
                break;
            case 2:
                temp_cost=player->information.vehicle_cost;
                break;
        }

        if(temp_cost>player->getMoney()){
            label->show();
            label->setText("Not enough gold");
            return false;
        }
        player->setMoney(-temp_cost);
        return true;
    }
}

double UnitMaker::getTrainingProgress(){
    return training_progress;
}

int UnitMaker::queueCount(){
    return queuecount;
}

void UnitMaker::setTrainingTime(int _training_time){
    training_time=_training_time;
}

void UnitMaker::setTrainingProgress(double _training_progress){
    training_progress+=_training_progress;
}

int UnitMaker::getUnitType(){
    return unitType;
}

void UnitMaker::setQueueCount(int n){
    queuecount+=n;
}

bool UnitMaker::upgrade(){

	if(level >= 3)
		return false;


    if(unitType==0){
		if(player->getMoney() < player->information.unitMaker_upgrade_cost)
			return false;
		else
			player->setMoney( -player->information.unitMaker_upgrade_cost);
    }


    if(unitType==1){
		if(player->getMoney() < player->information.super_unitMaker_upgrade_cost)
			return false;
		else
			player->setMoney( -player->information.super_unitMaker_upgrade_cost);
    }


    if(unitType==2){
		if(player->getMoney() < player->information.vehicle_unitMaker_upgrade_cost)
			return false;
		else
			player->setMoney( -player->information.vehicle_unitMaker_upgrade_cost);
    }

	level++;
	return true;

}

string UnitMaker::getStatus(){

    char status[100];
    sprintf(status,"this unit Maker have %d unit in queue this time" , queuecount);
    return status;
}


