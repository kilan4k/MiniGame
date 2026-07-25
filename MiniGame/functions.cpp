#include "functions.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>

#include <random>

using std::cout, std::cin, std::string, std::endl, std::vector;
Enemy* getRandomEnemy(vector<Enemy>& enemies) {

    int randDifficulty = getRandomNumber(1, 100);

    const int randEasy = 70;
    const int randMed = 90;
    const int randHard = 100;
    int easyEnemies = 5;
    int mediumEnemies = 8;
    int hardEnemies = 11;
    if (randDifficulty <= randEasy) {
        //cout << "EASY ";
        //cout << randDifficulty << "\n";
        int enemyNum = getRandomNumber(0,easyEnemies);
        return new Enemy(enemies[enemyNum]);
    }
    else if (randDifficulty <= randMed) {
        //cout << "MEDIUM ";
        //cout << randDifficulty << "\n";
        int enemyNum = getRandomNumber(easyEnemies+1,mediumEnemies);
        return new Enemy(enemies[enemyNum]);

    }
    else {
        //cout << "HARD ";
        //cout << randDifficulty<<"\n";
        
        int enemyNum = getRandomNumber(mediumEnemies+1,hardEnemies);
        return new Enemy(enemies[enemyNum]);
    }

}
void battleSystem(Player& player, Enemy*& enemy, vector<Enemy>& enemies) {
    cout << "\n\n=============== BATTLE MENU ===============\n\n";
    char choice;
    int numChoice;
    const int fleeingChance = 75;
    bool fleeing = false;
    bool isLeaving = false;
    bool choiceMade = false;




    while (!choiceMade) {
        cout << "\n-------------------------------------------\n";
        cout << "Type 'Y' if you agree to fight;\nType 'N' if you want to escape;\nType 'R' to show battle rules:\n";
        cin >> choice;
        clearInput();
        switch (toupper(choice)) {
        case 'Y':
            choiceMade = true;
            break;
        case 'N':
            cout << "Leaving this menu...\n";
            choiceMade = true;
            isLeaving = true;
            cout << "\n-------------------------------------------\n\n\n";
            return;
        case 'R':
            cout << "\n-------------------------------------------\n";
            cout << "Battle rules:\n";
            cout << "Every turn player and enemy attack each other only one time\nPlayer attacks enemy first, then enemy attacks.\nit only works otherwise if you try to flee away and fails.\nFlee chance = " << fleeingChance << "%\n";
            break;
        default:
            cout << "Error! Try again!\n";
            break;
        }
    }
    cout << "-------------------------------------------\n";
    enemy = getRandomEnemy(enemies);
    cout << "\nYour enemy is " << enemy->name << "\n";
    while (!isLeaving) {
        choice = ' ';
        choiceMade = false;
        if (fleeing) {

            int randChecking = getRandomNumber(1, 100);
            if (randChecking <= fleeingChance) {
                cout << "\nYou've successfully fleed the battle!\n";
                delete enemy;
                isLeaving = true;
                break;
            }
            else {
                cout << "\nYou failed to flee! Now " << enemy->name << " will attack you first!\n";
                enemy->Attack(player);
                player.Attack(*enemy);
            }
        }
        else {
            player.Attack(*enemy);
            enemy->Attack(player);
        }
        if (player.hp <= 0) {
            isLeaving = true;
            break;
        }
        if (enemy->hp <= 0) {
            isLeaving = true;
            break;
        }
        while (!choiceMade) {
            cout << "\nType 'Y' if you want to continue the fight\nType 'N' if you want to try to flee with " << fleeingChance << "% chance:\n";
            cin >> choice;
            clearInput();
            if (toupper(choice) == 'Y') {
                choiceMade = true;
                continue;
            }
            else if (toupper(choice) == 'N') {
                fleeing = true;
                choiceMade = true;
                continue;
            }
            else {
                cout << "Error! Wrong input!\n";
            }
        }

    }
    if (player.hp <= 0) {
        cout << "!!!You died!!!\n";
        cout << player.name << " was defeated.\n\n";

    }
    if (enemy->hp <= 0) {
        cout << "!!!You won!!!\n";
        cout << enemy->name << " was defeated.\n\n";
        player.money += enemy->money;
        player.AddXp(enemy->xpReward);
        cout << "You get " << enemy->xpReward << "xp\nYou get " << enemy->money << "$\n";
        delete enemy;
    }
    cout << "\n-------------------------------------------\n\n\n";
}
void openShop(Player& player, vector<Weapon>& weapons) {
    cout << "\n\n\n=============== WEAPON SHOP ===============\n";
    string choice;
    int numChoice;
    bool isLeaving = false;
    cout << "Welcome to the shop, here you can examine every weapons' statistics or buy new weapon\n";
    while (!isLeaving) {

        cout << "Type '1' to show weapon list and therefore buy a weapon;\nType '2' to show stats for every weapon;\nType '-1' to leave the shop\n";
        cin >> numChoice;
        clearInput();
        switch (numChoice) {
        case 1:
        {
            int i = 1;
            for (const auto& weapon : weapons) {
                cout << i++ << ". " << weapon.name;
                if (!weapon.isBought) {
                    cout << "; Price: " << weapon.price << "; Level required: " << weapon.lvlReq << "; Can buy - " << ((player.level >= weapon.lvlReq && player.money >= weapon.price) ? "Yes" : "No");
                }
                else {
                    cout << "; You own this weapon!";
                }
                cout << "\n";
            }
        }
        cout << "\n!Before buying a weapon make sure you have enough money and level!\n";
        cout << "To buy a weapon, type its number or its name:\n";
        std::getline(cin >> std::ws, choice);
        {
            bool found = false;
            int i = 1;

            for (auto& weapon : weapons) {
                string indexStr = std::to_string(i++);
                if ((toLowerString(choice) == toLowerString(weapon.name) || indexStr == choice)) {
                    found = true;
                    if (weapon.isBought) {
                        cout << "You already own " << weapon.name << "!\nDo you want to equip it? 'Y' for yes, 'N' for no:\n";
                        std::getline(cin >> std::ws, choice);
                        if (toLowerString(choice) == "y") {
                            player.currentWeapon = &weapon;
                            cout << "Successfully equipped " << weapon.name << "!\n";
                        }
                        break;
                    }
                    if (player.money >= weapon.price) {
                        if (player.level >= weapon.lvlReq) {
                            cout << "You have enough money to buy " << weapon.name << ". Type 'Y' if you want to buy it; Type 'N' if you don't want to buy it\n";
                            std::getline(cin >> std::ws, choice);
                            if (toLowerString(choice) == "y") {
                                weapon.isBought = true;
                                player.money -= weapon.price;
                                player.currentWeapon = &weapon;
                                cout << "Successfully bought " << weapon.name << " for " << weapon.price << "$\nThis weapon is now equipped. (if you want to change equipped weapon, go to inventory from menu)\n";
                                break;
                            }
                            else if (toLowerString(choice) == "n") {
                                break;
                            }
                            else {
                                cout << "Error! Try again!\n\n";
                                break;
                            }
                        }
                        else {
                            cout << "Your level is not enough to buy " << weapon.name << "!\n";
                        }
                    }
                    else {
                        cout << "You have not enough money to buy " << weapon.name << "!\n";
                    }
                }
            }
            if (!found) cout << "ERROR! Weapon is not found!\n";
        }
        break;
        case 2: printWeaponCatalogue(weapons);
            break;
        case -1:
            isLeaving = true;
            break;
        default:cout << "Error! Try again\n";
            break;

        }
    }

    cout << "\n-------------------------------------------\n\n\n";
}
Player* playerCreation(vector<Weapon>& weapons, vector<Player>& playerTypes) {// creating player's character
    cout << "======= WELCOME TO CHARACTER CREATOR ======\n";
    bool hasChosen = false;
    char choice;
    string cName;
    string nickname;
    while (!hasChosen) { //we'll be asking everytime till user chooses a character

        cout << "You can choose any of these characters: \n\n";
        {
            int i = 1;
            for (const auto& character : playerTypes) { // showing every character
                cout << i++ << ". " << character.name << "\n";
            }
        }

        cout << "\nEnter '1' to choose a character\nEnter '2' to show stats for each character\n";
        cin >> choice;
        switch (choice) {
        case '1':
            cout << "======Which of available characters you would like to choose?======\nEnter its name or its number: ";
            std::getline(cin >> std::ws, cName);
            {
                int i = 1;
                for (const auto& character : playerTypes) {
                    string indexStr = std::to_string(i++);
                    if ((toLowerString(character.name) == toLowerString(cName)) || (indexStr == cName)) { // checking if user's input equals any name of a character
                        hasChosen = true;
                        cout << "\nExcellent choice!\n\n======You have successfully chosen a character called " << character.name << ".======\n\nNow enter your nickname: ";
                        std::getline(cin >> std::ws, nickname);

                        cout << "Welcome to this dangerous world, " << nickname << " and I wish you good luck on this journey!\n\n";
                        Player* newPlayer = new Player(character.level, character.money, character.currentWeapon, character.armor);
                        newPlayer->name = nickname;
                        newPlayer->currentWeapon->isBought = true;
                        std::cout << "-------------------------------------------\n";
                        return newPlayer;
                        break;
                    }

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
    std::cout << "-------------------------------------------\n";
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
    {
        int i = 1;
        for (const auto& enemy : enemies) {
            cout << "\n-------------------------------------------\n";
            cout << "| " << i++ << ". " << enemy.name << ":\n";
            cout << "| HP: " << enemy.maxHp << "\n";
            cout << "| Basic damage: " << enemy.minDamage << "-" << enemy.maxDamage << "\n";
            cout << "| Critical damage chance: " << enemy.critChance << "%\n";
            cout << "| Armor class: " << enemy.armor << "\n";
            cout << "| Money drop: " << enemy.money << "$\n";
            cout << "| EXP drop: " << enemy.xpReward;
        }
    }
    cout << "\n-------------------------------------------\n\n\n";
}
void printWeaponCatalogue(const vector<Weapon>& weapons) { // Printing Weapon catalogue which may also be used as a shop
    {
        cout << "\nWeapon Stats:\n";
        int i = 1;
        for (const auto& weapon : weapons) {
            cout << "\n-------------------------------------------\n";
            cout << "| " << i++ << ". " << weapon.name << ":\n";
            cout << "| Basic damage: " << weapon.minDamage << "-" << weapon.maxDamage << "\n";
            cout << "| Critical damage chance: " << weapon.critChance << "%\n";
            cout << "| Price: " << weapon.price << "$\n";
            cout << "| Available on player level: " << weapon.lvlReq << "\n";
            if (weapon.isBought) {
                cout << "| You own this weapon";
            }
            else {
                cout << "| You don't own this weapon";
            }

        }
    }
    cout << "\n-------------------------------------------\n\n";
}
void printPlayerStats(const Player& player) { // Printing character or player stats 
    cout << "\n\n\n============= CHARACTER STATS =============\n";
    cout << "\n-------------------------------------------\n";
    cout << "| " << player.name << ":\n";
    cout << "| Current HP: " << player.hp << "\n";
    cout << "| Max HP: " << player.maxHp << "\n";
    cout << "| Level: " << player.level << "\n";
    cout << "| Equipped Weapon: " << player.currentWeapon->name << "\n";
    cout << "| Damage: " << player.getMinDamage() << "-" << player.getMaxDamage() << "\n";
    cout << "| Armor class: " << player.armor << "\n";
    cout << "| Money: " << player.money << "\n";
    cout << "| XP: " << player.playerXp << "\n";
    cout << "| XP left for next level: " << player.xpToNextLvl;
    cout << "\n-------------------------------------------\n\n\n";

}
int getRandomNumber(int num1, int num2) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(num1, num2);
    int randNum = dist(gen);
    return randNum;
}
