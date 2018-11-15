#include "superunit.h"
#include "player.h"
#include "map.h"

SuperUnit::SuperUnit(Map* _map,Player* player) :Unit(_map){
    gameObjectType=5;

    this->name=player->information.super_name;
    this->cost=player->information.super_cost;
    this->training_time=player->information.super_time_constructoin;
    this->max_health=player->information.super_max_health;
    this->attack_damage=player->information.super_attack_damage;
    this->attack_range=player->information.super_attack_range;
    this->attack_delay=player->information.super_attack_delay;
    this->speed=player->information.super_speed;
    this->max_mana=player->information.super_max_mana;
    this->mana_regeneration=player->information.super_regenition;
    this->specialattack=player->information.super_attack_special_damage;

    health=max_health;
    mana=max_mana;
    stoping_of_specialAttack=0;
}

int SuperUnit::getMaxMana(){
    return this->max_mana;
}

int SuperUnit::getMana(){
    return this->mana;
}

int SuperUnit::getManaRegenerationAmount(){
    return this->mana_regeneration;
}

int SuperUnit::getSpecialAttackDamage(){
    return this->specialattack;
}

int SuperUnit::getManaCost(){
    return this->manaCost;
}

void SuperUnit::specialAttack(GameObject* game_object){

	if(stoping_of_specialAttack >0)
		return;
    if(mana<manaCost)
       return;
    if(game_object==NULL)
        return;

    Player *temp= game_object->getPlayer();
    Player *my_player=this->player;

    if(temp->getTeam() != my_player->getTeam()){
        if(this->ObjectIsRange(game_object)){
            mana-=manaCost;
            stoping_of_specialAttack=attack_delay+1;
            game_object->Damage(specialattack);
        }
    }
}

bool SuperUnit::upgrade(){

	level++;
	max_health+= max_health /4;
	health+= health/4;
	attack_damage+= attack_damage/4;
	max_mana+= (max_mana * 15 ) / 100;
	mana+= (mana * 15) / 100;
	specialattack+= (specialattack*15) / 100;
	return true;

}

void SuperUnit::manaRegeneration(){

	if(mana<max_mana)
		mana+= mana_regeneration;
	if(mana>max_mana)
		mana=max_mana;

}

void SuperUnit::setstopingSpecialAttack(){
	if(stoping_of_specialAttack>0)
		stoping_of_specialAttack--;
}


string SuperUnit::getStatus(){

    char status[100];
    if(myRoad.size()==0)
        sprintf(status,"this unit don't go any where");
    else
        sprintf(status,"this unit go to block (%d,%d)",myRoad[0].y,myRoad[0].x);

    return status;
}


