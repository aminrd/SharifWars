#include "building.h"
#include "player.h"

Building::Building(Map* _map) :GameObject(_map){
    construction_progress=0;
}

int Building::getWidth(){
    return width;
}

int Building::getHeight(){
    return height;
}

int Building::getConstructionTime(){
    return construction_time;
}

int Building::getCostUpgrde(){
    return upgrade_cost;
}

double Building::getConstructionProgress(){
    return construction_progress;
}

void Building::setCostUpgrade(int _money){
    upgrade_cost=_money;
}

void Building::sell(){
	if(gameObjectType != 0) {
		player->setMoney(cost/2);
		health=0;
	}
}

void Building::setConstructionProgress(double _progress){
    construction_progress+=_progress;
    if(construction_progress>1)
        construction_progress=1;
}

Building::~Building(){

}
