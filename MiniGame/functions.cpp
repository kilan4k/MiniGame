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
    cout << "\n\n==================================================\n";
    cout << "                    BATTLE MENU";
    cout << "\n==================================================\n";
    char choice;
    const int fleeingChance = 75;
    bool fleeing = false;
    bool isLeaving = false;
    bool choiceMade = false;

    while (!choiceMade) {
        cout << "\n-------------------------------------------\n";
        cout << "Type 'Y' if you agree to fight;\nType 'N' if you want to escape;\nType 'R' to show battle rules:\n";
        cout << "-------------------------------------------\n";
        cin >> choice;
        clearInput();
        switch (toupper(choice)) {
        case 'Y':
            choiceMade = true;
            break;
        case 'N':
            cout << "Leaving this menu...";
            choiceMade = true;
            isLeaving = true;
            cout << "\n-------------------------------------------\n\n\n";
            return;
        case 'R':
            cout << "\n\n-------------------------------------------\n";
            cout << "Battle rules:\n";
            cout << "Every turn player and enemy attack each other only one time\nPlayer attacks enemy first, then enemy attacks.\nit only works otherwise if you try to flee away and fails.\nFlee chance = " << fleeingChance << "%";
            break;
        default:
            cout << "Error! Try again!";
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
            //cout << randChecking;
            if (randChecking <= fleeingChance) {
                cout << "\nYou've successfully fleed the battle!\n";
                isLeaving = true;
                break;
            }
            else {
                cout << "\nYou failed to flee! Now " << enemy->name << " will attack you first!\n";
                fleeing = false;
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
            cout << "-------------------------------------------\n";
            cout << "Type 'Y' if you want to continue the fight\nType 'N' if you want to try to flee with " << fleeingChance << "% chance\n";
            cout << "-------------------------------------------\n";
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
        cout << "YOU DIED\n";
        cout << player.name << " was defeated.\n\n";

    }
    if (enemy != nullptr) {
        if (enemy->hp <= 0) {
            cout << "YOU WON\n";
            cout << enemy->name << " was defeated.\n\n";
            cout << "You get " << enemy->xpReward << "xp\nYou get " << enemy->money << "$\n";
            player.money += (enemy->money)*(player.level*7+100)/100;
            player.AddXp((enemy->xpReward)*(player.level*5+100)/100);
            player.kills++;
            delete enemy;
            enemy = nullptr;
        }
        else {
            delete enemy;
            enemy = nullptr;
        }
    }
    cout << "\n-------------------------------------------\n\n\n";
}
void openShop(Player& player, vector<Weapon>& weapons) {
    cout << "\n\n\n==================================================\n";
    cout <<       "                     WEAPON SHOP";
    cout <<     "\n==================================================\n";
    string choice;
    int numChoice;
    bool isLeaving = false;
    cout << "Welcome to the shop, here you can examine every weapons' statistics or buy new weapon\n";
    while (!isLeaving) {
        cout << "-------------------------------------------\n";
        cout << "Type '1' to show weapon list and therefore buy a weapon;\nType '2' to show stats for every weapon;\nType '-1' to leave the shop\n";
        cout << "-------------------------------------------\n";
        cin >> numChoice;
        clearInput();
        switch (numChoice) {
        case 1:
        {
            int i = 1;
            cout << "\n-------------------------------------------\n";
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
            cout << "-------------------------------------------\n";
        }
        cout << "\n-------------------------------------------\n";
        cout << "!Before buying a weapon make sure you have enough money and level!\n";
        cout << "To buy a weapon, type its number or its name: ";
        std::getline(cin >> std::ws, choice);
        cout << "-------------------------------------------\n";
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
    cout << "\n==================================================\n";
    cout <<     "           WELCOME TO CHARACTER CREATOR";
    cout <<   "\n==================================================\n";
    bool hasChosen = false;
    char choice;
    string cName;
    string nickname;
    while (!hasChosen) { //we'll be asking everytime till user chooses a character

        cout << "You can choose any of these characters: \n\n";
        {
            cout << "-------------------------------------------\n";
            int i = 1;
            for (const auto& character : playerTypes) { // showing every character
                cout << i++ << ". " << character.name << "\n";
            }
            cout << "-------------------------------------------\n";
        }

        cout << "\nEnter '1' to choose a character\nEnter '2' to show stats for each character\n";
        cin >> choice;
        clearInput();
        switch (choice) {
        case '1':
            cout << "\n--------------------------------------------------\n";
            cout << "Which of available characters you would like to choose?";
            cout << "\n--------------------------------------------------\n";
            cout<<"\nEnter its name or its number: ";
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
    cout << "\n\n\n==================================================\n";
    cout <<       "                   ENEMIES MANUAL";
    cout <<     "\n==================================================\n";
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
        cout << "\n\n\n==================================================\n";
        cout <<       "                    WEAPON STATS";
        cout <<     "\n==================================================\n";
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
    cout << "\n-------------------------------------------\n\n\n";
}
void printPlayerStats(const Player& player) { // Printing character or player stats 
    cout << "\n\n\n==================================================\n";
    cout <<       "                CHARACTER STATS";
    cout <<     "\n==================================================\n";
    cout << "\n-------------------------------------------\n";
    cout << "| " << player.name << ":\n";
    cout << "| Current HP: " << player.hp << "\n";
    cout << "| Max HP: " << player.maxHp << "\n";
    cout << "| Level: " << player.level << "\n";
    cout << "| Equipped Weapon: " << player.currentWeapon->name << "\n";
    cout << "| Damage: " << player.getMinDamage() << "-" << player.getMaxDamage() << "\n";
    cout << "| Kills: "<< player.kills<<"\n";
    cout << "| Armor class: " << player.armor << "\n";
    cout << "| Money: " << player.money << "\n";
    cout << "| XP: " << player.playerXp << "\n";
    cout << "| XP left for next level: " << player.xpToNextLvl;
    cout << "\n-------------------------------------------\n\n";

}
int getRandomNumber(int num1, int num2) {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(num1, num2);
    int randNum = dist(gen);
    return randNum;
}
void gamePlaying(Player*& player, Enemy*& enemy, std::vector<Enemy>& enemies, std::vector<Weapon>& weapons, std::vector<Player> players) {
    player = playerCreation(weapons, players);
    cout << "[BONUS FOR PLAYING ALPHA]\n";
    cout << "Adding 100$\n";
    player->money += 100;
    bool LeavingGame = false;
    while (!LeavingGame ) {
        if (player->hp <= 0) { LeavingGame = true; break; }

        {
            cout << "\n\n==================================================\n";
            cout << "                    GAME MENU";
            cout <<   "\n==================================================\n";
        }//console output
        char choice;
        cout << "\n-------------------------------------------\n";
        cout << "Type '1' to battle\nType '2' to open shop menu\nType 'S' to print player's stats\nType 'H' to open heal menu\nType 'A' to open armor shop\nType 'E' to show every enemy stat in game\nType 'Q' to quit the game";
        cout << "\n-------------------------------------------\n";
        cin >> choice;
        clearInput();
        //cout << toupper(choice);
        switch (toupper(choice) ) {
        case '1': battleSystem(*player, enemy, enemies);
            break;
        case '2': openShop(*player, weapons);
            break;
        case 'S': printPlayerStats(*player);
            break;
        case 'H': player->HealPlayer();
            break;
        case 'A': armorShop(*player);
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
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void armorShop(Player& player) {
    cout << "\n\n==================================================\n";
    cout <<     "                     ARMOR SHOP";
    cout <<   "\n==================================================\n\n";
    cout << "\n-------------------------------------------\n";
    bool isLeaving = false;
    char choice;
    while (!isLeaving) {
        cout << "Your current Armor class is " << player.armor << "\n";
        if (player.armor > 0) {
            cout << "Your armor reflects " << armorClassFormula(player.armor) * 100 << "% damage\n";
        }
        if (player.armor < 4) {
            cout << "To buy " << player.armor + 1 << " armor class you have to spend " << player.getArmorPrice(player.armor + 1) << "$ and it will reflect " << armorClassFormula(player.armor + 1) * 100 << "% damage\n";
            if (player.getArmorPrice(player.armor + 1) > player.money) {
                cout << "You have not enough money to buy " << player.armor + 1 << " armor class!\n";
                isLeaving = true;
                continue;
            }
        }
        else {
            cout << "You own max level of armor! It deflects " << armorClassFormula(player.armor) * 100 << "% damage\n";
            isLeaving = true;
            continue;
        }
        cout << "Type 'Y' if you want to buy next armor class\nType 'N' if you don't want to buy next armor class\n";
        cout << "-------------------------------------------\n";
        cin >> choice;
        clearInput();
        switch (toupper(choice)) {
        case 'Y':
            player.armor++;
            player.money -= player.getArmorPrice(player.armor);
            cout << "You successfully bought " << player.armor << " class for " << player.getArmorPrice(player.armor) << "$\n";
            break;
        case 'N':
            isLeaving = true;
            continue;
            break;
        default:
            cout << "Error! Try again\n";
            break;
        }
    }
    cout << "-------------------------------------------\n\n\n";
}
double armorClassFormula(short armor) {
    return static_cast<double>(armor) / 5.0;
}
