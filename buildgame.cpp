#include "buildgame.h"
#include <QSound>
#include <QFont>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <QSpacerItem>
#include <QApplication>
#include <QHeaderView>
#include <QIcon>
#include "xmlreader.h"
#include "gamewindow.h"
using namespace std;

BuildGame::BuildGame(Game* game, QWidget* parent): QDesktopWidget() {

    MyGame=game;
    players_game.clear();
    game_players.clear();
    //------------------------------------play music
    music=new QSound("music/1.wav");
    music->play();
    music->setLoops(100);

    int width=QApplication::desktop()->width();
    int height=QApplication::desktop()->height();
    //------------------------------------set flag
    this->setWindowFlags(Qt::FramelessWindowHint);
    QIcon icon("start/2.jpg");
    this->setWindowIcon(icon);

    //------------------------------------table
    table=new QTableWidget(11,7,this);

    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Base,*(new QBrush(*(new QPixmap("map/5.jpg")))));
    table->setPalette(*palette);
    table->resize(width,height*0.94);

    table->setColumnWidth(0,table->width()*0.30);
    table->setColumnWidth(1,table->width()*0.08);
    table->setColumnWidth(2,table->width()*0.12);
    table->setColumnWidth(3,table->width()*0.12);
    table->setColumnWidth(4,table->width()*0.12);
    table->setColumnWidth(5,table->width()*0.12);
    table->setColumnWidth(6,table->width()*0.14);


    table->setRowHeight(0,0.2*table->height());
    for(int i=1; i<11; i++)
        table->setRowHeight(i,0.73*height/10);

    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();

    //------------------------------------money and map
    table->setSpan(0,0,1,3);
    table->setSpan(0,3,1,4);

    QVBoxLayout* Vlay=new QVBoxLayout;
    QHBoxLayout* Hlay=new QHBoxLayout;

    QLabel* label_map=new QLabel("Map");
    label_map->setAlignment(Qt::AlignCenter);

    QLabel* labelRow=new QLabel("    Row count");
    labelRow->setAlignment(Qt::AlignCenter);

    QLabel* labelCol=new QLabel("    Col count");
    labelCol->setAlignment(Qt::AlignCenter);

    map_frame=new QFrame;
    map_frame->setLayout(Vlay);

    map_colcount=new QSpinBox(map_frame);
    map_colcount->setRange(1,1000);
    map_colcount->resize(40,30);
    map_colcount->setValue(60);

    map_rowcount=new QSpinBox(map_frame);
    map_rowcount->setRange(1,1000);
    map_rowcount->resize(40,30);
    map_rowcount->setValue(60);

    Vlay->addWidget(label_map);
    Vlay->addLayout(Hlay);
    Hlay->addSpacerItem(new QSpacerItem(50,200, QSizePolicy::Fixed, QSizePolicy::Maximum));
    Hlay->addWidget(labelRow);
    Hlay->addWidget(map_rowcount);
    Hlay->addSpacerItem(new QSpacerItem(50,200, QSizePolicy::Fixed, QSizePolicy::Maximum));
    Hlay->addWidget(labelCol);
    Hlay->addWidget(map_colcount);
    Hlay->addSpacerItem(new QSpacerItem(60,200, QSizePolicy::Fixed, QSizePolicy::Maximum));
    Vlay->addSpacerItem(new QSpacerItem(40,30, QSizePolicy::Maximum, QSizePolicy::Fixed));
    table->setCellWidget(0,0,map_frame);


    //------------------------------------money

    QFrame* money_frame=new QFrame;
    QVBoxLayout* v_lay=new QVBoxLayout;
    QHBoxLayout* h_lay=new QHBoxLayout;

    QLabel* money_label=new QLabel("Money");
    money_label->setAlignment(Qt::AlignCenter);
    QLabel* money=new QLabel("Set first money");
    money->setAlignment(Qt::AlignCenter);

    money_spin=new QSpinBox;
    money_spin->setRange(0,100000);
    money_spin->setValue(10000);
    money_spin->setAlignment(Qt::AlignCenter);

    money_frame->setLayout(v_lay);
    v_lay->addWidget(money_label);
    h_lay->addSpacerItem(new QSpacerItem(140,200, QSizePolicy::Fixed, QSizePolicy::Maximum));
    h_lay->addWidget(money);
    h_lay->addSpacerItem(new QSpacerItem(50,200, QSizePolicy::Fixed, QSizePolicy::Maximum));
    h_lay->addWidget(money_spin);
    h_lay->addSpacerItem(new QSpacerItem(100,200, QSizePolicy::Fixed, QSizePolicy::Maximum));
    v_lay->addLayout(h_lay);
    v_lay->addSpacerItem(new QSpacerItem(30,30, QSizePolicy::Maximum, QSizePolicy::Fixed));

    table->setCellWidget(0,3,money_frame);


    //-----------------------------------select player

    //------------------------------------------------new label and set in table
    Lplayer_name=new QLabel("Player name");
    Lplayer_name->setAlignment(Qt::AlignCenter);
    table->setCellWidget(2,0,Lplayer_name);

    Lplayer_team=new QLabel("team");
    Lplayer_team->setAlignment(Qt::AlignCenter);
    table->setCellWidget(2,1,Lplayer_team);

    Lplayer_x=new QLabel("start row");
    Lplayer_x->setAlignment(Qt::AlignCenter);
    table->setCellWidget(2,2,Lplayer_x);

    Lplayer_y=new QLabel("start col");
    Lplayer_y->setAlignment(Qt::AlignCenter);
    table->setCellWidget(2,3,Lplayer_y);

    Lplayer_rowcount=new QLabel("row count");
    Lplayer_rowcount->setAlignment(Qt::AlignCenter);
    table->setCellWidget(2,4,Lplayer_rowcount);

    Lplayer_colcount=new QLabel("colcount");
    Lplayer_colcount->setAlignment(Qt::AlignCenter);
    table->setCellWidget(2,5,Lplayer_colcount);

    char str[100];

    for(int i=2; i<10; i++){

        //-----------------------------------------------name line edit
        sprintf(str,"player %d",i-1);
        player_name[i]=new QLineEdit(str);
        table->setCellWidget(i+1,0,player_name[i]);

        //-----------------------------------------------team comboBox
        int team_count=2;
        player_team[i]=new QComboBox;
        for(int j=0; j<team_count; j++){
            sprintf(str,"team %d",j+1);
            player_team[i]->addItem(str);
        }
        table->setCellWidget(i+1,1,player_team[i]);

        //-----------------------------------------------strat x
        sprintf(str,"%d",0);
        player_x[i]=new QLineEdit(str);
        table->setCellWidget(i+1,2,player_x[i]);

        //-----------------------------------------------start y
        sprintf(str,"%d",(i-2)*30);
        player_y[i]=new QLineEdit(str);
        table->setCellWidget(i+1,3,player_y[i]);

        //-----------------------------------------------row count
        sprintf(str,"%d",30);
        player_rowcount[i]=new QLineEdit(str);
        table->setCellWidget(i+1,4,player_rowcount[i]);

        //-----------------------------------------------col count
        sprintf(str,"%d",30);
        player_colcount[i]=new QLineEdit(str);
        table->setCellWidget(i+1,5,player_colcount[i]);

    }

    //-------------------------------------------------row = 0

    Lplayer_count=new QLabel("Count of Player");
    player_count=new QComboBox;
    for(int i=0; i<9; i++){
        sprintf(str,"%d",i);
        player_count->addItem(str);
    }

    Lplayer_count->setAlignment(Qt::AlignCenter);
    table->setCellWidget(1,0,Lplayer_count);
    table->setCellWidget(1,1,player_count);

    //-----------------------------------start and quit
    QTableWidget* tableButton=new QTableWidget(1,9,this);
    palette->setBrush(QPalette::Base,*(new QBrush(*(new QPixmap("map/5.jpg")))));
    tableButton->setPalette(*palette);

    tableButton->resize(width,height*0.059);
    tableButton->horizontalHeader()->hide();
    tableButton->verticalHeader()->hide();
    tableButton->move(0,height*0.94);
    tableButton->setShowGrid(false);
    tableButton->setRowHeight(0,height*0.057);
    for(int i=0; i<6; i++)
        tableButton->setColumnWidth(i,table->width()/9);

    start=new QPushButton("Start");
    quit=new QPushButton("Quit");
    tableButton->setCellWidget(0,3,start);
    tableButton->setCellWidget(0,5,quit);

    for(int i=3; i<11; i++)
        table->hideRow(i);

    //---------------------------------------------------change font all label
    QFont f("Arial", 12, QFont::Bold);

    Lplayer_count->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    Lplayer_count->setFont(f);
    Lplayer_name->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    Lplayer_team->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    Lplayer_x->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    Lplayer_y->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    Lplayer_rowcount->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    Lplayer_colcount->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    label_map->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    label_map->setFont(f);
    labelRow->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    labelCol->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    money_label->setStyleSheet("QLabel { color : rgb(200,150,50); }");
    money_label->setFont(f);
    money->setStyleSheet("QLabel { color : rgb(200,150,50); }");

    //-------------------------------------------------change spin
    QPalette myPalette;
    myPalette.setColor(QPalette::Active, QPalette::Base, QColor(200,150,50));
    map_rowcount->setPalette(myPalette);
    map_colcount->setPalette(myPalette);
    money_spin->setPalette(myPalette);
    player_count->setStyleSheet("QComboBox { background-color: rgb(200,150,50); }");
    player_count->setPalette(myPalette);


    //----------------------------------------------------signals
    connect(start,SIGNAL(clicked()),this,SLOT(Start()));
    connect(quit,SIGNAL(clicked()),this,SLOT(Quit()));
    connect(player_count,SIGNAL(currentIndexChanged(int)),this,SLOT(ShowPlayer()));
}


void BuildGame::ShowPlayer(){
    for(int i=3; i<11; i++)
        table->showRow(i);
    for(int i=3+player_count->currentIndex(); i<11; i++)
        table->hideRow(i);
}

void BuildGame::Start(){

    if(player_count->currentIndex()==0 || player_count->currentIndex()==1)
        return;


    map=new Map(map_rowcount->value(),map_colcount->value());

    //-------------------------------------------------------build zombie team
    vector <Block*> t1;
    Player zombie_player("zombie",-1,0,-1,t1);
    players_game.push_back(zombie_player);

    for(int i=1; i<player_count->currentIndex()+1; i++){

        Player temp;
        vector< Block*> area;
        int team_id=player_team[i+1]->currentIndex();
        int money=money_spin->value();
        QString str_name=player_name[i+1]->text();

        //-----------------------------------------------set area block
        int start_row=player_x[i+1]->text().toInt();
        int start_col=player_y[i+1]->text().toInt();
        int count_row=player_rowcount[i+1]->text().toInt();
        int count_col=player_colcount[i+1]->text().toInt();
        for(int j=start_row; j<start_row+count_row; j++)
            for(int k=start_col; k<start_col+count_col; k++)
                if(j>0 && k>0 && j<map->GetRowcount() && k<map->GetColcount())
                    area.push_back(map->getBlock(j,k));

        players_game.push_back(Player(str_name,team_id,money,i,area));

    }

    for(unsigned int i=0; i<players_game.size(); i++)
        game_players.push_back(&players_game[i]);
    XmlReader reader(game_players);
    //------------------------------------------------------build new game
    MyGame->newGame(game_players,map);
    music->stop();
    game_window=new GameWindow(MyGame,game_players);
    game_window->showMaximized();

}

void BuildGame::Quit(){
    exit(0);
}
