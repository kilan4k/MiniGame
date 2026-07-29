#pragma once
#include <string>
class Weapon
{
private:
	std::string name;
	int minDamage;
	int maxDamage;
	short critChance;
	int price;
	int lvlReq;
	bool isBought;
public:
	Weapon(std::string name, int minDamage,	int maxDamage,	short critChance,	int price,	int lvlReq,	bool isBought);
	std::string getName() const;
	int getMinDMG() const;
	int getMaxDMG() const;
	short getCritChance() const;
	int getPrice() const;
	int getLvlReq() const;
	bool getIsBought() const;
	void setIsBought(bool set);

};

