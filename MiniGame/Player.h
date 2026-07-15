#pragma once
class Player
{
public:
	float hp;
	float maxHp=100;
	int minDamage;
	int maxDamage;
	short critChance;
	short armor;
	int level = 1;
	int playerXp = 0;
	int xpToNextLvl = 100*level*1.5;
	int money = 0;
	
	Player(float hp, int minDamage, int maxDamage, short critChance, short armor);
	int CalculateDamage();
	int TakeDamage(int damage);
	bool isAlive();
	void AddXp(int amount);

};

