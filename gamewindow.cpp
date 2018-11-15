#include "gamewindow.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <QApplication>
#include <QHeaderView>
#include <vector>
#include <QSignalMapper>
#include <QPalette>
#include <QRect>
#include <QString>
#include <QMouseEvent>
#include <QScrollBar>
#include <QSpacerItem>
#include <QCursor>
#include <QPushButton>
#include <phonon/MediaObject>
#include <QSound>
#include <phonon/AudioOutput>
#include "unitmaker.h"
#include "game.h"
#include "moneymaker.h"
#include "unit.h"
#include "zombie.h"
#include "superunit.h"
#include "map.h"
#include "block.h"
#include "player.h"
#include "building.h"
#include "graphicmap.h"
using namespace std;

GameWindow::GameWindow(Game* _game, vector<Player*> _players,QWidget* parent) :QDesktopWidget(){

    upgrade=false;
    sell=false;
    super_attack=false;
    targeting=false;
    moving=false;
    turning=1;
    game=_game;
    count_turn=1;
    players=_players;
    row=_game->getMap()->GetRowcount();
    col=_game->getMap()->GetColcount();
    UnitMakerBuilding=NULL;
    unit=NULL;
    QPushButton temp;
    qApp->installEventFilter(this);
    this->setMouseTracking(true);

    //----------------------------------play Music

    QSound music("music/2.wav");
    music.play();
    music.setLoops(100);

    //--------------------------------new Map Buttons
    MapButtons=new QPushButton*[row];
    for(int i=0; i<row; i++)
        MapButtons[i]=new QPushButton[col];

    //-------------------------------set background for map button
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++){
            QIcon icon("map/11.jpg");
            MapButtons[i][j].setIconSize(QSize(43,35));
            MapButtons[i][j].setIcon(icon);
        }

    this->setWindowFlags(Qt::FramelessWindowHint);
    QIcon icon("start/2.jpg");
    this->setWindowIcon(icon);


    int width=QApplication::desktop()->width();
    int height=QApplication::desktop()->height();

    //-----------------------------------------------table 1
    table=new QTableWidget(2,1,this);
    table->resize(width,height);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    table->setColumnWidth(0,table->width());
    table->setRowHeight(0, (0.7*table->height())-1);
    table->setRowHeight(1, (0.3*table->height())-1);


    //-----------------------------------------------table 2
    table2=new QTableWidget(1,3);

    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Base,*(new QBrush(*(new QPixmap("table2/3.jpg")))));
    table->setPalette(*palette);

    table2->resize(width, (0.3*table->height()));
    table->setCellWidget(1,0,table2);
    table2->verticalHeader()->hide();
    table2->horizontalHeader()->hide();
    table2->setColumnWidth(0,(0.3205*table2->width()));
    table2->setColumnWidth(1,(0.43*table2->width()));
    table2->setColumnWidth(2,(0.248*table2->width())+1);
    table2->setRowHeight(0, table2->height());

    //------------------------------------------------Map Table
    MapTable=new QTableWidget(row,col);
    MapTable->setShowGrid(false);
    table->setCellWidget(0,0,MapTable);
    MapTable->verticalHeader()->hide();
    MapTable->horizontalHeader()->hide();
    MapTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    MapTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++){
            MapButtons[i][j].resize(30,30);
            MapTable->setCellWidget(i,j,&MapButtons[i][j]);
            MapTable->setColumnWidth(j,30);
            MapTable->setRowHeight(i,30);
        }

    //-------------------------------------------------Building Buttons
    Base_Building=new QPushButton("Base");
    Base_Building->setCheckable(true);
    MoneyMaker_Building=new QPushButton("Money");
    MoneyMaker_Building->setCheckable(true);
    Defence_Building=new QPushButton("Defence");
    Defence_Building->setCheckable(true);
    NormalMaker_Building=new QPushButton("Normal");
    NormalMaker_Building->setCheckable(true);
    SuperMaker_Building=new QPushButton("SuperUnit");
    SuperMaker_Building->setCheckable(true);
    VehicleMaker_Building=new QPushButton("Vehicle");
    VehicleMaker_Building->setCheckable(true);
    EndTurn=new QPushButton();
    QuitButton=new QPushButton();

    for(int i=0; i<10; i++)
        Button[i]=new QPushButton;

    //------------------------------------------------Informaition Label and Table
    Information=new QTableWidget(3,5);
    Information->setRowHeight(0,25);
    Information->setSpan(0,0,1,5);
    Information->setRowHeight(1,table2->height()/4-15);
    Information->setRowHeight(2,table2->height()/4-15);
    Information->setColumnWidth(0,(0.2*0.42*table2->width()));
    Information->setColumnWidth(1,(0.2*0.43*table2->width()));
    Information->setColumnWidth(2,(0.2*0.43*table2->width()));
    Information->setColumnWidth(3,(0.2*0.43*table2->width()));
    Information->setColumnWidth(4,(0.2*0.43*table2->width())-1);
    Information->verticalHeader()->hide();
    Information->horizontalHeader()->hide();
    name=new QLabel();
    Information->setCellWidget(0,0,name);
    name->setAlignment(Qt::AlignCenter);
    QPalette pal;
    pal.setColor( QPalette::Text, QColor(250,250,170) );
    name->setPalette(pal);
    for(int i=0; i<10; i++){
        Information_label[i]=new QLabel;
        Information_label[i]->setAlignment(Qt::AlignCenter);
        QPalette pal;
        pal.setColor( QPalette::Text, QColor(250,250,170) );
        Information_label[i]->setPalette(pal);
        Information->setCellWidget(1+i/5,i%5,Information_label[i]);

    }

    //-------------------------------------------------Building Table
    BuildingTable=new QTableWidget(2,6);
    BuildingTable->setRowHeight(0,table2->height()/2-2);
    BuildingTable->setRowHeight(1,table2->height()/2-1);
    BuildingTable->setSpan(1,0,1,6);
    BuildingTable->setColumnWidth(0,(0.17*0.43*table2->width()));
    BuildingTable->setColumnWidth(1,(0.17*0.43*table2->width()));
    BuildingTable->setColumnWidth(2,(0.17*0.43*table2->width()));
    BuildingTable->setColumnWidth(3,(0.17*0.43*table2->width()));
    BuildingTable->setColumnWidth(4,(0.16*0.43*table2->width())+1);
    BuildingTable->setColumnWidth(5,(0.16*0.43*table2->width())+1);
    table2->setCellWidget(0,1,BuildingTable);
    BuildingTable->verticalHeader()->hide();
    BuildingTable->horizontalHeader()->hide();

    BuildingTable->setCellWidget(0,0,Base_Building);
    BuildingTable->setCellWidget(0,1,Defence_Building);
    BuildingTable->setCellWidget(0,2,MoneyMaker_Building);
    BuildingTable->setCellWidget(0,3,NormalMaker_Building);
    BuildingTable->setCellWidget(0,4,SuperMaker_Building);
    BuildingTable->setCellWidget(0,5,VehicleMaker_Building);
    BuildingTable->setCellWidget(1,0,Information);


    //------------------------------------------------Player Table
    char TempString[100];
    sprintf(TempString,"Player %d",turning);
    PlayerTurn=new QLabel(TempString);
    PlayerTurn->setAlignment(Qt::AlignCenter);
    sprintf(TempString,"Money = %d",players[turning]->getMoney());
    PlayerMoney=new QLabel(TempString);
    PlayerMoney->setAlignment(Qt::AlignCenter);
    sprintf(TempString,"Turn %d",count_turn);
    turn_count=new QLabel(TempString);
    turn_count->setAlignment(Qt::AlignCenter);
    player_label=new QPushButton;
    QPalette pal2;
    pal2.setColor( QPalette::Text, QColor(250,250,170) );
    PlayerTurn->setPalette(pal2);
    PlayerMoney->setPalette(pal2);
    turn_count->setPalette(pal2);

    GameMap=new GraphicMap(MapTable,game->getInstance()->getMap());
    GameMap->resize(0.223*table2->width(),0.94*table2->height());

    PlayerTable=new QTableWidget(4,2);
    PlayerTable->setColumnWidth(0,0.224*table2->width());
    PlayerTable->setColumnWidth(1,0.095*table2->width());
    PlayerTable->setSpan(0,0,4,1);
    PlayerTable->setRowHeight(0,0.6*table2->height());
    PlayerTable->setRowHeight(1,0.13*table2->height());
    PlayerTable->setRowHeight(2,0.13*table2->height()+1);
    PlayerTable->setRowHeight(3,0.13*table2->height()+1);
    table2->setCellWidget(0,0,PlayerTable);
    PlayerTable->verticalHeader()->hide();
    PlayerTable->horizontalHeader()->hide();

    PlayerTable->setCellWidget(0,0,GameMap);
    PlayerTable->setCellWidget(0,1,player_label);
    PlayerTable->setCellWidget(1,1,PlayerTurn);
    PlayerTable->setCellWidget(2,1,PlayerMoney);
    PlayerTable->setCellWidget(3,1,turn_count);

    player_label->setIconSize(QSize(0.1*table2->width(),0.6*table2->height()));
    player_label->setIcon(QIcon("player/arm/p2.jpg"));

    //-------------------------------------------------Object Table
    ObjectTable=new QTableWidget(3,4);
    for(int i=0; i<3; i++)
        ObjectTable->setRowHeight(i,0.33*table2->height());
    for(int i=0; i<4; i++)
        ObjectTable->setColumnWidth(i,(0.25*0.248*table2->width()));

    ObjectTable->verticalHeader()->hide();
    ObjectTable->horizontalHeader()->hide();
    ObjectTable->setShowGrid(false);

    table2->setCellWidget(0,2,ObjectTable);

    for(int i=0; i<10; i++)
        ObjectTable->setCellWidget(i/4,i%4,Button[i]);

    ObjectTable->setCellWidget(2,3,EndTurn);
    ObjectTable->setCellWidget(2,2,QuitButton);

    //-------------------------------set background for object table button
    QIcon icon2("object/object.jpg");
    for(int i=0; i<10; i++){
        Button[i]->setIconSize(QSize(0.25*0.25*table2->width(),0.36*table2->height()));
        Button[i]->setIcon(icon2);
    }
    EndTurn->setIconSize(QSize(0.25*0.25*table2->width() ,0.34*table2->height()));
    EndTurn->setIcon(QIcon("object/endturn.jpg"));


    QuitButton->setIconSize(QSize(0.25*0.25*table2->width(),0.34*table2->height()));
    QuitButton->setIcon(QIcon("object/Quit.jpg"));


    //-------------------------------------------------Common unit
    common_layout=new QHBoxLayout(this);
    for(int i=0; i<10; i++){
        common_unit[i]=new QPushButton;
        common_unit[i]->resize(40,40);
        common_layout->addWidget(common_unit[i]);
    }
    common_layout->addSpacerItem(new QSpacerItem(100,200, QSizePolicy::Expanding, QSizePolicy::Maximum));
    for(int i=0; i<10; i++)
        common_unit[i]->hide();

    //----------------------------------------------------event label

    events=new QLabel(this);
    events->move( 140,0.645*table->height());
    events->resize(300,20);
    events->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    QFont f( "Arial", 12, QFont::Bold);
    events->setFont(f);
    events->hide();

    //-------------------------------------------------Mapping Signal
    connect(QuitButton,SIGNAL(clicked()),this,SLOT(QuitGame()));
    connect(EndTurn,SIGNAL(clicked()),this,SLOT(NextTurn()));
    connect(Button[0],SIGNAL(clicked()),this,SLOT(CreateUnit()));
    connect(Button[1],SIGNAL(clicked()),this,SLOT(Move()));
    connect(Button[2],SIGNAL(clicked()),this,SLOT(Unload()));
    connect(Button[3],SIGNAL(clicked()),this,SLOT(SetTarget()));
    connect(Button[4],SIGNAL(clicked()),this,SLOT(Selling()));

    //------------------------------------------------------------map Buttons
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(CreateBuilding(int)));

    for(int i=0; i<row; i++)
       for (int j=0; j<col; j++) {
           signalMapper->setMapping(&MapButtons[i][j], i+row*j);
           connect(&MapButtons[i][j], SIGNAL(clicked()), signalMapper, SLOT(map()));
       }

    //------------------------------------------------------------common buttons
    QSignalMapper *signalMapper2 = new QSignalMapper(this);
    connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(setUnits(int)));

    for(int i=0; i<10; i++){
        signalMapper2->setMapping(common_unit[i],i);
        connect(common_unit[i], SIGNAL(clicked()), signalMapper2, SLOT(map()));
    }

    //------------------------------------------------------------checkable buttons
    connect(Base_Building,SIGNAL(clicked()),this,SLOT(ShowMyArea()));
    connect(Defence_Building,SIGNAL(clicked()),this,SLOT(ShowMyArea()));
    connect(MoneyMaker_Building,SIGNAL(clicked()),this,SLOT(ShowMyArea()));
    connect(NormalMaker_Building,SIGNAL(clicked()),this,SLOT(ShowMyArea()));
    connect(SuperMaker_Building,SIGNAL(clicked()),this,SLOT(ShowMyArea()));
    connect(VehicleMaker_Building,SIGNAL(clicked()),this,SLOT(ShowMyArea()));

}


void GameWindow::Selling(){
    if(Button[4]->toolTip()=="Sell"){
        UnitMakerBuilding->sell();
    }
}


void GameWindow::CreateUnit(){
    if(Button[0]->toolTip()=="Create Unit")
       game->constructUnit(players[turning],UnitMakerBuilding,events);
}

void GameWindow::Unload(){
    if(Button[2]->toolTip()=="Unload")
        game_object->unload();
    if(Button[2]->toolTip()=="Special Attack")
        super_attack=true;
}

void GameWindow::UnActive(){
    for(int i=0; i<6; i++){
        Button[i]->setToolTip("");
        Button[i]->setIcon(QIcon("object/object.jpg"));
    }
    UnitMakerBuilding=NULL;
    unit=NULL;
    sell=false;
    upgrade=false;
    moving=false;
    targeting=false;
    super_attack=false;
    game_objects.clear();
    this->SetInformation(NULL);
    for(int i=0; i<10; i++)
        common_unit[i]->hide();
}

void GameWindow::CreateBuilding(int place){

    events->hide();
    char TempString[100];
    int r=place%row;
    int c=place/row;

    //--------------------------------------------------------------------------setTarget
    if(targeting==true){
        vector<GameObject*> objects;
        objects=game->getMap()->getBlock(r,c)->getObjects();
        game_object->setTargetObject(objects[0]);
        targeting=false;
        GameMap->update();
        this->UnActive();
        return;
    }

    //--------------------------------------------------------------------------move Unit
    if(moving==true){
        unit->moveToBlock(r,c);
        moving=false;
        GameMap->update();
        this->UnActive();
        return;
    }

    //--------------------------------------------------------------------------Special Attack
    if(super_attack==true){
        vector<GameObject*> objects;
        objects=game->getMap()->getBlock(r,c)->getObjects();
        SuperUnit* temp_super=dynamic_cast<SuperUnit*>(unit);
        temp_super->specialAttack(objects[0]);
        super_attack=false;
        GameMap->update();
        this->UnActive();
        return;
    }

    //--------------------------------------------------------------------------Create Building

    //-------------------------------------------------------------
    if(Base_Building->isChecked()==true){
       if(game->constructBuilding(players[turning],0,r,c,events)==true){
           for(int i=r; i<r+3; i++)
               for(int j=c; j<c+4; j++){
                   MapButtons[i][j].setIcon(QIcon("player/building/base.jpg"));
                   //MapButtons[i][j].setAutoFillBackground( true );
                   //MapButtons[i][j].setStyleSheet("QPushButton{background-color:green}");
               }
           sprintf(TempString,"Money = %d",players[turning]->getMoney());
           PlayerMoney->setText(TempString);
           GameMap->update();
           this->UnActive();
           return;
       }
    }

    //-------------------------------------------------------------
    if(Defence_Building->isChecked()==true){
       if(game->constructBuilding(players[turning],1,r,c,events)==true){
           for(int i=r; i<r+2; i++)
               for(int j=c; j<c+2; j++){
                   MapButtons[i][j].setIcon(QIcon("player/building/defence.jpg"));
                   //MapButtons[i][j].setAutoFillBackground( true );
                   //MapButtons[i][j].setStyleSheet("QPushButton{background-color:red}");
               }
           sprintf(TempString,"Money = %d",players[turning]->getMoney());
           PlayerMoney->setText(TempString);
           GameMap->update();
           this->UnActive();
           return;
       }
    }

    //-------------------------------------------------------------
    if(MoneyMaker_Building->isChecked()==true){
       if(game->constructBuilding(players[turning],2,r,c,events)==true){
           for(int i=r; i<r+3; i++)
               for(int j=c; j<c+4; j++){
                   MapButtons[i][j].setIcon(QIcon("player/building/moneymaker.jpg"));
                   //MapButtons[i][j].setAutoFillBackground( true );
                   //MapButtons[i][j].setStyleSheet("QPushButton{background-color:blue}");
               }
           sprintf(TempString,"Money = %d",players[turning]->getMoney());
           PlayerMoney->setText(TempString);
           GameMap->update();
           this->UnActive();
           return;
       }
    }

    //-------------------------------------------------------------
    if(NormalMaker_Building->isChecked()==true){
       if(game->constructBuilding(players[turning],3,r,c,events)==true){
           for(int i=r; i<r+3; i++)
               for(int j=c; j<c+4; j++){
                   MapButtons[i][j].setIcon(QIcon("player/building/normalmaker.jpg"));
                   //MapButtons[i][j].setAutoFillBackground( true );
                   //MapButtons[i][j].setStyleSheet("QPushButton{background-color:yellow}");
               }
           sprintf(TempString,"Money = %d",players[turning]->getMoney());
           PlayerMoney->setText(TempString);
           GameMap->update();
           this->UnActive();
           return;
       }
    }

    //-------------------------------------------------------------
    if(SuperMaker_Building->isChecked()==true){
        if(game->constructBuilding(players[turning],4,r,c,events)==true){
            for(int i=r; i<r+3; i++)
                for(int j=c; j<c+4; j++){
                    MapButtons[i][j].setIcon(QIcon("player/building/supermaker.jpg"));
                    //MapButtons[i][j].setAutoFillBackground( true );
                    //MapButtons[i][j].setStyleSheet("QPushButton{background-color:brown}");
                }
            sprintf(TempString,"Money = %d",players[turning]->getMoney());
            PlayerMoney->setText(TempString);
            GameMap->update();
            this->UnActive();
            return;
        }
    }

    //------------------------------------------------------------
    if(VehicleMaker_Building->isChecked()==true){
        if(game->constructBuilding(players[turning],5,r,c,events)==true){
            for(int i=r; i<r+3; i++)
                for(int j=c; j<c+4; j++){
                    MapButtons[i][j].setIcon(QIcon("player/building/vehiclemaker.jpg"));
                    //MapButtons[i][j].setAutoFillBackground( true );
                    //MapButtons[i][j].setStyleSheet("QPushButton{background-color:purple}");
                }
            sprintf(TempString,"Money = %d",players[turning]->getMoney());
            PlayerMoney->setText(TempString);
            GameMap->update();
            this->UnActive();
            return;
        }
    }

    //--------------------------------------------------------------------------Change Object Table
    int number=0;//number of game object in the block
    vector <GameObject*> temp_checker;
    temp_checker=game->getMap()->getBlock(r,c)->getObjects();

    for(unsigned int k=0; k<temp_checker.size(); k++)
        if(temp_checker[k]!=NULL)
            number=k;
    number=0;
    game_object=temp_checker[number];

    if(temp_checker.size()>1){
        for(int i=0; i<temp_checker.size(); i++)
            common_unit[i]->show();
        for(int i=0; i<temp_checker.size(); i++)
            game_objects.push_back(temp_checker[i]);
        GameMap->update();
        return;
    }

    //-------------------------------------------------------------------------one object
    this->setUnit(game_object);
}


void GameWindow::setUnits(int numberButton){
    for(int i=0; i<10; i++)
        common_unit[i]->hide();
    this->setUnit(game_objects[numberButton]);
}


void GameWindow::setUnit(GameObject* game_object){

    if(game_object==NULL){
        this->UnActive();
        return;
    }

    if(game_object->getType()==3){
        this->UnActive();
        if(players[turning]==game_object->getPlayer()){
            Button[0]->setToolTip("Create Unit");
            Button[0]->setIcon(QIcon("object/unit.jpg"));
            Button[3]->setToolTip("Set Target");
            Button[3]->setIcon(QIcon("object/settarget.jpg"));
            Button[1]->setToolTip("Upgrade");
            Button[1]->setIcon(QIcon("object/upgrade.jpg"));
            Button[4]->setToolTip("Sell");
            Button[4]->setIcon(QIcon("object/sell.jpg"));
        }
        UnitMakerBuilding = dynamic_cast <Building*> (game_object);
        this->SetInformation(UnitMakerBuilding);
        return;
    }

    if(game_object->getType()==1){
        this->UnActive();
        if(players[turning]==game_object->getPlayer()){
            Button[1]->setToolTip("Upgrade");
            Button[1]->setIcon(QIcon("object/upgrade.jpg"));
            Button[3]->setToolTip("Set Target");
            Button[3]->setIcon(QIcon("object/settarget.jpg"));
            Button[2]->setToolTip("Unload");
            Button[2]->setIcon(QIcon("object/unload.jpg"));
            Button[4]->setToolTip("Sell");
            Button[4]->setIcon(QIcon("object/sell.jpg"));
        }
        UnitMakerBuilding=dynamic_cast<Building*>(game_object);
        this->SetInformation(game_object);
        return;
    }

    if(game_object->getType()==6){
        this->UnActive();
        if(players[turning]==game_object->getPlayer()){
            Button[1]->setToolTip("Move");
            Button[1]->setIcon(QIcon("object/move.jpg"));
            Button[2]->setToolTip("Unload");
            Button[2]->setIcon(QIcon("object/unload.jpg"));
            Button[3]->setToolTip("Set Target");
            Button[3]->setIcon(QIcon("object/settarget.jpg"));
        }
        unit=dynamic_cast<Unit*>(game_object);
        this->SetInformation(game_object);
        return;
    }

    if(game_object->getType()>3){
        this->UnActive();
        if(players[turning]==game_object->getPlayer()){
            Button[1]->setToolTip("Move");
            Button[1]->setIcon(QIcon("object/move.jpg"));
            Button[3]->setToolTip("Set Target");
            Button[3]->setIcon(QIcon("object/settarget.jpg"));
            if(game_object->getType()==5){
                Button[2]->setToolTip("Special Attack");
                Button[2]->setIcon(QIcon("object/specialattack.jpg"));
            }
        }
        unit= dynamic_cast<Unit*> (game_object);
        this->SetInformation(unit);
        return;
    }

    if(game_object->getType()<3){
        this->UnActive();
        if(players[turning]==game_object->getPlayer()){
            Button[3]->setToolTip("Set Target");
            Button[3]->setIcon(QIcon("object/settarget.jpg"));
            Button[1]->setToolTip("Upgrade");
            Button[1]->setIcon(QIcon("object/upgrade.jpg"));
            if(game_object->getType()!=0){
                Button[4]->setToolTip("Sell");
                Button[4]->setIcon(QIcon("object/sell.jpg"));
            }
        }
        this->SetInformation(game_object);
        UnitMakerBuilding=dynamic_cast<Building*> (game_object);
        return;
    }
}


void GameWindow::QuitGame(){
    exit(0);
}

void GameWindow::SetTarget(){
    if(Button[3]->toolTip()=="Set Target")
        targeting=true;
}

void GameWindow::Move(){
    if(Button[1]->toolTip()=="Upgrade")
        UnitMakerBuilding->upgrade();

    if(Button[1]->toolTip()=="Move")
        moving=true;
}

GameObject* GameWindow::SetInformation(GameObject* object){

    if(object==NULL){
        name->setText("");
        for(int i=0; i<10; i++)
            Information_label[i]->setText("");
        return object;
    }

    events->hide();
    this->SetCheckFalse();
    name->setText(object->getName());
    char temp_string[100];
    sprintf(temp_string,"Health: %d/%d",object->getHealth(),object->getMaxHealth());
    Information_label[0]->setText(temp_string);
    sprintf(temp_string,"Damage: %d",object->getAttackDamage());
    Information_label[1]->setText(temp_string);
    sprintf(temp_string,"Delay: %d",object->getAttackDelay());
    Information_label[2]->setText(temp_string);
    sprintf(temp_string,"Range: %d",object->getAttackRange());
    Information_label[3]->setText(temp_string);
    sprintf(temp_string,"Player: %d",object->getPlayer()->getPlayerID());
    Information_label[4]->setText(temp_string);
    sprintf(temp_string,"level: %d",object->getLevel());
    Information_label[5]->setText(temp_string);

    if( 3<object->getType() && object->getType()<7){
        sprintf(temp_string,"speed: %d" ,object->getSpeed());
        Information_label[6]->setText(temp_string);
        if(object->getType()==5){
            SuperUnit* temp_unit=dynamic_cast<SuperUnit*> (object);
            sprintf(temp_string,"mana: %d/%d",temp_unit->getMana(),temp_unit->getMaxMana());
            Information_label[7]->setText(temp_string);
            sprintf(temp_string,"Special: %d",temp_unit->getSpecialAttackDamage());
            Information_label[8]->setText(temp_string);
        }
    }

    if(object->getType()==2){
        MoneyMaker* temp=dynamic_cast<MoneyMaker*> (object);
        sprintf(temp_string,"Income: %d",temp->getIncome());
        Information_label[6]->setText(temp_string);
    }

    if(object->getType()==3){
        UnitMaker* temp=dynamic_cast<UnitMaker*> (object);
        sprintf(temp_string,"UnitTraining: %d",temp->queueCount());
        Information_label[6]->setText(temp_string);
        sprintf(temp_string,"TrainProg: %.2lf",temp->getConstructionProgress());
        Information_label[7]->setText(temp_string);
    }

    if(object->getType()==1 || object->getType()==6){
        sprintf(temp_string,"units: %d",object->getCapacity());
        Information_label[9]->setText(temp_string);
    }

    return object;
}


void GameWindow::NextTurn(){
    this->SetCheckFalse();
    events->hide();
    this->ShowArea(turning,true);

    turning++;
    if(turning>=players.size()){

        //-------------------------------------create zombie
        int zombie_spawn=Zombie::zombie_spawn_period;
        if(count_turn%zombie_spawn==0)
            for(int j=0; j<Zombie::zombie_spawn_count; j++)
                game->constructZombie(players[0]);
        turning=1;
        count_turn++;
        Update();
        char temp_str[100];
        sprintf(temp_str,"Turn %d",count_turn);
        turn_count->setText(temp_str);

    }
    //------------------------------------change icon
    char temp_string[100];
    sprintf(temp_string,"player/arm/p%d.jpg",turning+1);
    player_label->setIcon(QIcon(temp_string));

    //-------------------------------------change text label
    sprintf(temp_string,"Player %d",turning);
    PlayerTurn->setText(temp_string);
    sprintf(temp_string,"Money = %d",players[turning]->getMoney());
    PlayerMoney->setText(temp_string);
    this->UnActive();
    this->SetInformation(NULL);
    vector <Player*> temp=game->getPlayers();

    if(temp[turning]==NULL)
        this->NextTurn();

}


void GameWindow::Update(){

    Map temp_map(row,col);
    temp_map.Eqaul(game->getInstance()->getMap());
    game->advanceGame();

    GameMap->update();
    vector <GameObject*>t1;
    vector <GameObject*>t2;

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++){

            t1=temp_map.getBlock(i,j)->getObjects();
            t2=game->getMap()->getBlock(i,j)->getObjects();
            bool flag=false;

            if(t1.size() == t2.size()){
               for(int k=0; k<t1.size(); k++)
                  if(t1[k]!= t2[k])
                      flag=true;
            }
            else
                flag=true;
            //------------------------------show zombie

            if(t1[0]!=NULL)
                if(t1[0]->getType()>3)
                    flag=true;
            //-----------------------------


            if(flag==false)
                continue;

            int number=0;//number of game object in the block
            vector <GameObject*> temp_checker;
            temp_checker=game->getMap()->getBlock(i,j)->getObjects();
            number=0;

            //-----------------------------------------------------------------show empty block
            if(game->getMap()->getBlock(i,j)->getEmpty()==true) { //show empty block
                    MapButtons[i][j].setIcon(QIcon("map/11.jpg"));
                continue;
            }

            //---------------------------------------------------------Show unit

            if(temp_checker[number]->getType()==4)
                MapButtons[i][j].setIcon(QIcon("player/unit/normal.jpg"));

            if(temp_checker[number]->getType()==5)
                MapButtons[i][j].setIcon(QIcon("player/unit/super.jpg"));

            if(temp_checker[number]->getType()==6)
                MapButtons[i][j].setIcon(QIcon("player/unit/vehicle.jpg"));

            if(temp_checker[number]->getType()==7)
                MapButtons[i][j].setIcon(QIcon("player/unit/zombie.jpg"));

        }

}

void GameWindow::SetCheckFalse(){

    if(Base_Building->isChecked()==true)
        this->ShowArea(turning,false);
    if(Defence_Building->isChecked()==true)
        this->ShowArea(turning,true);
    if(MoneyMaker_Building->isChecked()==true)
        this->ShowArea(turning,true);
    if(NormalMaker_Building->isChecked()==true)
        this->ShowArea(turning,true);
    if(SuperMaker_Building->isChecked()==true)
        this->ShowArea(turning,true);
    if(VehicleMaker_Building->isChecked()==true)
        this->ShowArea(turning,true);

    Base_Building->setChecked(false);
    Defence_Building->setChecked(false);
    MoneyMaker_Building->setChecked(false);
    NormalMaker_Building->setChecked(false);
    SuperMaker_Building->setChecked(false);
    VehicleMaker_Building->setChecked(false);
}

void GameWindow::ShowArea(int _turning, bool remove){
/*
    vector <class Block*> blocks=players[turning]->getPlayerArea();
    if(remove==false)
        for(unsigned int i=0; i<blocks.size(); i++)
            if(blocks[i]->getEmpty())
                MapButtons[blocks[i]->getRow()][blocks[i]->getCol()].setIcon(QIcon("map/10.jpg"));
    if(remove==true)
        for(unsigned int i=0; i<blocks.size(); i++)
            if(blocks[i]->getEmpty())
                MapButtons[blocks[i]->getRow()][blocks[i]->getCol()].setIcon(QIcon("map/11.jpg"));
*/
}

void GameWindow::ShowMyArea(){

    if(Base_Building->isChecked()==true){
        this->ShowArea(turning,false);
        return;
    }
    if(Defence_Building->isChecked()==true){
        this->ShowArea(turning,false);
        return;
    }
    if(MoneyMaker_Building->isChecked()==true){
        this->ShowArea(turning,false);
        return;
    }
    if(NormalMaker_Building->isChecked()==true){
        this->ShowArea(turning,false);
        return;
    }
    if(SuperMaker_Building->isChecked()==true){
        this->ShowArea(turning,false);
        return;
    }
    if(VehicleMaker_Building->isChecked()==true){
        this->ShowArea(turning,false);
        return;
    }
    this->ShowArea(turning,true);
}


void GameWindow::LeftMap(){
    QScrollBar* temp=MapTable->horizontalScrollBar();
    temp->setValue(temp->value()-1);
}

void GameWindow::RightMap(){
    QScrollBar* temp=MapTable->horizontalScrollBar();
    temp->setValue(temp->value()+1);
}

void GameWindow::UpMap(){
    QScrollBar* temp=MapTable->verticalScrollBar();
    temp->setValue(temp->value()-1);
}

void GameWindow::DownMap(){
    QScrollBar* temp=MapTable->verticalScrollBar();
    temp->setValue(temp->value()+1);
}

GameWindow::~GameWindow(){

}


