#include "checker.h"
#include "player.h"
#include "map.h"
#include "block.h"
#include <iostream>
using namespace std;

Checker::Checker(){

}

void Checker::Print_map(Map* map){

    for(int i=0; i<map->GetColcount(); i++)
        cout<<"_";
    cout<<endl;

//-----------------------------------------------------------------show map

    for(int i=0; i<map->GetRowcount(); i++){
        for(int j=0; j<map->GetColcount(); j++){

            int number=0;//number of game object in the block
            vector <GameObject*> temp_checker;
            temp_checker=map->getBlock(i,j)->getObjects();

            for(unsigned int k=0; k<temp_checker.size(); k++)
                if(temp_checker[k]!=NULL)
                    number=k;

            //-----------------------------------------------------------------show empty block

            if(map->getBlock(i,j)->getEmpty()==true) { //show empty block
                cout<<" ";
                continue;
            }

            //-------------------------------------------------------------------show buiding

            if(temp_checker[number]->getType()==0) //show base building player
                cout<<"#";

            if(temp_checker[number]->getType()==1)//show Tower defence
                cout<<"*";

            if(temp_checker[number]->getType()==2)//show money Maker
                cout<<"$";

            if(temp_checker[number]->getType()==3){//show Unit maker
                int type=temp_checker[number]->getUnitType();
                switch (type){

                    case 0:
                        cout<<"-";
                        break;

                    case 1:
                        cout<<"+";
                        break;

                    case 2:
                        cout<<":";
                        break;
                }
            }

            //---------------------------------------------------------Show unit

            if(temp_checker[number]->getType()==4)
                cout<<"N";

            if(temp_checker[number]->getType()==5)
                cout<<"S";

            if(temp_checker[number]->getType()==6)
                cout<<"V";

        }
        cout<<"|"<<endl;//show end of line of map
    }


    for(int i=0; i<map->GetColcount(); i++)
        cout<<"_";
    cout<<"|"<<endl;
}



void Checker::Print_money(vector<Player*> _players){//show money of player

    for(unsigned int i=0; i<_players.size(); i++)
        cout<<"money of player"<<i<<" :"<<_players[i]->getMoney()<<"       "<<endl;
}
