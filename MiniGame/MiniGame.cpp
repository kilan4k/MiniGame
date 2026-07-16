#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
using std::cout, std::cin, std::string, std::endl, std::vector;


void printEnemyCatalogue(const vector<Enemy>& enemies);
void printWeaponCatalogue(const vector<Weapon>& weapons);
void playerCreation(Player& myPlayer);
int main()
{
    srand(time(0));

    //Player myPlayer;

    //Enemy types
    Enemy* pCurrentEnemy;
    Enemy rat = Enemy("Rat", 25, 5, 10, 10, 0, 5, 10);
    Enemy spider = Enemy("Spider", 50, 15, 25, 50, 0, 10, 20);
    Enemy rogue = Enemy("Rogue", 75, 25, 35, 15, 0, 10, 20);
    Enemy skeleton = Enemy("Skeleton", 75, 20, 30, 60, 0, 15, 30);
    Enemy zombie = Enemy("Zombie", 100, 20, 30, 15, 1, 15, 30);
    Enemy goblin = Enemy("Goblin", 75, 30, 40, 10, 0, 25, 30);
    Enemy barbarian = Enemy("Barbarian", 100, 20, 40, 5, 1, 30, 50);
    Enemy bear = Enemy("Bear", 75, 40, 70, 25, 2, 55, 75);
    Enemy juggernaut = Enemy("Juggernaut", 250, 15, 20, 10, 3, 50, 100);
    Enemy knight = Enemy("Knight", 150, 40, 65, 25, 2, 75, 100);
    Enemy dragon = Enemy("Dragon", 300, 30, 60, 35, 1, 100, 120);
    Enemy demon = Enemy("Demon", 400, 60, 100, 40, 1, 120, 200);

    vector<Enemy> enemies = {rat, spider, rogue, skeleton, zombie, goblin, barbarian, bear, juggernaut, knight, dragon, demon};

    //Weapon types
    Weapon fists = Weapon("Fists", 10, 20, 5, 0, 0, true);
    Weapon knife = Weapon("Knife", 20, 30, 5, 25, 1, false);
    Weapon machete = Weapon("Machete", 25,35,10,35,4,false);
    
    vector<Weapon> weapons = { fists, knife, machete };



    int experienceAddTest = 10;
    /*
    while (true) {
        cout << "\n";
        std::cin.get();
        cout <<"My player hp: " << myPlayer.hp << "\n";
        cout << "My player xp: " << myPlayer.playerXp<< "\n; My player lvl: "<<myPlayer.level<<"\n; My player left xp for next level: "<<myPlayer.xpToNextLvl<<"\n";
        experienceAddTest *= 3;
        myPlayer.AddXp(experienceAddTest);
    }*/
    printEnemyCatalogue(enemies);
    printWeaponCatalogue(weapons);

    return 0;
}





void playerCreation(Player& myPlayer) {



}
void printEnemyCatalogue(const vector<Enemy>& enemies) { // Printing every enemy in game just so that user knows what to deal with
    cout << "\n\n\n============= ENEMIES MANUAL ==============\n";
    for (const auto& enemy : enemies) {
        cout << "\n-------------------------------------------\n";
        cout << "| " << enemy.name << ":\n";
        cout << "| HP: " << enemy.maxHp << "\n";
        cout << "| Damage: " << enemy.minDamage<<"-"<<enemy.maxDamage << "\n";
        cout << "| Critical damage chance: " << enemy.critChance<< "%\n";
        cout << "| Armor class: " << enemy.armor<< "\n";
        cout << "| Money drop: " << enemy.money<< "$\n";
        cout << "| EXP drop: " << enemy.xpReward;
    }
    cout << "\n-------------------------------------------\n\n\n";
}
void printWeaponCatalogue(const vector<Weapon>& weapons) { // Printing Weapon catalogue which may also be used as a shop
    cout << "\n\n\n=============== WEAPON SHOP ===============\n";
    for (const auto& weapon : weapons) {
        cout << "\n-------------------------------------------\n";
        cout << "| " << weapon.name<<":\n";
        cout<<"| Damage: " << weapon.minDamage << "-" << weapon.maxDamage<<"\n";
        cout << "| Critical damage chance: " << weapon.critChance << "%\n";
        cout << "| Price: " << weapon.price << "$\n";
        cout << "| Available on player level: " << weapon.lvlReq<< "\n";
        if (weapon.isBought) {
            cout << "| You own this weapon";
        }
        else {
            cout << "| You don't own this weapon";
        }

    }
    cout << "\n-------------------------------------------\n\n\n";
}
