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
	int money = 0;
	
	Player(float hp, int minDamage, int maxDamage, short critChance, short armor);
	int CalculateDamage();
	int TakeDamage(int damage);
	bool isAlive();


};

