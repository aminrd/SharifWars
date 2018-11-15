#include "iostream"
#include <time.h>
#include "cstdlib"
#include "checker.h"
#include "unit.h"
#include "superunit.h"
#include "vehicle.h"
#include "normalunit.h"
#include "base.h"
#include "game.h"
#include "unit.h"
#include "gameobject.h"
#include "player.h"
#include "map.h"
#include "defence.h"
#include "base.h"
#include "place.h"
#include "moneymaker.h"
#include "unitmaker.h"
#include "building.h"
#include "zombie.h"
#include "endgame.h"

using namespace std;

Game* Game::instance=0;

Game* Game::getInstance(){
    if(instance==0)
        instance=new Game;
    return instance;
}

void Game::newGame(vector<Player*> _players , Map* _map){
    srand(time(NULL));
    map=_map;
    players=_players;
}

void Game::SetGameObject(){
    for(unsigned int i=0; i<players.size(); i++){
        vector<GameObject*> temp=players[i]->getPlayerObject();
        for(unsigned int j=0; j<temp.size(); j++){
            game_objects.push_back(temp[j]);
        }
    }
}

vector<Player*> Game::getPlayers(){
    vector <Player*> temp_players;
    vector <GameObject*> objects;
    for(unsigned int i=0; i<players.size(); i++){
        //if(players[i]!=NULL)
            temp_players.push_back(players[i]);
    }
    return temp_players;
}

vector<GameObject*> Game::getObjects(){
    vector <GameObject*> temp;
    for(unsigned int i=0; i<game_objects.size(); i++)
		if(game_objects[i] != NULL)
			temp.push_back(game_objects[i]);
	return temp;
}


vector<Building*> Game::getBuildings(){
	vector <Building*> temp;
	Building* temp_build;
    for(unsigned int i=0; i<game_objects.size(); i++)
		if(game_objects[i] != NULL)
			if(game_objects[i]->getType()<4){
				temp_build=dynamic_cast <Building*> (game_objects[i]);
				temp.push_back(temp_build);
			}
	return temp;
}


vector<class Unit*> Game::getUnits(){
	vector <Unit*> temp;
	Unit* temp_unit;
    for(unsigned int i=0; i<game_objects.size(); i++)
		if(game_objects[i] != NULL)
			if(game_objects[i]->getType() < 3){
				temp_unit=dynamic_cast <Unit*> (game_objects[i]);
				temp.push_back(temp_unit);
			}
	return temp;
}


bool Game::constructBuilding(Player* player, int buildingType, int row,int col, QLabel* label){

    //---------------------------------------------------------------check the building isn't second base

    if(buildingType==0)
        if(player->getPlayerObject().size()>0){
            label->show();
            label->setText("You build base before");
            return false;
        }

    //---------------------------------------------------------------check that base build first

    if(buildingType>0)
        if(player->getPlayerObject().size()==0){
            label->show();
            label->setText("You must build Base first");
            return false;
        }

    //---------------------------------------------------------------create a map

    int** map_a=NULL;
    map_a=new int* [map->GetRowcount()];
    for(int i=0; i<map->GetRowcount(); i++)
        map_a[i]=new int [map->GetColcount()];

    //--------------------------------------initialize map_a
    for(int i=0; i<map->GetRowcount(); i++)
        for(int j=0; j<map->GetColcount(); j++)
            map_a[i][j]=0;

    int height_building=0;
    int width_building=0;

    if(buildingType==1){
        height_building=2;
        width_building=2;
    }
    else{
        width_building=4;
        height_building=3;
    }

    //------------------------------------------------------------------Check building place in page or not

    if(col+width_building>map->GetColcount()){

		for(int i=0; i<map->GetRowcount(); i++)//delete array of map
            delete []map_a[i];
		delete []map_a;

        label->show();
        label->setText("Your Building isn't in page");
        return false;
    }

    if(row+height_building>map->GetRowcount()){

        for(int i=0; i<map->GetRowcount(); i++)//delete array of map
			delete []map_a[i];
		delete []map_a;

        label->show();
        label->setText("Your Building isn't in page");
        return false;
    }


    //================================================================== Check area is for this Player

    vector <Block*> temp_area=player->getPlayerArea();
    for(unsigned int i=0; i<temp_area.size(); i++){
        map_a[temp_area[i]->getRow()][temp_area[i]->getCol()]=-1;
    }

    for(int i=row; i<row+height_building; i++)
        for(int j=col; j<col+width_building; j++){
            if(map_a[i][j]!=-1){

				for(int i=0; i<map->GetRowcount(); i++)//delete array of map
					delete []map_a[i];
				delete []map_a;

                label->show();
                label->setText("You must build in your area");
                return false;
            }
        }
/**/
	for(int i=0; i<map->GetRowcount(); i++)//delete array of map
		delete []map_a[i];
	delete []map_a;

    //-------------------------------------------------------------------check is enough money

    int temp_cost=0;
    switch (buildingType){
        case 0:
            temp_cost=player->information.base_cost;
            break;
        case 1:
            temp_cost=player->information.defence_cost;
            break;
        case 2:
            temp_cost=player->information.moneyMaker_cost;
            break;
        case 3:
            temp_cost=player->information.unitMaker_cost;
            break;
        case 4:
            temp_cost=player->information.super_unitMaker_cost;
            break;
        case 5:
            temp_cost=player->information.vehicle_unitMaker_cost;
            break;
    }

    if(player->getMoney()<temp_cost){
        label->show();
        label->setText("Not enough gold");
        return false;
    }
/**/
    //================================================================== check is blocks empty


    for(int i=row; i<row+height_building; i++)
        for(int j=col; j<col+width_building; j++){
            if(i>0 && i<map->GetRowcount())
                if(j>0 && j<map->GetColcount())
                    if(!map->getBlock(i,j)->getEmpty()){
                        label->show();
                        label->setText("You must build in empty area");
                        return false;
                    }
        }

    for(int i=row-1; i<row+height_building+1; i++)
        for(int j=col-1; j<col+width_building+1; j++){
            if(i>0 && i<map->GetRowcount())
                if(j>0 && j<map->GetColcount())
                    if(!map->getBlock(i,j)->Empty_Of_Building()){
                        label->show();
                        label->setText("You must build in empty area");
                        return false;
                    }
        }

    //when all above condition be true construction is possible
/**/
  //------------------------------------------------------------------ construct a build
    Building* build=NULL;

    switch(buildingType){

    case 0:
        build=new Base(map,player);
        player->addBuilding(build);
        break;

    case 1:
        build=new Defence(map,player);
        player->addBuilding(build);
        break;

    case 2:
        build=new MoneyMaker(map,player);
        player->addBuilding(build);
        break;

    case 3:
        build=new UnitMaker(map,player,0);
        player->addBuilding(build);
        break;

    case 4:
        build=new UnitMaker(map,player,1);
        player->addBuilding(build);
        break;

    case 5:
        build=new UnitMaker(map,player,2);
        player->addBuilding(build);
        break;
    }

    game_objects.push_back(build);
    player->setMoney(-temp_cost);
    build->setPlace(row,col);
    build->SetPlayer(player);

    for(int i=row; i<row+height_building; i++)
        for(int j=col; j<col+width_building; j++)
            map->getBlock(i,j)->addObject(build);

    return true;
}//end of construct building function


bool Game::constructUnit(Player* player, Building* building, QLabel* label){

    UnitMaker* temp_unitMaker= dynamic_cast <UnitMaker*> (building);
    if(temp_unitMaker==false)
        return false;
    temp_unitMaker->trainUnit(label);
        return true;
}

bool Game::Build_Unit(Player* player,Building* building){

    Unit* unit=NULL;
    int build_type=building->getUnitType();
//-----------------------------------------------------build unit
    switch (build_type){

        case 0:
            unit=new NormalUnit(map,player);
            player->addUnit(unit);
            break;

        case 1:
            unit=new SuperUnit(map,player);
            player->addUnit(unit);
            break;

        case 2:
            unit=new Vehicle(map,player);
            player->addUnit(unit);
            break;

    }

    game_objects.push_back(unit);

    //-----------------------------------------------------find a place to put unit
    int height=3;
    int width=4;
    int row=building->getBlock()->getRow();
    int col=building->getBlock()->getCol();

    if(row>0){
        if(col>0){
            map->getBlock(row-1,col-1)->addObject(unit);
            row=row-1;
            col=col-1;
        }
        else{
            map->getBlock(row-1, col+width)->addObject(unit);
            row=row-1;
            col=col+width;
        }

    }
    else{
        if(col>0){
            map->getBlock(row+height, col-1)->addObject(unit);
            row=row+height;
            col=col-1;
        }
        else{
            map->getBlock(row+height, col+width)->addObject(unit);
            row=row+height;
            col=col+width;
        }
    }

    UnitMaker* temp_unitMaker=dynamic_cast <UnitMaker*> (building);
    temp_unitMaker->setQueueCount(-1);

	for(int i=1; i< building->getLevel(); i++)
		unit->upgrade();
    unit->setPlace(row,col);
    unit->SetPlayer(player);
    return true;
}



class Map* Game::getMap(){
    return map;
}

bool Game::constructZombie(Player* player){

    //--------------------------------------create zombie
    Zombie* zombie=new Zombie(map,player);
    game_objects.push_back(zombie);
    zombie->SetPlayer(player);
    player->addUnit(zombie);

    //--------------------------------------put zombie in map

    vector<Block*> empty_block;
    for(int i=0; i<map->GetRowcount(); i++)
        for(int j=0; j<map->GetColcount(); j++)
            if(map->getBlock(i,j)->getEmpty())
                empty_block.push_back(map->getBlock(i,j));
    int random=rand()%empty_block.size();

    map->getBlock(empty_block[random]->getRow(),empty_block[random]->getCol())->addObject(zombie);
    zombie->setPlace(empty_block[random]->getRow(),empty_block[random]->getCol());

    return true;
}

void Game::advanceGame(){

//------------------------------------------------------increase money of player
    for(unsigned int i=0; i<game_objects.size(); i++){
        if(game_objects[i] !=NULL)
            if(game_objects[i]->getType()==2){
                MoneyMaker* temp_moneyMaker = dynamic_cast <MoneyMaker*> (game_objects[i]);
                if(temp_moneyMaker->getConstructionProgress()>=1)
                    temp_moneyMaker->getPlayer()->setMoney( temp_moneyMaker->getIncome());
            }

    }
//-----------------------------------------------------set target for objects that TargetObject=NULL

	for(unsigned int i=0; i<game_objects.size(); i++)
		if(game_objects[i] != NULL)
			if(game_objects[i]->getTargetObject()==NULL)
				if(game_objects[i]->GetRoad().size() ==0){

				    vector <Block*> rangeBlock;
					rangeBlock=game_objects[i]->getBlocksInRange();
					//---------------------------------------check set Target is possilbe
					for(unsigned int k=0; k<rangeBlock.size(); k++){

						vector <GameObject*> temp=rangeBlock[k]->getObjects();

						for(unsigned int j=0; j<temp.size(); j++)
							if(temp[j] != NULL)
								if( game_objects[i]->getPlayer()->getTeam() != temp[j]->getPlayer()->getTeam() ){
									game_objects[i]->setTargetObject(temp[j]);
								}

						temp.clear();
					}

				}


//----------------------------------------------------follow target object

    for(unsigned int i=0; i<game_objects.size(); i++)
        if(game_objects[i]!=NULL)
            if(game_objects[i]->getTargetObject()!=NULL){

                GameObject* target=game_objects[i]->getTargetObject();

                if(game_objects[i]->getPlayer()->getTeam()== game_objects[i]->getTargetObject()->getPlayer()->getTeam()){
                    if(game_objects[i]->getType()>3){//if target is friend then for any work my object must be unit

                        //---------------------------------------------------------put in tower or vehicle
                        if(target->getType()==6 || target->getType()==1){
                            bool flag=false;
                            //----------------------------------------------------check can put in tower or vehicle
                            int Startx=game_objects[i]->getBlock()->getCol()- game_objects[i]->getSpeed();
                            int Starty=game_objects[i]->getBlock()->getRow()- game_objects[i]->getSpeed();
                            int Endx=game_objects[i]->getBlock()->getCol()+ game_objects[i]->getSpeed();
                            int Endy=game_objects[i]->getBlock()->getRow()+ game_objects[i]->getSpeed();
                            //---------------------------------------------------- set x,y valid
                            if(Startx<0)
                                Startx=0;
                            if(Starty<0)
                                Starty=0;

                            if(Endx >= map->GetColcount())
                                Endx= map->GetColcount()-1;
                            if(Endy >= map->GetRowcount())
                                Endy= map->GetRowcount()-1;

                            for(int j=Starty; j<Endy; j++){
                                if(flag==true)
                                    break;
                                for(int k=Startx; k<Endx; k++)
                                    if(game_objects[i]->ObjectIsRange(target)){
                                        Unit* temp_unit=dynamic_cast <Unit*> (game_objects[i]);
                                        if(target->addUnit(temp_unit)==true){
                                            temp_unit->getBlock()->removeObject(temp_unit);
                                            temp_unit->In_Vehicle();
                                            flag=true;
                                            break;
                                        }
                                    }
                            }

                            if(flag==false)
                                game_objects[i]->Move_Nearest_Block();
                        }

                        //---------------------------------------------------------follow friend unit or building
                        if(target->getType()!=6 && target->getType()!=1)
                            game_objects[i]->Move_Nearest_Block();

                    }
                }

                else{

                    //if(game_objects[i]->getPlayer()->getTeam() == game_objects[i]->getTargetObject()->getPlayer()->getTeam()) {

                    if(game_objects[i]->ObjectIsRange(target))
                        game_objects[i]->Attack(target);
                    else
                        game_objects[i]->Move_Nearest_Block();

                }

 /**/

            }



/**/
//----------------------------------------------------attack all game object

    for(unsigned int i=0; i<game_objects.size(); i++){
        if(game_objects[i]!=NULL){

            if(game_objects[i]->getType()<4){
                Building* temp_build= dynamic_cast <Building*> (game_objects[i]);
                if(temp_build->getConstructionProgress()>=1)
                    game_objects[i]->AttackPossible();
            }
            else
                game_objects[i]->AttackPossible();

		}
    }

//------------------------------------------------------move zombie random

    for(unsigned int i=0; i<game_objects.size(); i++)
        if(game_objects[i]!=NULL)
            if(game_objects[i]->getType()==7 && game_objects[i]->getTargetObject()==NULL && game_objects[i]->GetRoad().size()==0){

                vector<Block*> empty_block;
                for(int i=0; i<map->GetRowcount(); i++)
                    for(int j=0; j<map->GetColcount(); j++)
                        if(map->getBlock(i,j)->getEmpty())
                            empty_block.push_back(map->getBlock(i,j));
                int random=rand()%empty_block.size();
                game_objects[i]->moveToBlock(empty_block[random]->getRow(),empty_block[random]->getCol());
            }



//------------------------------------------------------create zombie from dead unit

    Player* temp_player;
    for(unsigned int i=0; i<game_objects.size(); i++)
        if(game_objects[i]!=NULL)
            if(game_objects[i]->getType()==7)
                temp_player=game_objects[i]->getPlayer();


    for(unsigned int i=0; i<game_objects.size(); i++)
        if(game_objects[i]!=NULL)
            if(game_objects[i]->getHealth()<=-10000){
                //--------------------------------------create zombie
                Zombie* zombie=new Zombie(map,temp_player);
                game_objects.push_back(zombie);
                zombie->SetPlayer(temp_player);
                temp_player->addUnit(zombie);

                //--------------------------------------put zombie in map
                Block* block=game_objects[i]->getBlock();
                zombie->setPlace(block->getRow(),block->getCol());
                map->getBlock(block->getRow(),block->getCol())->addObject(zombie);
            }




//------------------------------------------------------kill all health<=0

    for(unsigned int i=0; i<game_objects.size(); i++){
        if(game_objects[i]==NULL)
            continue;
        if(game_objects[i]->getHealth()<=0){
            int x,y;


            //--------------------------------------------------remove from map
            x=game_objects[i]->getBlock()->getCol();
            y=game_objects[i]->getBlock()->getRow();

            if(game_objects[i]->getType()<4){

            	if(game_objects[i]->getType()==1)//if gameObject is defence unload units
					game_objects[i]->unload();

                Building* temp_building=dynamic_cast <Building*> (game_objects[i]);
                for(int j=y; j<y+temp_building->getHeight(); j++)
                    for(int k=x; k<x+temp_building->getWidth(); k++)
                        map->getBlock(j,k)->removeObject(game_objects[i]);
            /**/
            }
            else{
                map->getBlock(y,x)->removeObject(game_objects[i]);

				//------------------------------------------------------------kill unit in vehicle
				if(game_objects[i]->getType()==6) {
					Vehicle* temp_vehicle= dynamic_cast <Vehicle*> (game_objects[i]);
					vector <Unit*> units= temp_vehicle->getUnits();

					for(unsigned int l=0; l<units.size(); l++)
						for(unsigned int j=0; j<game_objects.size(); j++) //delete unit and  Target Object
							if(game_objects[j] !=NULL){

								if(game_objects[j]->getTargetObject()==units[l])//delete target object
									game_objects[j]->stop();

								if(game_objects[j]==units[l]){//delete unit
									delete game_objects[j];
									game_objects[j]=NULL;
								}
							}
				}
            }

            for(unsigned int j=0; j<game_objects.size(); j++){//delete Target Object
                if(game_objects[j] !=NULL)
                    if(game_objects[j]->getTargetObject()==game_objects[i])
                        game_objects[j]->stop();
            }

            delete game_objects[i];
            game_objects[i]=NULL;
        }

    }

//------------------------------------------------------move object

    for(unsigned int i=0; i<game_objects.size(); i++){

        if(game_objects[i]!=NULL)
        if(4 <= game_objects[i]->getType()){

                vector<place> temp_place;
                temp_place=game_objects[i]->GetRoad();

				if(temp_place.size() >0)
					for(int l=0; l<game_objects[i]->getSpeed(); l++) {

						Block* block=game_objects[i]->getBlock();
						int currentX=block->getCol();
						int currentY=block->getRow();

						for(unsigned int k=0; k<temp_place.size(); k++){
							if(temp_place[k].x==currentX && temp_place[k].y==currentY){

								if(k==0){//we are in end of road
									game_objects[i]->stop();
									break;
								}

								map->getBlock(temp_place[k-1].y,temp_place[k-1].x)->addObject(game_objects[i]);
								map->getBlock(temp_place[k].y,temp_place[k].x)->removeObject(game_objects[i]);
								game_objects[i]->setPlace(temp_place[k-1].y,temp_place[k-1].x);

								break;
							}

						}

					}


        }
    }
    /**/


//------------------------------------------------------progress buildings

    for(unsigned int i=0; i<game_objects.size(); i++){
        if(game_objects[i]!=NULL)
            if(game_objects[i]->getType()<4){
                Building* temp_building= dynamic_cast <Building*> (game_objects[i]);
                double progress=temp_building->getConstructionProgress();
                if(progress<1)
                    temp_building->setConstructionProgress( 1.0/temp_building->getConstructionTime());
            }
    }

/**/
//------------------------------------------------------Training units

    for(unsigned int i=0; i<game_objects.size(); i++){
        if(game_objects[i]!=NULL)
            if(game_objects[i]->getType()==3){

                UnitMaker* temp_UnitMaker = dynamic_cast <UnitMaker*> (game_objects[i]);

                if(temp_UnitMaker->getConstructionProgress()<1)
                    continue;

                if(temp_UnitMaker->queueCount()>0)
                    temp_UnitMaker->setTrainingProgress( 1.0/ temp_UnitMaker->getTrainingTime());
                else
                    continue;

                if(temp_UnitMaker->getTrainingProgress()>=1){
                    this->Build_Unit(temp_UnitMaker->getPlayer(),temp_UnitMaker);
                    temp_UnitMaker->setTrainingProgress(- temp_UnitMaker->getTrainingProgress()); //set training progress=0
                }

            }
    }

//-------------------------------------------------------decrease delaying of attack

	for(unsigned int i=0; i<game_objects.size(); i++)
		if(game_objects[i] != NULL){
				game_objects[i]->setStopingAttack();
				game_objects[i]->setstopingSpecialAttack();
		}

//-------------------------------------------------------mana regeneration

	for(unsigned int i=0; i<game_objects.size(); i++)
		if(game_objects[i] != NULL){
			SuperUnit* temp_super=dynamic_cast <SuperUnit*> (game_objects[i]);
			if(temp_super !=0)
				temp_super->manaRegeneration();
		}

//-------------------------------------------------------Kill a player
    for(unsigned int i=0; i<players.size(); i++)
        if(players[i]!= NULL)
            if(players[i]->getPlayerBuilding().size()>0){
                vector<Building*> temp_building=players[i]->getPlayerBuilding();
                if(temp_building[0]==NULL){
                    vector <GameObject*> temp=players[i]->getPlayerObject();
                    for(unsigned int j=0; j<players[i]->getPlayerObject().size(); j++)
                        if(temp[j]!=NULL)
                                temp[j]->setHealth(0);
                }
                else{
                    if(temp_building[0]->getHealth()<=0){
                        vector <GameObject*> temp=players[i]->getPlayerObject();
                        for(unsigned int j=0; j<players[i]->getPlayerObject().size(); j++)
                            if(temp[j]!=NULL)
                                    temp[j]->setHealth(0);
                    }
                }
                /**/
            }


    for(unsigned int i=0; i<players.size(); i++){

        bool flag=false;
        vector <GameObject*> temp;
        if(players[i]!=NULL){
            temp=players[i]->getPlayerObject();
            for(unsigned int j=0; j<game_objects.size(); j++){
                if(game_objects[j]!=NULL)
                    if(game_objects[j]->getHealth()>0 && game_objects[j]->getPlayer()==players[i]){
                        flag=true;
                        break;
                    }
            }
            if(flag==true)
                continue;
            else{
                players[i]=NULL;
            }
        }
    }


//-------------------------------------------------------Check end of game

    int winner=0;
    vector<Player*> player_live;

    for(unsigned int i=0; i<players.size(); i++)
        if(players[i]!=NULL)
            player_live.push_back(players[i]);

    winner=player_live[0]->getTeam();
    for(int i=1; i<player_live.size(); i++)
        if(player_live[i]->getTeam()!=winner)
            return;

    EndGame* End=new EndGame(winner+1);
    End->show();


//---------------------------------------------------------

}//end of advance game

Game::~Game(){
    delete map;
    delete instance;
}
