#pragma once
#include <vector>
#include "Creature.h"


class Enemy: public Creature {
public:
	virtual void attack(Creature* player) = 0;

	vector<string> shape;
	int exp = 0;
};