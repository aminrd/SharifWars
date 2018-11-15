#include "iostream"
#include "player.h"
#include "unitmaker.h"
#include "unit.h"
#include "block.h"
#include "map.h"
#include "building.h"
#include "gameobject.h"
using namespace std;

Player::Player(){
}

Player::Player(QString _name, int _team, int _startingMoney, int _Player_ID, vector<Block*> _area){
    name=_name;
    team_ID=_team;
    money=_startingMoney;
    area=_area;
    Player_ID=_Player_ID;
}

int Player::getPlayerID(){
    return Player_ID;
}

QString Player::getName(){
    return name;
}

int Player::getTeam()const{
    return team_ID;
}

int Player::getMoney(){
    return money;
}

vector <Building*> Player::getPlayerBuilding(){
    return player_building;
}

vector<Block*> Player::getPlayerArea(){
    return area;
}

vector<GameObject*> Player::getPlayerObject(){
    return player_object;
}

vector <Unit*> Player::getPlayerUnit(){
    return player_unit;
}

vector <UnitMaker*> Player::getUnitMaker(){
    return player_unitMaker;
}

void Player::addBuilding(Building* _building){
    player_object.push_back(_building);
    player_building.push_back(_building);
}

void Player::addUnit(Unit* _unit){
    player_object.push_back(_unit);
    player_unit.push_back(_unit);
}

void Player::setMoney(int _money){
    money+=_money;
}

void Player::setMap(Map* _map){
    map=_map;
}

void Player::setArea(int _x,int _y,int _width, int _height){
    my_x=_x;
    my_y=_y;
    my_height=_height;
    my_width=_width;
    for(int i=my_x; i<my_x+my_width; i++)
        for(int j=my_y; j<my_y+my_width; j++)
            area.push_back(map->getBlock(i,j));
}

void Player::dead_Object(GameObject* _object){
    for(unsigned int i=0; i<player_object.size(); i++)
        if(_object==player_object[i])
            player_object[i]=NULL;
}
