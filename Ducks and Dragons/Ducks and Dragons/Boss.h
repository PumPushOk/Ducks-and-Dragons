#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
{
public:
    void attack(Creature* player) {
        player->health -= damage;
        if (player->health < 0)
            player->health = 0;
    }

    Boss() {
        Enemy::name = "Uncle";
        Enemy::maxHealth = 500;
        Enemy::health = maxHealth;
        Enemy::damage = 75;
        Enemy::shape = {
       "~~~~~~~~~~~00000000~~~~~~",
       "~~~~~~~~~000EEEEEE00~~~~~",
       "~~~~~~~~006EEEEEEEE00~~~~",
       "~~~~~~~~06EEEE8FFFEE0~~~~",
       "~~~~~~~00EEEE8FFFFEE0~~~~",
       "~~~~~~0066EEE8FFFEE0~~~~~",
       "~~~~~006666E0000000000~~~",
       "~~~~0066660000000000000~~",
       "~~0066660000000EEE000~~~~",
       "~~0E06600BFFF000E0F0~~~~~",
       "~~0EE0000BFFF0F000000~~~~",
       "~~0EEE00EEEFFFE04CFF00~~~",
       "~~0EEEEEEEB0EE04CCCFC0~~~",
       "~~~0EE000E00E044CCCCC0~~~",
       "~~~0EEE0000000404CCCC0~~~",
       "~~~0EEE08800F00044440~~~~",
       "~~~~000E08F8FF8F0000~~~~~",
       "~~~~~00EE00FFFFFFF080~~~~",
       "~~~~~000EEEEEEEEEEE80~~~~",
       "~~~~~~~0000EEEEEEE00~~~~~",
       "~~~~~~~~~~000000000~~~~~~",
        };
    }
};

