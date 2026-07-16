#pragma once
#include <string>
class Weapon
{
public:
	std::string name;
	int minDamage;
	int maxDamage;
	short critChance;
	int price;
	int lvlReq;
	bool isBought;

	Weapon(std::string name, int minDamage,	int maxDamage,	short critChance,	int price,	int lvlReq,	bool isBought);


};

