#include "defence.h"
#include "map.h"
#include "unit.h"
#include "player.h"

Defence::Defence(Map* _map,class Player* player) :Building(_map){

    units_count=0;
    gameObjectType=1;
    height=2;
    width=2;

    this->name=player->information.defence_name;
    this->cost=player->information.defence_cost;
    this->upgrade_cost=player->information.defence_upgrade_cost;
    this->construction_time=player->information.defence_time_constructoin;
    this->max_health=player->information.defence_max_health;
    this->attack_damage=player->information.defence_attack_damage;
    this->attack_range=player->information.defence_attack_range;
    this->attack_delay=player->information.defence_attack_delay;

    health=max_health;


}

vector<Unit*> Defence::getUnits(){
    return units;
}

bool Defence::addUnit(Unit* _unit){
    if(units_count<4){
        units.push_back(_unit);
        units_count++;
        _unit->stop();
        return true;
    }
    return false;
}

void Defence::unload(){


    int startx=place_x-1;
    int starty=place_y-1;
    int endx=place_x+1;
    int endy=place_y+1;

    if(startx<0)
        startx=0;
    if(starty<0)
        starty=0;
    if(endx>=map->GetColcount())
        endx=map->GetColcount()-1;
    if(endy>=map->GetRowcount())
        endy=map->GetRowcount()-1;

    for(int i=starty; i<endy+1; i++ )
        for(int j=startx; j<endx+1; j++)
            if(map->getBlock(i,j)->Empty_Of_Building()){
                for(unsigned int k=0; k<units.size(); k++){
                    units[k]->setPlace(i,j);
                    units[k]->Out_Vehicle();
                    map->getBlock(i,j)->addObject(units[k]);
                }
                units.clear();
                return;
            }
}

bool Defence::upgrade(){

	if(level>=3)
		return false;

	if(player->getMoney() < player->information.defence_upgrade_cost)
		return false;

	level++;
	player->setMoney(- player->information.defence_upgrade_cost);
	attack_damage+= attack_damage / 4;
	attack_range+= attack_range /4;
	return true;

}

string Defence::getStatus(){
    char status[100];
    sprintf(status,"there are %d unit in tower" , units.size());
    return status;
}


int Defence::getCapacity(){
    return units_count;
}

Defence::~Defence(){

}
