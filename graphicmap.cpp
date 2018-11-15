#include "graphicmap.h"

#include <QPainter>
#include <gameobject.h>
#include <QHeaderView>
#include <QScrollBar>
#include "map.h"
#include "player.h"
#include "gameobject.h"

GraphicMap::GraphicMap(QTableWidget* _table, Map* _map, QWidget* parent){
    map=_map;
    maptable=_table;

}

void GraphicMap::paintEvent(QPaintEvent* event){
    QWidget::paintEvent(event);
    QPainter p(this);

    int width_block=this->width()/map->GetColcount();
    int height_block=this->height()/map->GetRowcount();
    int start_height=this->height()- (height_block*map->GetRowcount());
    start_height/=2;
    int start_width=this->width()- (width_block*map->GetColcount());
    start_width/=2;

    for(int i=0; i<map->GetRowcount(); i++)
        for(int j=0; j<map->GetColcount(); j++){


            int number=0;//number of game object in the block
            vector <GameObject*> temp_checker;
            temp_checker=map->getBlock(i,j)->getObjects();
            number=0;

            //-----------------------------------------------------------------show empty block
            if(map->getBlock(i,j)->getEmpty()==true) { //show empty block
                p.setBrush(QColor(20,80,20,220));
            }
            else{
                Player s;

                int id=temp_checker[number]->getPlayer()->getPlayerID();

                switch(id){

                    case -1:
                    p.setBrush(QColor(200,200,200,220));
                    break;

                    case 1:
                    p.setBrush(QColor(80,20,20,220));
                    break;

                    case 2:
                    p.setBrush(QColor(20,20,80,220));
                    break;

                    case 3:
                    p.setBrush(QColor(80,80,20,220));
                    break;

                    case 4:
                    p.setBrush(QColor(80,20,80,220));
                    break;

                    case 5:
                    p.setBrush(QColor(20,80,80,220));
                    break;
                }
            }

            p.setPen(Qt::NoPen);
            p.drawRect(j*width_block+start_width,i*height_block+start_height,width_block,height_block);

        }


    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::blue);
    p.drawRect(start_width+maptable->horizontalScrollBar()->value()*width_block , start_height+maptable->verticalScrollBar()->value()*height_block , width_block*47, height_block*18);

}
