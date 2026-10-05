#pragma once
#include <string>
#include <compare>
enum class WeaponIndex {
	Fists = 0,
	Knife = 1,
	Machete = 2,
	Axe = 3,
	Hammer = 4,
	Sword = 5,
	Bow = 6,
	Katana = 7,
	Shotgun = 8,
	FireStaff = 9,
	LightSaber = 10,
	DeadStaff = 11
};
class Weapon
{
private:
	WeaponIndex weaponId;
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

	Weapon(WeaponIndex weaponId, std::string name, int minDamage,	int maxDamage,	short critChance,	int price,	int lvlReq,	bool isBought);
	WeaponIndex getWeaponId()const;
	std::string getName() const;
	int getMinDMG() const;
	int getMaxDMG() const;
	short getCritChance() const;
	int getPrice() const;
	int getLvlReq() const;
	bool getIsBought() const;
	void setIsBought(bool set);

};

