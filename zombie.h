#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "unit.h"

class Zombie : public Unit{

public:
    Zombie(class Map*,class Player*);
    static int zombie_max_health;
    static int zombie_attack_damage;
    static int zombie_attack_range;
    static int zombie_attack_delay;
    static int zombie_speed;
    static int zombie_spawn_period;
    static int zombie_spawn_count;
    bool Attack(GameObject*);

};

#endif // ZOMBIE_H
