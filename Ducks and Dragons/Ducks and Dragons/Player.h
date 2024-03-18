#pragma once
#include "Creature.h"

class Player : public Creature
{
public:
	void attack(Creature* enemy) {
		enemy->health -= damage;
		if (enemy->health < 0)
			enemy->health == 0;
	}

	Player()  {
		Creature::maxHealth = 100;
		Creature::health = maxHealth;
		Creature::damage = 10;
		Creature::coins = 0;
	}
};

