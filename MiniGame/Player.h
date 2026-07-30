#pragma once
#include <vector>
#include <compare>
#include <utility>
#include <string>
#define NEXT_LEVEL_XP_FORMULA 10*level*1.25
class Player
{
private:
	std::string name;
	float maxHp = 100;
	float hp;
	class Weapon* currentWeapon;
	std::vector<Weapon> inventory;
	short armor;
	int level;
	int playerXp = 0;
	int xpToNextLvl = NEXT_LEVEL_XP_FORMULA;
	int money = 0;
	int kills = 0;

public:
	bool operator==(const Player& other)const {
		return name == other.name;
	}

	Player(int level, int money, Weapon* currentWeapon, short armor); 
	std::pair<int, int>CalculateDamage()const;
	int TakeDamage(int damage);
	void Attack(class Enemy& target);
	void AddXp(int amount);
	void HealPlayer();
	int getMinDamage()const;
	int getMaxDamage()const;
	int getCritChance()const;
	int getArmorPrice(short armorClass)const;
	bool isAlive()const;


	const std::vector<Weapon>& getInventory() const;
	std::vector<Weapon>& getInventory();

	void addWeaponToInventory(const Weapon& weapon);
	std::string getName()const;
	void setName(std::string sName);
	float getMaxHp()const;
	float getHp()const;
	Weapon* getCurrentWeapon()const;
	void setCurrentWeapon(Weapon& weapon);
	short getArmor()const;
	void setArmor(short num);
	int getLevel()const;
	int getPlayerXp()const;
	int getXpToNextLvl()const;
	int getMoney()const;
	void addMoney(int num);
	void spendMoney(int num);
	int getKills()const;
	void addKills(int num);

};

