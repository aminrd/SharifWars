#ifndef BUILDGAME_H
#define BUILDGAME_H
#include <QDesktopWidget>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QFrame>
#include <QSpinBox>
#include <QComboBox>
#include <QSound>
#include <QLineEdit>
#include "game.h"
#include "map.h"
#include "gamewindow.h"
#include "player.h"

class BuildGame :public QDesktopWidget{

    Q_OBJECT

public:
    BuildGame(Game*, QWidget* parent=0);

private:
    vector<Player> players_game;
    vector<Player*> game_players;
    Game* MyGame;
    GameWindow* game_window;
    Map* map;
    //--------------------qmusic
    QSound* music;

    //--------------------push buttons
    QPushButton* start;
    QPushButton* quit;
    QPushButton* arm_player[10];

    //--------------------table
    QTableWidget* table;
    QTableWidget* player_selection;
    QTableWidget* players[10];
    QTableWidget* table1;

    //--------------------frame
    QFrame* map_frame;

    //---------------------spin box
    QSpinBox* map_rowcount;
    QSpinBox* map_colcount;
    QSpinBox* money_spin;

    //---------------------line edit
    QLineEdit* player_name[10];
    QLineEdit* player_x[10];
    QLineEdit* player_y[10];
    QLineEdit* player_rowcount[10];
    QLineEdit* player_colcount[10];

    //------------------------label
    QLabel* Lplayer_count;
    QLabel* Lplayer_name;
    QLabel* Lplayer_team;
    QLabel* Lplayer_x;
    QLabel* Lplayer_y;
    QLabel* Lplayer_rowcount;
    QLabel* Lplayer_colcount;

    //------------------------ComboBox
    QComboBox* player_team[10];
    QComboBox* player_count;

public slots:
    void ShowPlayer();
    void Quit();
    void Start();

};

#endif // BUILDGAME_H
