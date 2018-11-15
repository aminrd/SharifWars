#include "map.h"
#include "iostream"
#include "block.h"
using namespace std;

Map::Map(int _rowcount, int _colcount){
    rowcount=_rowcount;
    colcount=_colcount;
    map=new Block*[rowcount];
    for(int i=0; i<rowcount; i++)
        map[i]=new Block[colcount];

    //--------------------------------------------------------set all block empty

    for(int i=0; i<rowcount; i++)
        for(int j=0; j<colcount; j++)
            map[i][j].setEmpty();
    //---------------------------------------------------------set row and col of all block

    for(int i=0; i<rowcount; i++)
        for(int j=0; j<colcount; j++)
            map[i][j].setPlace(i,j);

}

Block* Map::getBlock(int row,int col){
    if( 0<=row && row<rowcount && 0<=col && col<colcount )
        return &(map[row][col]);
    else
        return NULL;
}

Map::~Map(){
    for(int i=0; i<rowcount; i++)
        delete []map[i];
    delete []map;
}

int Map::GetRowcount(){
    return rowcount;
}

int Map::GetColcount(){
    return colcount;
}

void Map::Eqaul(Map* _map){
    for(int i=0; i<rowcount; i++)
        for(int j=0; j<colcount; j++){
            Block* temp=_map->getBlock(i,j);
            map[i][j]=(*temp);
        }
}

