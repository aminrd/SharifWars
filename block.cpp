#include "block.h"

Block::Block(){

}

vector <GameObject*> Block::getObjects(){
    vector <GameObject*> temp_objects;
    for(unsigned int i=0; i<objects.size(); i++){
        if(objects[i]!=NULL)
            temp_objects.push_back(objects[i]);
    }
    if(temp_objects.size()==0)
        temp_objects.push_back(NULL);
    return temp_objects;
}

int Block::getRow(){
    return row;
}

int Block::getCol(){
    return col;
}

void Block::addObject(GameObject* object){
    objects.push_back(object);
}

void Block::removeObject(GameObject *object){
    for(unsigned int i=0; i<objects.size(); i++)
        if(objects[i]==object)
            objects[i]=NULL;
}

bool Block::getEmpty() const{
    for(unsigned int i=0; i<objects.size(); i++)
        if(objects[i]!=NULL)
            return false;
    return true;
}

bool Block::Empty_Of_Building(){
    for(unsigned int i=0; i<objects.size(); i++)
        if(objects[i]!=NULL)
            if(objects[i]->getType()<4)
                return false;
    return true;
}

void Block::setPlace(int _row,int _col){
    row=_row;
    col=_col;
}

void Block::setEmpty(){
    objects.clear();
}
