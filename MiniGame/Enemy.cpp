#include "Enemy.h"
#include <cstdlib>
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl;

Enemy::Enemy() {
	name = "nullEnemy";
	hp = 1;
	maxHp= 1;
	minDamage = 1;
	maxDamage = 1;
	critChance = 0;
	armor = 0;
	money = 1;
}
Enemy::Enemy(string name, float maxHp, int minDamage, int maxDamage, short critChance, short armor, int money, int xpReward)
	: name(name), hp(maxHp),maxHp(maxHp), minDamage(minDamage),maxDamage(maxDamage),critChance(critChance),armor(armor),money(money), xpReward(xpReward) 
{}

int Enemy::CalculateDamage() {
	int damage = rand() % (1 + maxDamage - minDamage) + minDamage; // Damage between min and max
	//cout << "Random Damage got: " << damage<<"\n";
	damage = rand() % 100 < critChance ? round((float)damage * 1.5) : damage; // damage after crit + 50% 
	//cout << "Damage after critChance: " << damage<<"\n";
	return damage;
}

int Enemy::TakeDamage(int damage) {
	damage = armor <= 4 ? damage - damage * armor / 5 : damage - damage * 4 / 5; // Damage reduces if there's armor. Can't be armor class greater than 4 tho
	//cout << "Damage after armor: " << damage << "\n"; 
	hp -= damage < hp ? damage : hp; // if dmg is greater than hp then u cry man
	return damage;
}

bool Enemy::isAlive() {
	return hp > 0;
}

