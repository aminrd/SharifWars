#include <math.h>
#include "gameobject.h"
#include "building.h"
#include "place.h"
#include "map.h"
#include "player.h"

GameObject::GameObject(Map* _map,int _place_x, int _place_y):map(_map){
    level=1;
    target_object=NULL;
    place_x=_place_x;
    place_y=_place_y;
    stoping_of_attack=0;
    inVehicle=false;
}

void GameObject::SetPlayer(Player* _player){
    player=_player;
}

Block* GameObject::getBlock(){
	if(inVehicle==false)
		return map->getBlock(place_y,place_x);
	else
		return NULL;
}

int GameObject::getStopingAttack(){
	return stoping_of_attack;
}

Player* GameObject::getPlayer(){
    return player;
}

QString GameObject::getName(){
    return this->name;
}

int GameObject::getMaxHealth(){
    return this->max_health;
}

int GameObject::getHealth(){
    return this->health;
}

int GameObject::getAttackDamage(){
    return this->attack_damage;
}

int GameObject::getAttackRange(){
    return this->attack_range;
}

int GameObject::getAttackDelay(){
    return this->attack_delay;
}

int GameObject::getCost(){
    return this->cost;
}

vector<Block*> GameObject::getBlocksInRange(){
    int start_x,start_y;
    int end_x,end_y;

    start_x=place_x - attack_range;
    start_y=place_y - attack_range;
    if(start_x<0)
        start_x=0;
    if(start_y<0)
        start_y=0;

    //---------------------------------------------------in building attack range increase in end of x,y
    if(gameObjectType<4){
        Building* temp_building=dynamic_cast <Building*> (this);
        end_x=place_x + temp_building->getWidth() + attack_range;
    }
    else
        end_x=place_x + attack_range;

    if(gameObjectType<4){
        Building* temp_building=dynamic_cast <Building*> (this);
        end_y=place_y + temp_building->getHeight() + attack_range;
    }
    else
        end_y=place_y + attack_range;

    //------------------------------------------------------------

    if(end_x >= map->GetColcount())
        end_x= map->GetColcount()-1;
    if(end_y >= map->GetRowcount())
        end_y= map->GetRowcount()-1;

    vector<Block*> temp;
    for(int i=start_y; i<end_y; i++)
        for(int j=start_x; j<end_x; j++)
            temp.push_back(map->getBlock(i,j));

    return temp;
}

int GameObject::getLevel(){
    return level;
}

int GameObject::getType(){
    return gameObjectType;
}

void GameObject::setTargetObject(GameObject* object){
    target_object=object;
}

GameObject* GameObject::getTargetObject(){
    return this->target_object;
}

void GameObject::stop(){
    target_object=NULL;

}

bool GameObject::ObjectIsRange(GameObject *object){
    vector <Block*> range;
    range=this->getBlocksInRange();
    for(unsigned int i=0; i<range.size(); i++)
        if(range[i] == object->getBlock())
            return true;
    return false;
}

bool GameObject::Attack(GameObject* game_object){

    if(game_object==NULL)
        return false;
    Player *temp=game_object->getPlayer();
    Player *my_player=player;
    int id1=temp->getTeam();
    int id2=my_player->getTeam();

    if(id1 != id2){
    	if(stoping_of_attack==0){
            game_object->Damage(attack_damage);
            stoping_of_attack=attack_delay+1;
            return true;
    	}
    }
    return false;
}

bool GameObject::AttackPossible(){

    vector <Block*> rangeBlock;
    rangeBlock=this->getBlocksInRange();
    //---------------------------------------check attack is possilbe
    for(unsigned int i=0; i<rangeBlock.size(); i++){
        vector <GameObject*> temp=rangeBlock[i]->getObjects();
        for(unsigned int j=0; j<temp.size(); j++)
            if( this->Attack(temp[j]) )
                return true;
        temp.clear();
    }
    //----------------------------------------no object for attack
    return false;
}

void GameObject::Damage(int damage){
		health-=damage;
}

void GameObject::setStopingAttack(){
	if(stoping_of_attack>0)
		stoping_of_attack--;
}

void GameObject::setHealth(int _health){
    health=_health;
}

void GameObject::setLevel(int _level){
    level=_level;
}

void GameObject::setPlace(int placeY,int placeX){
    place_x=placeX;
    place_y=placeY;
}

void GameObject::Move_Nearest_Block(){

    Block* nearest=NULL;
    int temp_distance=1000000;

    int Startx=target_object->getBlock()->getCol()-1;
    int Starty=target_object->getBlock()->getRow()-1;
    int Endx=target_object->getBlock()->getCol()+2;
    int Endy=target_object->getBlock()->getRow()+2;

    Building* temp_target=dynamic_cast <Building*> (target_object);
    if(target_object->getType()<4){
        Endx=target_object->getBlock()->getCol() + temp_target->getWidth()+1;
        Endy=target_object->getBlock()->getRow() + temp_target->getHeight()+1;
    }
    //---------------------------------------------------- set x,y valid
    if(Startx<0)
        Startx=0;
    if(Starty<0)
        Starty=0;

    if(Endx >= map->GetColcount())
        Endx= map->GetColcount()-1;
    if(Endy >= map->GetRowcount())
        Endy= map->GetRowcount()-1;

    //---------------------------------------------------find nearest Block

    bool flag=false;

    for(int i=Starty; i<Endy; i++)
        for(int j=Startx; j<Endx; j++){

            vector<GameObject*> temp_search=map->getBlock(i,j)->getObjects();
            flag=false;
            for(unsigned int k=0; k<temp_search.size(); k++)
                if(temp_search[k]==target_object)
                    flag=true;
            if(flag==true)
                continue;

            if(fabs(i-place_y) + fabs(j-place_x) < temp_distance && map->getBlock(i,j)->Empty_Of_Building() )
                if(this->getBlock()!= map->getBlock(i,j)) {
                    temp_distance=fabs(i-place_y) + fabs(j-place_x);
                    nearest=map->getBlock(i,j);
                }

        }
    this->moveToBlock(nearest->getRow(),nearest->getCol());
}


void GameObject::Kill(){
    delete this;
}

GameObject::~GameObject(){

}

