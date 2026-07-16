#include <string>
using std::string;
#pragma once
class Weapon
{
public:
	string name;
	int minDamage;
	int maxDamage;
	short critChance;
	int price;
	int lvlReq;
	bool isBought;

	Weapon(string name, int minDamage,	int maxDamage,	short critChance,	int price,	int lvlReq,	bool isBought);


};

