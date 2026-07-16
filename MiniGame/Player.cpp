#include "Player.h"
#include <cstdlib>
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl;


Player::Player(float hp, Weapon* currentWeapon, short critChance, short armor)
	:hp(hp), minDamage(minDamage), maxDamage(maxDamage), critChance(critChance), armor(armor)
{}
int Player::CalculateDamage() {
	
	int damage = rand() % (1+maxDamage - minDamage) + minDamage; // Damage between min and max
	//cout << "Random Damage got: " << damage<<"\n";
	damage = rand() % 100 < critChance ? round((float)damage * 1.5) : damage; // damage after crit + 50% 
	//cout << "Damage after critChance: " << damage<<"\n";
	return damage;
}
int Player::TakeDamage(int damage) {
	damage = armor <= 4 ? damage - damage * armor / 5 : damage - damage * 4 / 5; // Damage reduces if there's armor. Can't be armor class greater than 4 tho
	//cout << "Damage after armor: " << damage << "\n"; 
	hp -= damage<hp?damage:hp; // if dmg is greater than hp then u cry man
	return damage;
}
bool Player::isAlive() {
	return hp > 0;
}
void Player::AddXp(int amount) {
	playerXp += amount;
	while (playerXp >= xpToNextLvl) {
		level++;
		playerXp -= xpToNextLvl;
		xpToNextLvl = 100 * level * 1.5;
	}
}