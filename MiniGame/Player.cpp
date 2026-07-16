#include "Player.h"
#include "Weapon.h"
#include <cstdlib>
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl;


Player::Player(int level, int money, Weapon* currentWeapon, short armor)
	:level(level),money(money),maxHp(90+level*10), hp(90 + level * 10), currentWeapon(currentWeapon), armor(armor)
{}
int Player::CalculateDamage() {
	int minDamage = getMinDamage();
	int maxDamage = getMaxDamage();
	int damage = rand() % (1+maxDamage - minDamage) + minDamage; // Damage between min and max
	//cout << "Random Damage got: " << damage<<"\n";
	damage = rand() % 100 < getCritChance() ? round((float)damage * 1.5) : damage; // damage after crit + 50% 
	//cout << "Damage after critChance: " << damage<<"\n";
	return damage;
}
int Player::TakeDamage(int damage) {
	damage = armor <= 4 ? damage - damage * armor / 5 : damage - damage * 4 / 5; // Damage reduces if there's armor. Can't be armor class greater than 4 tho
	//cout << "Damage after armor: " << damage << "\n"; 
	hp -= damage<hp?damage:hp; // if dmg is greater than hp then u cry man
	return damage;
}
bool Player::isAlive() { // Checking if Player's alive
	return hp > 0;
}
void Player::AddXp(int amount) { // Adding XP to a player, if levels up then reduces xp required for lvl in case they have xp for leveling up to few more levels
	playerXp += amount;
	while (playerXp >= xpToNextLvl) {
		level++;
		playerXp -= xpToNextLvl;
		xpToNextLvl = 100 * level * 1.5;
	}
}
int Player::getMinDamage()const {
	return currentWeapon->minDamage+(level*2);
}
int Player::getMaxDamage()const {
	return currentWeapon->maxDamage + (level * 2);
}
int Player::getCritChance() const {
	return currentWeapon->critChance;
}