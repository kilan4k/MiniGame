#pragma once
#include <string>
#include <utility>
enum class DifficultyLevel;
enum class EnemyIndex {
	Rat = 0,
	Spider = 1,
	Rogue = 2,
	Skeleton = 3,
	Zombie = 4,
	Goblin = 5,
	Barbarian = 6,
	Bear = 7,
	Juggernaut= 8,
	Knight = 9,
	Dragon = 10,
	Demon = 11
};


class Enemy
{
private:
	EnemyIndex enemyId;
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
	Enemy(EnemyIndex enemyId, std::string name, float maxHp, int minDamage, int maxDamage, short critChance, short armor,int money,int xpReward, DifficultyLevel difficulty);
	const EnemyIndex getEnemyId()const;

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
	DifficultyLevel getDifficulty()const;
};

