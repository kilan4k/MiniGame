#include "Weapon.h"
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl;

Weapon::Weapon(string name, int minDamage, int maxDamage, short critChance, int price, int lvlReq, bool isBought) 
	:	name(name), minDamage(minDamage),maxDamage(maxDamage),critChance(critChance),price(price),lvlReq(lvlReq),isBought(isBought)
{}
