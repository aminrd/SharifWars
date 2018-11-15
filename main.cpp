#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <windows.h>
#include <QApplication>

#include "base.h"
#include "defence.h"
#include "unit.h"
#include "place.h"
#include "moneymaker.h"
#include "unitmaker.h"
#include "normalunit.h"
#include "superunit.h"
#include "vehicle.h"
#include "block.h"
#include "game.h"
#include "gameobject.h"
#include "player.h"
#include "map.h"
#include "checker.h"
#include "building.h"
#include "startwindow.h"
#include "gamewindow.h"
#include "xmlreader.h"
#include "endgame.h"
#include "buildgame.h"



using namespace std;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);


    //-----------------------------------------------------------------------Start Game
    BuildGame GamePlay(Game::getInstance());
    StartWindow StartGame(&GamePlay);
    StartGame.showNormal();
    //EndGame end(2);
    //end.show();

    return a.exec();
}
