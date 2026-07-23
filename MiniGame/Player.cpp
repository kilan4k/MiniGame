#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include <cstdlib>
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl;


Player::Player(int level, int money, Weapon* currentWeapon, short armor)
	:level(level),money(money),maxHp(90+level*10), hp(90 + level * 10), currentWeapon(currentWeapon), armor(armor)
{
	
}
std::pair<int, int> Player::CalculateDamage(){
	int minDamage = getMinDamage();
	int maxDamage = getMaxDamage();
	bool getCrit= rand() % 100 < getCritChance();
	int baseDamage = rand() % (1+maxDamage - minDamage) + minDamage; // Damage between min and max
	//cout << "Random Damage got: " << damage<<"\n";
	int finalDamage= getCrit? round((float)baseDamage* 1.5) : baseDamage; // damage after crit + 50% 
	//cout << "Damage after critChance: " << damage<<"\n";
	return { finalDamage,baseDamage};
}
void Player::Attack(Enemy& target) {
	std::cout << "\n-------------------------------------------";
	auto damageData = CalculateDamage();
	int afterCritDamage = damageData.first;
	int baseDamage = damageData.second;
	bool isCrit = afterCritDamage > baseDamage; // if final damage > base damage => its a crit
	int finalDamage = target.TakeDamage(afterCritDamage);
	int blockedDamage = afterCritDamage - finalDamage;
	std::cout << "\n[COMBAT, PLAYER'S TURN] Player " << name << " attacks " << target.name << "\n";
	
	std::cout << "--> Base damage: " << baseDamage << "\n";
	if (isCrit) cout << "[CRITICAL DAMAGE]\n--> Damage after crit: "<<afterCritDamage<<"\n";
	if (blockedDamage > 0) {
		std::cout << "--> " << target.name << "'s armor (" << target.armor << " class) blocked " << blockedDamage << " damage.\n";
	}
	std::cout << "--> Result: Dealt " << finalDamage << " damage leaving enemy with " << target.hp << " HP.";
	std::cout << "\n-------------------------------------------\n\n\n";
}
int Player::TakeDamage(int damage) {
	damage = armor <= 4 ? damage - damage * ((float)armor / 5.0) : damage - damage * 4.0 / 5.0; // Damage reduces if there's armor. Can't be armor class greater than 4 tho
	//cout << "Damage after armor: " << damage << "\n"; 
	hp -= damage<hp?damage:hp; // if dmg is greater than hp then u cry man
	return damage;
}
bool Player::isAlive() { // Checking if Player's alive
	return hp > 0;
}
void Player::AddXp(int amount) { // Adding XP to a player, if levels up then reduces xp required for lvl in case they have xp for leveling up to few more levels
	std::cout << "\n-------------------------------------------";
	playerXp += amount;
	while (playerXp >= xpToNextLvl) {
		level++;
		std::cout << "\n[LEVEL] you leveled up to " << level << " level\n";
		playerXp -= xpToNextLvl;
		xpToNextLvl = 100 * level * 1.5;
		maxHp = (90 + level * 10);
		hp = hp + 10 > maxHp ? maxHp : hp+10;
		cout << "HP: " << hp;
	}
	std::cout << "\n-------------------------------------------\n" << "\n";
}

int Player::getMinDamage()const {
	return currentWeapon->minDamage+(level*2);
}
int Player::getMaxDamage()const {
	return currentWeapon->maxDamage + (level * 2);
}
int Player::getCritChance() const {
	return currentWeapon->critChance;
}

void Player::HealPlayer() {
	const int HEAL_PRICE_PERHP = 0+(level*2); 
	int totalCost = HEAL_PRICE_PERHP * (maxHp - hp);
	char choice; // for checkin Y and N
	int numChoice; // for choosing hp
	bool leaving = false;
	std::cout << "\n-------------------------------------------\n";
	std::cout << "[HEALING MENU]\n";
	std::cout << "\nYour balance is " << money << "$\n";
	if (hp == maxHp) {
		std::cout << "You already have max HP of " << maxHp<<"\n";
	}
	while (!leaving && hp!=maxHp) { // repeating ts till user leaves menu
		if (money >= totalCost) {
			std::cout << "\nAre you sure you want to spend " << HEAL_PRICE_PERHP << "$ per hp to heal yourself to your max HP of " << maxHp << "\n";
			std::cout << "Healing to " << maxHp << " will cost you " << totalCost << "$\n";
			std::cout << "Type 'Y' if you agree, Type 'N' if you do not or want to heal to a specific number of HP\n";
			std::cin >> choice;

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			switch (toupper(choice)) {
			case 'Y':
				choice = ' ';
				money -= totalCost;
				hp = maxHp;
				std::cout << "You're successfully healed! Your HP now is " << hp<<"!\n";
				leaving = true;
				break;

			case 'N':
				choice = ' ';
				std::cout << "Type '-1' if you want to leave this menu, Type a number " << hp + 1 << '-' << maxHp << " to choose HP to heal you for.\n";
				std::cin >> numChoice;

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (numChoice == -1) leaving = true;
				else if ( (numChoice > hp && numChoice <= maxHp) ) { // checking if input number is available number to heal
					std::cout << "Healing to " << numChoice << " HP will cost you " << HEAL_PRICE_PERHP * (numChoice - hp)<<"$" <<
					"\nType 'Y' if you agree to heal, type 'N' to leave this menu\n";
					std::cin >> choice;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (toupper(choice) == 'Y') {
					money -= HEAL_PRICE_PERHP * (numChoice - hp );
					std::cout << "You have successfully healed to " << numChoice<< " HP! And spent "<< HEAL_PRICE_PERHP * (numChoice - hp) << "$\n";
					hp = numChoice;
					leaving = true;
					}
					else {
						leaving = true;
					}
				}
				else {
					std::cout << "Error! Try again!\n";
				}
				break;
			default:
				std::cout << "Error! Try again!\n";
					break;
			}
		}
		else 
		{
			if (money >= HEAL_PRICE_PERHP) {
			std::cout << "\nYou have not enough money to heal you to " << maxHp << " HP (that costs " << totalCost << "$)\n";
			std::cout << "Heal Price per 1 HP = "<<HEAL_PRICE_PERHP<<"\n";
			std::cout << "Type '-1' if you want to leave this menu, Type a number " << hp + 1 << '-' <<(int) (hp + (money/HEAL_PRICE_PERHP ))<< " to choose HP to heal you for.\n";
			std::cin >> numChoice;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (numChoice == -1) leaving = true;
			else if (numChoice>hp && numChoice<=(hp + (money / HEAL_PRICE_PERHP))) {
				std::cout << "Healing to " << numChoice << " HP will cost you " << HEAL_PRICE_PERHP * (numChoice - hp)<<"$" <<
				"\nType 'Y' if you agree to heal, type 'N' to leave this menu\n";
				std::cin >> choice;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (toupper(choice) == 'Y') {
					money -= HEAL_PRICE_PERHP * (numChoice - hp);
					std::cout << "You have successfully healed to " << numChoice << " HP! And spent " << HEAL_PRICE_PERHP * (numChoice - hp) << "$\n";
					hp = numChoice;
					leaving = true;
				}
			}
			else {
				std::cout << "Error! Try again!\n";
			}	
		}
			else {
				std::cout<<"\nYou don't even have enough money to heal you for 1 HP lol (it's "<<HEAL_PRICE_PERHP<<"$ per 1 HP" << "\n";
				leaving = true;
			}
		}
	}
	std::cout << "-------------------------------------------\n";
}