#pragma once
#include <string>
#include <compare>
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
	Weapon() = default;
	bool operator==(const Weapon& other)const {
		return name == other.name;
	}
	bool operator!=(const Weapon& other)const {
		return name != other.name;
	}

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

