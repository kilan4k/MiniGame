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

void clearInput();
Enemy* getRandomEnemy(std::vector<Enemy>& enemies);
void battleSystem(Player& player, Enemy*& enemy, std::vector<Enemy>& enemies);
std::string toLowerString(std::string str);
void printPlayerStats(const Player& player);
void printEnemyCatalogue(const std::vector<Enemy>& enemies);
void printWeaponCatalogue(const std::vector<Weapon>& weapons);
Player* playerCreation(std::vector<Weapon>& weapons, std::vector<Player>& playerTypes);
void openShop(Player& player, std::vector<Weapon>& weapons);
int getRandomNumber(int num1, int num2);
void gamePlaying(Player*& player, Enemy*& enemy, std::vector<Enemy>& enemies, std::vector<Weapon>& weapons, std::vector<Player> players);
void armorShop(Player& player);
double  armorClassFormula(short armor);