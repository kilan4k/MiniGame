#pragma once
#include <utility>
#include <string>
#define NEXT_LEVEL_XP_FORMULA 20*level*1.25;
class Player
{
private:




public:
	std::string name;
	float maxHp = 100;
	float hp;
	class Weapon* currentWeapon;
	short armor;
	int level;
	int playerXp = 0;
	int xpToNextLvl = NEXT_LEVEL_XP_FORMULA;
	int money = 0;
	int kills = 0;
	Player(int level, int money, Weapon* currentWeapon, short armor); 
	std::pair<int, int >CalculateDamage();
	int TakeDamage(int damage);
	void Attack(class Enemy& target);
	bool isAlive();
	void AddXp(int amount);
	int getMinDamage()const;
	int getMaxDamage()const;
	int getCritChance()const;
	void HealPlayer();
	int getArmorPrice(short armorClass);
};

