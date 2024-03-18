#pragma once
#include <string>
using namespace std;

class Creature
{
public:
	virtual void attack(Creature* player) = 0;

	string name = "";
	int maxHealth = 0;
	int health = 0;
	int damage = 0;
	int coins = 0;
};

