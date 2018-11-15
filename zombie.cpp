#include "zombie.h"
#include "player.h"

int Zombie::zombie_attack_damage=1;
int Zombie::zombie_attack_delay=1;
int Zombie::zombie_attack_range=1;
int Zombie::zombie_speed=1;
int Zombie::zombie_spawn_count=1;
int Zombie::zombie_spawn_period=1000;
int Zombie::zombie_max_health=1;

Zombie::Zombie(class Map* _map,class Player* _player) : Unit(_map){
    gameObjectType=7;
    name="Zombie";
    max_health=zombie_max_health;
    attack_damage=zombie_attack_damage;
    attack_range=zombie_attack_range;
    attack_delay=zombie_attack_delay;
    speed=zombie_speed;

    health=max_health;
}

bool Zombie::Attack(GameObject* game_object){


    if(game_object==NULL)
        return false;
    if(game_object->getType()<4)
        return false;

    Player *temp=game_object->getPlayer();
    Player *my_player=player;
    int id1=temp->getTeam();
    int id2=my_player->getTeam();

    if(id1 != id2){
        if(stoping_of_attack==0){
            game_object->Damage(attack_damage);

            //--------------------------------------------if zombie kill unit

            if(game_object->getHealth()<=0)
                game_object->setHealth(-10000);

            stoping_of_attack=attack_delay+1;
            return true;
        }
    }
    return false;
}
