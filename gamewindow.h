#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <vector>
#include <iostream>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QWidget>
#include <QTableWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include "graphicmap.h"
using namespace std;

class GameWindow : public QDesktopWidget{

    Q_OBJECT
public:
    GameWindow(class Game* , vector<class Player*> , QWidget* parent=0);
    bool eventFilter(QObject* obj,QEvent* event) {
        if(event->type()==QEvent::MouseMove){
            GameMap->update();
            int x=QCursor::pos().x();
            int y=QCursor::pos().y();
            if(y<8)
                this->UpMap();
            if(y>this->height()-7)
                this->DownMap();
            if(x<8)
                this->LeftMap();
            if(x>this->width()-8)
                this->RightMap();
        }
        return false;
    }
    ~GameWindow();

private:
    bool sell;
    bool upgrade;
    bool targeting;
    bool moving;
    bool super_attack;
    int row;
    int col;
    int count_turn;
    int turning;
    class Game* game;
    class Building* UnitMakerBuilding;
    class Unit* unit;
    class GameObject* game_object;
    vector<class GameObject*> game_objects;
    vector<class Player*> players;

    //------------------------tables
    QTableWidget* table;
    QTableWidget* table2;
    QTableWidget* MapTable;
    QTableWidget* BuildingTable;
    QTableWidget* PlayerTable;
    QTableWidget* ObjectTable;
    QTableWidget* Information;

    //----------------------------pushButtons
    QPushButton** MapButtons;
    QPushButton* EndTurn;
    QPushButton* Base_Building;
    QPushButton* VehicleMaker_Building;
    QPushButton* SuperMaker_Building;
    QPushButton* NormalMaker_Building;
    QPushButton* MoneyMaker_Building;
    QPushButton* Defence_Building;
    QPushButton* QuitButton;
    QPushButton* Button[10];
    QPushButton* player_label;
    QPushButton* common_unit[10];

    //----------------------------graphic map
    GraphicMap* GameMap;

    //----------------------------labels
    QLabel* events;
    QLabel* PlayerTurn;
    QLabel* PlayerMoney;
    QLabel* turn_count;

    //--------information labels
    QLabel* damage;
    QLabel* health;
    QLabel* speed;
    QLabel* units;
    QLabel* unit_training;
    QLabel* level;
    QLabel* special_attack;
    QLabel* mana;
    QLabel* name;
    QLabel* attack_range;
    QLabel* attack_delay;
    QLabel* Information_label[10];

    //----------------------------Layouts
    QHBoxLayout* common_layout;

    //----------------------------functions
    void Update();
    class GameObject* SetInformation(class GameObject*);
    void setUnit(class GameObject*);
    void SetCheckFalse();
    void ShowArea(int,bool);

public slots:
    void CreateBuilding(int place);
    void setUnits(int numberButton);
    void QuitGame();
    void NextTurn();
    void CreateUnit();
    void UnActive();
    void Move();
    void SetTarget();
    void Unload();
    void RightMap();
    void LeftMap();
    void UpMap();
    void DownMap();
    void Selling();
    void ShowMyArea();
};

#endif // GAMEWINDOW_H
