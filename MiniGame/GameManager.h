#pragma once
#include "Enemy.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"
#include <string>
#include <vector>
#include <memory>
#include <array>
using std::vector,std::string,std::array;
class GameManager
{
private:
    array<Enemy, 12> enemies;
    array<Weapon, 12> weapons;
    array<Player, 6> players;

	std::unique_ptr<Player> myPlayer = nullptr;

    void declareData();
public:
    enum WeaponIndex {
        FISTS = 0,
        KNIFE = 1,
        MACHETE = 2,
        AXE = 3,
        HAMMER = 4,
        SWORD = 5,
        BOW = 6,
        KATANA = 7,
        SHOTGUN = 8,
        FIRESTF = 9,
        LGHTSBR = 10,
        DEADSTF = 11
    };
    enum EnemyIndex {
        RAT = 0,
        SPIDER = 1,
        ROGUE = 2,
        SKELETON = 3,
        ZOMBIE = 4,
        GOBLIN = 5,
        BARBARIAN = 6,
        BEAR = 7,
        JUGGERNAUT = 8,
        KNIGHT = 9,
        DRAGON = 10,
        DEMON = 11
    };

    GameManager();
    ~GameManager();
    void run();
    void quit();

    void battleSystem();
    std::unique_ptr<Enemy> getRandomEnemy();
    void playerCreation();
    void printEnemyCatalogue()const;
    void printWeaponCatalogue()const;
    void printPlayerStats(const Player& player)const;
    void inventorySystem();
    void openShop();
    void armorShop();

};

