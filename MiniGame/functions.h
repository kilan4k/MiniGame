#pragma once
#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#include <random>
#include <memory>

void clearInput();
std::unique_ptr<Enemy> getRandomEnemy(std::vector<Enemy>& enemies);
void battleSystem(Player& player, std::vector<Enemy>& enemies);
std::string toLowerString(std::string str);
void printPlayerStats(const Player& player);
void printEnemyCatalogue(const std::vector<Enemy>& enemies);
void printWeaponCatalogue(const std::vector<Weapon>& weapons);
void inventorySystem(Player& player);
Player* playerCreation(std::vector<Weapon>& weapons, const std::vector<Player>& playerTypes);
void openShop(Player& player, std::vector<Weapon>& weapons);
int getRandomNumber(int num1, int num2);
void gamePlaying(Player*& player, std::vector<Enemy>& enemies, std::vector<Weapon>& weapons, const std::vector<Player> players);
void armorShop(Player& player);
constexpr double armorClassFormula(short armor) {
    return static_cast<double>(armor) / 5.0;
}