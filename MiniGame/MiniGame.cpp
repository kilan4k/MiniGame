#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
using std::cout, std::cin, std::string, std::endl, std::vector;



std::string toLowerString(std::string str);
void printPlayerStats(const Player& player);
void printEnemyCatalogue(const vector<Enemy>& enemies);
void printWeaponCatalogue(const vector<Weapon>& weapons);
Player* playerCreation(vector<Weapon>& weapons, vector<Player>& playerTypes);

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

int main()
{
    srand(time(0));
    
    //Declaring different objects
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
    Weapon fists = Weapon("Fists", 10, 20, 5, 0, 0, true); //0
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
    empty.name = "New character"; 
    Player bandit = Player(1, 50, &weapons[KNIFE], 0);
    bandit.name = "Bandit";
    Player punchman = Player(1, 0, &weapons[FISTS], 1);
    punchman.name = "Punchman";
    Player archer = Player(1, 0, &weapons[BOW], 0);
    archer.name = "Archer";
    Player lvlPunchman = Player(10, 50, &weapons[FISTS], 0);
    lvlPunchman.name = "Leveled up Punchman";
    Player lumberjack = Player(1, 0, &weapons[AXE], 0);
    lumberjack.name = "Lumberjack";
    Player robber = Player(1, 100, &weapons[FISTS], 0);
    robber.name = "Robber";

    vector<Player> players = { empty, bandit, punchman, archer, lvlPunchman, lumberjack, robber};

    Player* myPlayer = playerCreation(weapons,players);

    printPlayerStats(*myPlayer);
    pCurrentEnemy = new Enemy(zombie);
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
 
    
    

    //printEnemyCatalogue(enemies);
    //printWeaponCatalogue(weapons);
    //printPlayerStats(*myPlayer);
    //*myPlayer->currentWeapon = deadlystf;
    cin.get();
    
    //delete myPlayer;
    return 0;
}





Player* playerCreation( vector<Weapon>& weapons, vector<Player>& playerTypes) {// creating player's character
    cout << "======= WELCOME TO CHARACTER CREATOR ======\n"; 
    bool hasChosen = false;
    char choice ;
    string cName;
    string nickname;
    while (!hasChosen) { //we'll be asking everytime till user chooses a character

    cout << "You can choose any of these characters: \n\n";
   for (const auto& character : playerTypes) { // showing every character
        cout << character.name<<"\n"; 
    }
   cout << "\nEnter '1' to choose a character\nEnter '2' to show stats for each character\n";
   cin >> choice;
   switch (choice) {
    case '1':
        cout << "======Which of available characters you would like to choose?======\nEnter its name: ";
        std::getline(cin >> std::ws, cName);
        for (const auto& character : playerTypes) {
            if (toLowerString(character.name) == toLowerString(cName)) { // checking if user's input equals any name of a character
                hasChosen = true;
                cout << "\nExcellent choice!\n\n======You have successfully chosen a character called " << character.name << ".======\n\nNow enter your nickname: ";
                std::getline(cin>>std::ws, nickname);
                
                cout << "Welcome to this dangerous world, " << nickname << " and I wish you good luck on this journey!\n\n";
                Player* newPlayer = new Player(character.level, character.money, character.currentWeapon, character.armor);
                newPlayer->name= nickname;
                return newPlayer;
                break;
            }
            
        }
        if (!hasChosen) {
            cout << "\nError! Try again.\n"; // Error in case user inputs some dumb stuff
        }
        break;
    case '2':
        for (const auto& character : playerTypes) {
            printPlayerStats(character);// if user asks to show stats we show him stats for every character
        }
        break;
    default:
        cout << "\nError! Try again.\n";
        break;
   }
    
    }
    return nullptr;
}
std::string toLowerString(std::string str) {
    for (char& c : str) {
        c = std::tolower(static_cast<unsigned char>(c)); // for loop to turn string into a lowercase string obv
    }
    return str;
}
void printEnemyCatalogue(const vector<Enemy>& enemies) { // Printing every enemy in game just so that user knows what to deal with
    cout << "\n\n\n============= ENEMIES MANUAL ==============\n";
    for (const auto& enemy : enemies) {
        cout << "\n-------------------------------------------\n";
        cout << "| " << enemy.name << ":\n";
        cout << "| HP: " << enemy.maxHp << "\n";
        cout << "| Basic damage: " << enemy.minDamage<<"-"<<enemy.maxDamage << "\n";
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
        cout<<"| Basic damage: " << weapon.minDamage << "-" << weapon.maxDamage<<"\n";
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
void printPlayerStats(const Player& player) { // Printing character or player stats 
    cout << "\n\n\n============= CHARACTER STATS =============\n";
    cout << "\n-------------------------------------------\n";
    cout << "| " << player.name << ":\n";
    cout << "| HP: " << 90 + player.level * 10 << "\n";
    cout << "| Level: " << player.level << "\n";
    cout << "| Weapon: " << player.currentWeapon->name<< "\n";
    cout << "| Damage: " << player.getMinDamage()<<"-"<<player.getMaxDamage() << "\n";
    cout << "| Armor class: " << player.armor<< "\n";
    cout << "| Money: " << player.money<< "\n";
    cout << "| XP: " << player.playerXp<< "\n";
    cout << "| XP left for next level: " << player.xpToNextLvl;
    cout << "\n-------------------------------------------\n\n\n";

}