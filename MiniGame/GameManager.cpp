#include "GameManager.h"
#include "Enemy.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"
#include <string>
#include <vector>

using std::cout, std::cin, std::string, std::endl, std::vector;

GameManager::GameManager() {}
GameManager::~GameManager() {
    if (myPlayer != nullptr) {
        delete myPlayer;
        myPlayer = nullptr;
    }
}


void GameManager::declareData() {
   //Declaring different objects
   //Enemy types

    Enemy rat = Enemy("Rat", 25, 5, 10, 10, 0, 10, 10); // 0
    Enemy spider = Enemy("Spider", 50, 15, 25, 50, 0, 20, 20);// 1
    Enemy rogue = Enemy("Rogue", 75, 25, 35, 15, 0, 20, 20);// 2
    Enemy skeleton = Enemy("Skeleton", 75, 20, 30, 60, 0, 30, 30);// 3
    Enemy zombie = Enemy("Zombie", 100, 20, 30, 15, 1, 30, 30);// 4
    Enemy goblin = Enemy("Goblin", 75, 30, 40, 10, 0, 50, 30);// 5
    Enemy barbarian = Enemy("Barbarian", 100, 20, 40, 5, 1, 60, 50);// 6
    Enemy bear = Enemy("Bear", 75, 40, 70, 25, 2, 105, 75);// 7
    Enemy juggernaut = Enemy("Juggernaut", 250, 15, 20, 10, 3, 100, 100);// 8
    Enemy knight = Enemy("Knight", 150, 40, 65, 25, 2, 150, 100);// 9
    Enemy dragon = Enemy("Dragon", 300, 30, 60, 35, 1, 200, 120);// 10
    Enemy demon = Enemy("Demon", 400, 60, 100, 40, 1, 240, 200);// 11

    enemies = { rat, spider, rogue, skeleton, zombie, goblin, barbarian, bear, juggernaut, knight, dragon, demon };

    //Weapon types
    Weapon fists = Weapon("Fists", 10, 20, 5, 0, 0, false); //0
    Weapon knife = Weapon("Knife", 20, 30, 5, 25, 1, false);//1
    Weapon machete = Weapon("Machete", 25, 35, 10, 85, 6, false);//2
    Weapon axe = Weapon("Axe", 35, 45, 35, 150, 7, false);//3
    Weapon hammer = Weapon("Hammer", 20, 40, 33, 95, 7, false);//4
    Weapon sword = Weapon("Sword", 40, 55, 25, 200, 10, false);//5
    Weapon bow = Weapon("Bow", 25, 60, 65, 250, 15, false);//6
    Weapon katana = Weapon("Katana", 50, 75, 50, 400, 20, false);//7
    Weapon shotgun = Weapon("Shotgun", 30, 90, 1, 600, 25, false);//8
    Weapon firestf = Weapon("Fire staff", 50, 70, 50, 750, 25, false);//9
    Weapon lightsaber = Weapon("Light Saber", 67, 80, 25, 800, 25, false);//10
    Weapon deadlystf = Weapon("Deadly staff", 50, 200, 67, 1500, 50, false);//11

    weapons = { fists, knife, machete, axe, hammer, sword, bow, katana, shotgun, firestf, lightsaber, deadlystf };

    //Player types (and declaring names beneath cus i'm a lazy man to edit a constructor but it ain't a big deal ig)
    Player empty = Player(1, 0, &weapons[WeaponIndex::FISTS], 0);
    empty.setName("New character");
    Player bandit = Player(1, 50, &weapons[WeaponIndex::KNIFE], 0);
    bandit.setName("Bandit");
    Player punchman = Player(1, 0, &weapons[WeaponIndex::FISTS], 1);
    punchman.setName("Punchman");
    Player archer = Player(1, 0, &weapons[WeaponIndex::BOW], 0);
    archer.setName("Archer");
    Player lvlPunchman = Player(10, 50, &weapons[WeaponIndex::FISTS], 0);
    lvlPunchman.setName("Leveled up Punchman");
    Player lumberjack = Player(1, 0, &weapons[WeaponIndex::AXE], 0);
    lumberjack.setName("Lumberjack");
    Player robber = Player(1, 100, &weapons[WeaponIndex::FISTS], 0);
    robber.setName("Robber");

    players = { empty, bandit, punchman, archer, lvlPunchman, lumberjack, robber };
}
void GameManager::run() {
    declareData();
    myPlayer = playerCreation(weapons, players);
    cout << "[BONUS FOR PLAYING ALPHA]\n";
    cout << "Adding 100$\n";
    myPlayer->addMoney(100);
    bool LeavingGame = false;
    while (!LeavingGame) {
        if (myPlayer->getHp() <= 0) { LeavingGame = true; break; }

        {
            cout << "\n==================================================\n";
            cout << "                    GAME MENU";
            cout << "\n==================================================\n";
        }//console output
        char choice;
        cout << "\n-------------------------------------------\n";
        cout << "Type '1' to battle\nType '2' to open shop menu\nType 'S' to print player's stats\nType 'H' to open heal menu\nType 'I' to open inventory\nType 'A' to open armor shop\nType 'E' to show every enemy stat in game\nType 'Q' to quit the game";
        cout << "\n-------------------------------------------\n";
        cin >> choice;
        clearInput();
        //cout << toupper(choice);
        switch (toupper(choice)) {
        case '1': battleSystem(*myPlayer, enemies);
            break;
        case '2': openShop(*myPlayer, weapons);
            break;
        case 'S': printPlayerStats(*myPlayer);
            break;
        case 'H': myPlayer->HealPlayer();
            break;
        case 'I': inventorySystem(*myPlayer);
            break;
        case 'A': armorShop(*myPlayer);
            break;
        case 'E': printEnemyCatalogue(enemies);
            break;
        case 'Q': LeavingGame = true;
            break;
        default:
            cout << "Error! Try again!\n";
            break;
        }


    }
}