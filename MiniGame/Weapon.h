#pragma once
#include <string>
class Weapon
{
	friend class Player;
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

