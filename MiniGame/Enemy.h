#pragma once
class Enemy
{
	float hp;
	float maxHp;
	float minDMG;
	float maxDMG;
	short critChance;
	short armor;
	
	Enemy(float hp, float maxHp, float minDMG, float maxDMG, short critChance, short armor);
	int TakeDamage(int damage);
	bool isAlive();


};

