#pragma once
#include <utility>
#include <string>
class Player
{
	friend class Weapon;
public:
	std::string name;
	float maxHp = 100;
	float hp;
	Weapon* currentWeapon;
	short armor;
	int level;
	int playerXp = 0;
	int xpToNextLvl = 100*level*1.5;
	int money = 0;

	Player(int level, int money, Weapon* currentWeapon, short armor); 
	std::pair<int, int >CalculateDamage();
	int TakeDamage(int damage);
	void Attack(class Enemy& target);
	bool isAlive();
	void AddXp(int amount);
	int getMinDamage()const;
	int getMaxDamage()const;
	int getCritChance()const;

};

