#pragma once
#include <string>
#include <utility>
#include "GameManager.h"
class Enemy
{
private:
	std::string name;
	float hp;
	float maxHp;
	int minDamage;
	int maxDamage;
	short critChance;
	short armor;
	int money;
	int xpReward;
	DifficultyLevel difficulty;
public:
	Enemy();
	Enemy(std::string name, float maxHp, int minDamage, int maxDamage, short critChance, short armor,int money,int xpReward, DifficultyLevel difficulty);
	std::pair<int, int> CalculateDamage()const;
	void Attack(class Player& target);
	int TakeDamage(int damage);
	
	bool isAlive()const;
	std::string getName()const;
	float getHp()const;
	float getMaxHp()const;
	int getMinDamage()const;
	int getMaxDamage()const;
	short getCritChance()const;
	short getArmor()const;
	int getMoney()const;
	int getXpReward()const;

};

