#pragma once
#include <iostream>
#include <Windows.h>
#include "Enemy.h"
using namespace std;

class Location
{ 
public:
	string name;
	COORD coord;
	Enemy* enemy;

	Location(const string& name, COORD coord, Enemy* enemy) :name(name), coord(coord), enemy(enemy) {}
};