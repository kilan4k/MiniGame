#include "Weapon.h"
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl;

Weapon::Weapon(string name, int minDamage, int maxDamage, short critChance, int price, int lvlReq, bool isBought) 
	:	name(name), minDamage(minDamage),maxDamage(maxDamage),critChance(critChance),price(price),lvlReq(lvlReq),isBought(isBought)
{}
std::string Weapon::getName() const {
	return name;
}
int Weapon::getMinDMG() const {
	return minDamage;
}
int Weapon::getMaxDMG() const {
	return maxDamage;
}
short Weapon::getCritChance() const {
	return critChance;
}
int Weapon::getPrice() const {
	return price;
}
int Weapon::getLvlReq() const {
	return lvlReq;
}

bool Weapon::getIsBought() const {
	return isBought;
}
void Weapon::setIsBought(bool set) {
	isBought = set;
}