#include "Enemy.h"
#include "Player.h"
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

std::pair<int, int> Enemy::CalculateDamage() {
	int baseDamage = rand() % (1 + maxDamage - minDamage) + minDamage; // Damage between min and max
	bool getCrit = rand() % 100 < critChance;
	//cout << "Random Damage got: " << damage<<"\n";
	int finalDamage = getCrit ? round((float)baseDamage * 1.5) : baseDamage; // damage after crit + 50% 
	//cout << "Damage after critChance: " << damage<<"\n";
	return { finalDamage, baseDamage };
}
void Enemy::Attack(class Player& target) {
	auto damageData = CalculateDamage();
	int afterCritDamage = damageData.first;
	int baseDamage = damageData.second;
	bool isCrit = afterCritDamage > baseDamage; // if final damage > base damage => its a crit
	int finalDamage = target.TakeDamage(afterCritDamage);
	int blockedDamage = afterCritDamage - finalDamage;
	std::cout << "\n[COMBAT, ENEMY's TURN] Enemy " << name << " attacks Player " << target.name << "\n";

	std::cout << "--> Base damage: " << baseDamage << "\n";
	if (isCrit) cout << "[CRITICAL DAMAGE]\n--> Damage after crit: " << afterCritDamage << "\n";
	if (blockedDamage > 0) {
		std::cout << "--> " << target.name << "'s armor (" << target.armor << " class) blocked " << blockedDamage << " damage.\n";
	}
	std::cout << "--> Result: Dealt " << finalDamage << " damage leaving player with " << target.hp << " HP.\n\n";
}
int Enemy::TakeDamage(int damage) {
	damage = armor <= 4 ? damage - damage *( (float)armor / 5.0 ): damage - damage * 4.0 / 5.0; // Damage reduces if there's armor. Can't be armor class greater than 4 tho
	//cout << "Damage after armor: " << damage << "\n"; 
	hp -= damage < hp ? damage : hp; // if dmg is greater than hp then u cry man
	return damage;
}

bool Enemy::isAlive() {
	return hp > 0;
}

