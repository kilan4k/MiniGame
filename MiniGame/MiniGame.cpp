#include "Enemy.h"
#include "Weapon.h"
#include "functions.h"
#include "Player.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl, std::vector;

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
int main()
{ 
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

    vector<Enemy> enemies = {rat, spider, rogue, skeleton, zombie, goblin, barbarian, bear, juggernaut, knight, dragon, demon};

    //Weapon types
    Weapon fists = Weapon("Fists", 10, 20, 5, 0, 0, false); //0
    Weapon knife = Weapon("Knife", 20, 30, 5, 25, 1, false);//1
    Weapon machete = Weapon("Machete", 25,35,10,85,6,false);//2
    Weapon axe = Weapon("Axe", 35,45,35,150,7,false);//3
    Weapon hammer = Weapon("Hammer", 20, 40, 33, 95, 7, false);//4
    Weapon sword = Weapon("Sword", 40, 55, 25, 200, 10, false);//5
    Weapon bow = Weapon("Bow", 25, 60, 65, 250, 15, false);//6
    Weapon katana = Weapon("Katana", 50, 75, 50, 400, 20, false);//7
    Weapon shotgun = Weapon("Shotgun", 30, 90, 1, 600, 25, false);//8
    Weapon firestf= Weapon("Fire staff", 50, 70, 50, 750, 25, false);//9
    Weapon lightsaber = Weapon("Light Saber", 67, 80, 25, 800, 25, false);//10
    Weapon deadlystf= Weapon("Deadly staff", 50, 200, 67, 1500, 50, false);//11

    vector<Weapon> weapons = { fists, knife, machete, axe, hammer, sword, bow, katana, shotgun, firestf, lightsaber, deadlystf};

    //Player types (and declaring names beneath cus i'm a lazy man to edit a constructor but it ain't a big deal ig)
    Player empty = Player(1, 0, &weapons[FISTS], 0);
    empty.setName("New character");
    Player bandit = Player(1, 50, &weapons[KNIFE], 0);
    bandit.setName("Bandit");
    Player punchman = Player(1, 0, &weapons[FISTS], 1);
    punchman.setName("Punchman");
    Player archer = Player(1, 0, &weapons[BOW], 0);
    archer.setName("Archer");
    Player lvlPunchman = Player(10, 50, &weapons[FISTS], 0);
    lvlPunchman.setName("Leveled up Punchman");
    Player lumberjack = Player(1, 0, &weapons[AXE], 0);
    lumberjack.setName("Lumberjack");
    Player robber = Player(1, 100, &weapons[FISTS], 0);
    robber.setName("Robber");

    vector<Player> players = { empty, bandit, punchman, archer, lvlPunchman, lumberjack, robber};

    //Player and Enemy defining
    Player* myPlayer = nullptr;
    //Enemy* pCurrentEnemy = nullptr;

    //Game loop
    gamePlaying(myPlayer, enemies, weapons, players);

    /*
    myPlayer->money += 100;
    myPlayer->AddXp(5000);
    while(myPlayer->hp>0){
    battleSystem(*myPlayer, pCurrentEnemy, enemies);
    openShop(*myPlayer, weapons);
    printPlayerStats(*myPlayer);
    myPlayer->HealPlayer();
    }
    */
    /*
    myPlayer->money = 200;
    
    printPlayerStats(*myPlayer);
  
    pCurrentEnemy = new Enemy(zombie);
    pCurrentEnemy->Attack(*myPlayer);
    myPlayer->AddXp(250);
    myPlayer->HealPlayer();
    printPlayerStats(*myPlayer);
    */
    /*
    while (myPlayer != nullptr && pCurrentEnemy != nullptr &&(pCurrentEnemy->isAlive() and myPlayer->isAlive())) {
        
        myPlayer->Attack(*pCurrentEnemy);
        if (!pCurrentEnemy->isAlive()) {
            std::cout << pCurrentEnemy->name << " is dead.\n";        
            break;
        }
        pCurrentEnemy->Attack(*myPlayer);
        if (!myPlayer->isAlive()) {
            std::cout << myPlayer->name << " is dead.\n";
            break;
        }        
    }
    if (!myPlayer->isAlive()) delete myPlayer;
    if (!pCurrentEnemy->isAlive()) delete pCurrentEnemy;
 */    
    //openShop(*myPlayer, weapons);
    //printPlayerStats(*myPlayer);
    //printEnemyCatalogue(enemies);
    //printWeaponCatalogue(weapons);
    //printPlayerStats(*myPlayer);
    //*myPlayer->currentWeapon = deadlystf;
    cout << "\n[GAME ENDS]\n\n";
    clearInput();
    cin.get();
    if (myPlayer != nullptr) delete myPlayer;
    return 0;
}
//END OF MAIN



