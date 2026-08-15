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

enum class DifficultyLevel {
    EASY,
    NORMAL,
    HARD
};

struct DifficultyConfig {
    float healCostMultiplier = 1.0f;
    float enemyHpMultiplier = 1.0f;
    short easyEnemyChance = 75;
    short medEnemyChance = 18;
    short hardEnemyChance = 7;
    int easyNum = 0;
    int medNum = 0;
    int hardNum = 0;
    std::string difficultyName = "";
};
inline constexpr DifficultyConfig EASY_CONFIG = {
    .healCostMultiplier = 0.8f,
    .enemyHpMultiplier = 0.8f,
    .easyEnemyChance = 87,
    .medEnemyChance = 12,
    .hardEnemyChance = 1,
    .difficultyName = "Easy"
};
inline constexpr DifficultyConfig NORMAL_CONFIG = {
    .healCostMultiplier = 1.0f,
    .enemyHpMultiplier = 1.0f,
    .easyEnemyChance = 75,
    .medEnemyChance = 18,
    .hardEnemyChance = 7,
    .difficultyName = "Normal"
};
inline constexpr DifficultyConfig HARD_CONFIG = {
    .healCostMultiplier = 1.2f,
    .enemyHpMultiplier = 1.2f,
    .easyEnemyChance = 50,
    .medEnemyChance = 35,
    .hardEnemyChance = 15,
    .difficultyName = "Hard"
};


class GameManager
{
private:

    array<Enemy, 12> enemies;
    array<Weapon, 12> weapons;
    array<Player, 6> players;
	std::unique_ptr<Player> myPlayer = nullptr;

    DifficultyLevel currentDifficulty = DifficultyLevel::NORMAL;
    DifficultyConfig currentConfig;

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

    DifficultyLevel getDifficulty()const;
    void setDifficulty(DifficultyLevel difficulty);
    void battleSystem();
    std::unique_ptr<Enemy> getRandomEnemy()const;
    void playerCreation();
    void printEnemyCatalogue()const;
    void printWeaponCatalogue()const;
    void printPlayerStats()const;
    void printPlayerStats(const Player& player)const;
    void inventorySystem();
    void openShop();
    void armorShop();
    void chooseDifficulty();

};

