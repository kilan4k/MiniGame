#include "Enemy.h"
#include "Player.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
using std::cout, std::cin, std::string, std::endl;




void playerCreation(Player& myPlayer);
int main()
{
    srand(time(0));

    Player myPlayer = Player(100, 20, 50, 25, 2);
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

    
    int experienceAddTest = 10;
    while (true) {
        std::cin.get();
        cout <<"My player hp: " << myPlayer.hp << "\n";
        cout << "My player xp: " << myPlayer.playerXp<< "\n; My player lvl: "<<myPlayer.level<<"\n; My player left xp for next level: "<<myPlayer.xpToNextLvl;
        experienceAddTest *= 3;
        myPlayer.AddXp(experienceAddTest);
    }
    

    return 0;
}




//idea: 
//I have a class of player and Enemy.
//Player should have HP, MaxHP, minDMG,maxDMG(so theres random dmg), critChance(+50%dmg),Money, Level, and maybe something else 
//Enemy should have HP, maxHP, minDMG,maxDMG, Armor, Money (when u kill him u get money)
//First when starting program there should be starting screen, choose a weapon, go to shop or go battle, when u go battle u can meet a random enemy (their stats should increase in % with bigger player's level
//Then when battle starts theres 50% chance of either u attack first or enemy, after both attack u can either continue fight or leave
//if u lose, program closes, if u win u get money from enemy and then u can go shopping, healing or continue battling.
//maybe i'll add something as well I just can't think of it now
//Each class of Armor should decrease incoming damage by 20%. max Armor is 4
void playerCreation(Player& myPlayer) {



}
