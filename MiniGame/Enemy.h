#pragma once
#include <string>
class Enemy
{
public:
	std::string name;
	float hp;
	float maxHp;
	int minDamage;
	int maxDamage;
	short critChance;
	short armor;
	int money;
	int xpReward;
	Enemy();
	Enemy(std::string name, float maxHp, int minDamage, int maxDamage, short critChance, short armor,int money,int xpReward);
	int CalculateDamage();
	int TakeDamage(int damage);
	bool isAlive();


};

