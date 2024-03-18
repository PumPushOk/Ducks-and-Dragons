#pragma once
#include "Enemy.h"
class Ogre : public Enemy
{
public:
	void attack(Creature* player) {
        player->health -= damage;
        if (player->health < 0)
            player->health = 0;
	}

	Ogre() {
		Enemy::name = "Green Guy";
        Enemy::maxHealth = 200;
		Enemy::health = maxHealth;
		Enemy::damage = 30;
        Enemy::coins = 35;
        Enemy::exp = 70;
		Enemy::shape = {
               "~~~~~~A~~AAAA~~A~~~~~~",
               "~~~~~AA~AAAAAA~AA~~~~~",
               "~~~~~~~AAAAAAAA~~~~~~~",
               "~~~~~~~AA88AA88~~~~~~~",
               "~~~~~~~AA0AAA0A~~~~~~~",
               "~~~~~~AAAAAAA2AA~~~~~~",
               "~~~~~~AAA4A222AA~~~~~~",
               "~~~~~~AAAA44444A~~~~~~",
               "~~~~~~AAAAAAAAAA~~~~~~",
               "~~~8888AAAAAAAAA877~~~",
               "~~77788888AAAAAA88877~",
               "~77778888888778888777~",
        };
	}

};

