#pragma once
#include <vector>
#include <compare>
#include <utility>
#include <string>

class Player
{
private:
	class Weapon* currentWeapon;
	std::vector<Weapon*> inventory;
	short armor;
	int level;
	float maxHp = 100;
	float hp;
	int playerXp = 0;
	int money = 0;
	int kills = 0;
	std::string name;
	static constexpr float BASE_HEAL_COST = 0.25f;
	static constexpr float HEAL_COST_PER_LVL = 0.02f;
	

	constexpr float getMaxHpFormula() const {
		return 90.0f + ((level * 10.0f) * 1.1f);
	}
	constexpr int getLevelXpFormula()const {
		return static_cast<int>(10 * level * 1.25);
	}
	int xpToNextLvl = getLevelXpFormula();
public:
	Player() = default;
	bool operator==(const Player& other)const {
		return name == other.name;
	}

	Player(int level, int money, Weapon* currentWeapon, short armor, std::string name); 
	std::pair<int, int>CalculateDamage()const;
	int TakeDamage(int damage);
	void Attack(class Enemy& target);
	void AddXp(int amount);
	void HealPlayer(float healCostMultiplier);
	int getMinDamage()const;
	int getMaxDamage()const;
	int getCritChance()const;
	int getArmorPrice(short armorClass)const;
	bool isAlive()const;


	const std::vector<Weapon*>& getInventory() const;
	std::vector<Weapon*>& getInventory();

	void addWeaponToInventory(Weapon* weapon);
	std::string getName()const;
	void setName(std::string sName);
	float getMaxHp()const;
	float getHp()const;
	Weapon* getCurrentWeapon()const;
	void setCurrentWeapon(Weapon* weapon);
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

constexpr double armorClassFormula(short armor) {
	return static_cast<double>(armor) / 5.0;
}