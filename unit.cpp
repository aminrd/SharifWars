#include "unit.h"
#include "map.h"
#include "place.h"

Unit::Unit(Map* _map):GameObject(_map){
    myRoad.clear();
    health=max_health;
}

int Unit::getSpeed(){
    return speed;
}

struct Parent_road{
    int x;
    int y;
    int parent_x;
    int parent_y;
};

void Unit::moveToBlock(Block* _block){

	if(_block->Empty_Of_Building()==false){

		int number=0;//number of game object in the block
        vector <GameObject*> temp_move;
        temp_move=_block->getObjects();

        for(unsigned int k=0; k<temp_move.size(); k++)
            if(temp_move[k]!=NULL)
                number=k;

		this->setTargetObject(temp_move[number]);
		return;
	}


    myRoad.clear();
    //-------------------------------------------------build temp Map
    block=_block;
    int** map_array=NULL;
    map_array=new int*[map->GetRowcount()];
    for(int i=0; i<map->GetRowcount(); i++)
        map_array[i]=new int[map->GetColcount()];

    //-------------------------------------------------- fill the map with empty or not empty

    for(int i=0; i<map->GetRowcount(); i++)
        for(int j=0; j<map->GetColcount(); j++)
            if(map->getBlock(i,j)->Empty_Of_Building()==true)
                map_array[i][j]=-1;
            else
                map_array[i][j]=-2;

    //---------------------------------------------------

    vector <Parent_road> road;//road is a queue of block
    Parent_road temp;
    temp.x=place_x;
    temp.y=place_y;
    temp.parent_x=0;
    temp.parent_y=0;
    road.push_back(temp);

   map_array[place_y][place_x]=0;

   for(int k=0; true; k++){

       int j=road[k].x;
       int i=road[k].y;
       //----------------------set all neighberhood with K+1
       BfsHelper(k,i,j,i,j+1,map_array,map->GetRowcount(),map->GetColcount(),road);
       BfsHelper(k,i,j,i,j-1,map_array,map->GetRowcount(),map->GetColcount(),road);
       BfsHelper(k,i,j,i-1,j,map_array,map->GetRowcount(),map->GetColcount(),road);
       BfsHelper(k,i,j,i+1,j,map_array,map->GetRowcount(),map->GetColcount(),road);
       BfsHelper(k,i,j,i-1,j-1,map_array,map->GetRowcount(),map->GetColcount(),road);
       BfsHelper(k,i,j,i-1,j+1,map_array,map->GetRowcount(),map->GetColcount(),road);
       BfsHelper(k,i,j,i+1,j-1,map_array,map->GetRowcount(),map->GetColcount(),road);
       BfsHelper(k,i,j,i+1,j+1,map_array,map->GetRowcount(),map->GetColcount(),road);
       if(i==block->getRow() && j==block->getCol())//we arrive end block
           break;
   }
    //---------------------------------------------------- find road

    myRoad.clear();

    int i=block->getRow();//set i equal end block
    int j=block->getCol();//set j equal end block

    while(true){

        for(unsigned int k=0; k<road.size(); k++)
            if(i==road[k].y && j==road[k].x){

                place temp;
                temp.y=i;
                temp.x=j;

                myRoad.push_back(temp);
                i=road[k].parent_y;
                j=road[k].parent_x;

            }
            if(i==this->place_y && j==this->place_x){// we arrive start block
                place temp;
                temp.y=i;
                temp.x=j;
                myRoad.push_back(temp);
                break; //break from while
            }
    }


	for(int i=0; i<map->GetRowcount(); i++)//delete array of map
		delete []map_array[i];
	delete []map_array;

}

void Unit::moveToBlock(int row, int col){
    block=map->getBlock(row,col);
    this->moveToBlock(block);
}

void Unit::stop(){
    target_object=NULL;
    myRoad.clear();
}

vector <place> Unit::GetRoad(){
    return myRoad;
}


void Unit::BfsHelper(int &k,int i,int j,int _i,int _j,int** _map_array,int rowcount,int colcount,vector<Parent_road> &_road){
    Parent_road temp;
        if(_i>=0 && _i<rowcount && _j>=0 && _j<colcount)
            if(_map_array[_i][_j]==-1){
                _map_array[_i][_j]=k+1;
                Parent_road temp;
                temp.x=_j;
                temp.y=_i;
                temp.parent_x=j;
                temp.parent_y=i;
                _road.push_back(temp);
            }
}
