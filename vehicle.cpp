#include "vehicle.h"
#include "block.h"
#include "player.h"
#include "superunit.h"
#include "normalunit.h"
#include "map.h"

Vehicle::Vehicle(Map* _map,Player* player) :Unit(_map){
    units_count=0;
    gameObjectType=6;

    this->name=player->information.vehicle_name;
    this->cost=player->information.vehicle_cost;
    this->training_time=player->information.vehicle_time_constructoin;
    this->max_health=player->information.vehicle_max_health;
    this->attack_damage=player->information.vehicle_attack_damage;
    this->attack_range=player->information.vehicle_attack_range;
    this->attack_delay=player->information.vehicle_attack_delay;
    this->speed=player->information.vehicle_speed;
    this->capacity=player->information.vehicle_capacity;

    health=max_health;

}

int Vehicle::getCapacity(){
    return capacity;
}

vector<Unit*> Vehicle::getUnits(){
    return units;
}

void Vehicle::unload(){

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
                	units[k]->Out_Vehicle();
                    units[k]->setPlace(i,j);
                    map->getBlock(i,j)->addObject(units[k]);
                }
                units.clear();
                return;
            }

/**/

}

bool Vehicle::addUnit(Unit* _unit){

    if(_unit->getType()==6)
        return false;
    if(units_count >= capacity )
        return false;
    units.push_back(_unit);
    units_count++;
    _unit->stop();
    return true;
}

bool Vehicle::upgrade(){

	level++;
	max_health+= max_health /2;
	health+= health/2;
	speed+= speed /4;
	return true;

}

string Vehicle::getStatus(){
    char status[100];
    sprintf(status,"there are %d unit in vehicle",units_count);
    return status;
}
