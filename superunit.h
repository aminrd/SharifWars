#ifndef SUPERUNIT_H
#define SUPERUNIT_H
#include "unit.h"
#include <stdio.h>
#include <cstring>

class SuperUnit :public Unit{

friend class Game;

private:
    int mana;
    int max_mana;
    int mana_regeneration;
    int specialattack;
    int manaCost;
    int training_time;
    int stoping_of_specialAttack;
    bool upgrade();

public:
    SuperUnit(class Map*,class Player*);
    int getMaxMana();
    int getMana();
    int getManaRegenerationAmount();
    int getSpecialAttackDamage();
    int getManaCost();
    void manaRegeneration();
    void specialAttack(GameObject*);
    void setstopingSpecialAttack();
    string getStatus();

};

#endif // SUPERUNIT_H
