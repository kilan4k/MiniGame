#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <ctime>
using std::cout, std::cin, std::string, std::endl;




void playerCreation(Player& myPlayer);
int main()
{
    
    srand(time(0));
    Player myPlayer = Player(100, 100, 100, 50, 0);
    while (true) {
        std::cin.get();
        cout<<myPlayer.TakeDamage(myPlayer.CalculateDamage())<<"\n";
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
