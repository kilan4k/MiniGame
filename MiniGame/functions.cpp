#include "functions.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <random>
#include <limits>
#include <utility>


using std::cout, std::cin, std::string, std::endl, std::vector;

void gamePlaying(Player*& player, Enemy*& enemy, std::vector<Enemy>& enemies, std::vector<Weapon>& weapons, const std::vector<Player> players) {
    player = playerCreation(weapons, players);
    cout << "[BONUS FOR PLAYING ALPHA]\n";
    cout << "Adding 100$\n";
    player->addMoney(100);
    bool LeavingGame = false;
    while (!LeavingGame ) {
        if (player->getHp()<= 0) { LeavingGame = true; break; }

        {
            cout << "\n\n==================================================\n";
            cout << "                    GAME MENU";
            cout <<   "\n==================================================\n";
        }//console output
        char choice;
        cout << "\n-------------------------------------------\n";
        cout << "Type '1' to battle\nType '2' to open shop menu\nType 'S' to print player's stats\nType 'H' to open heal menu\nType 'I' to open inventory\nType 'A' to open armor shop\nType 'E' to show every enemy stat in game\nType 'Q' to quit the game";
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
        case 'I': inventorySystem(*player);
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
    cout << "\nYour enemy is " << enemy->getName() << "\n";
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
                cout << "\nYou failed to flee! Now " << enemy->getName() << " will attack you first!\n";
                fleeing = false;
                enemy->Attack(player);
                player.Attack(*enemy);
            }
        }
        else {
            player.Attack(*enemy);
            enemy->Attack(player);
        }
        if (player.getHp() <= 0) {
            isLeaving = true;
            break;
        }
        if (enemy->getHp() <= 0) {
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
    if (player.getHp()<= 0) {
        cout << "YOU DIED\n";
        cout << player.getName() << " was defeated.\n\n";

    }
    if (enemy != nullptr) {
        if (enemy->getHp() <= 0) {
            cout << "YOU WON\n";
            cout << enemy->getName()<< " was defeated.\n\n";
            cout << "You get " << enemy->getXpReward() << "xp\nYou get " << enemy->getMoney() << "$\n";
            player.addMoney((enemy->getMoney()) * (player.getLevel() * 7 + 100) / 100) ;
            player.AddXp((enemy->getXpReward()) * (player.getLevel() * 5 + 100) / 100);
            player.addKills(1);
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
Player* playerCreation(vector<Weapon>& weapons, const vector<Player>& playerTypes) {// creating player's character
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
                cout << i++ << ". " << character.getName() << "\n";
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
                    if ((toLowerString(character.getName()) == toLowerString(cName)) || (indexStr == cName)) { // checking if user's input equals any name of a character
                        hasChosen = true;
                        cout << "\nExcellent choice!\n\n======You have successfully chosen a character called " << character.getName() << ".======\n\nNow enter your nickname: ";
                        std::getline(cin >> std::ws, nickname);

                        cout << "Welcome to this dangerous world, " << nickname << " and I wish you good luck on this journey!\n\n";
                        Player* newPlayer = new Player(character.getLevel(), character.getMoney(), character.getCurrentWeapon(), character.getArmor());
                        newPlayer->setName(nickname);
                        newPlayer->getCurrentWeapon()->setIsBought(true);
                        newPlayer->addWeaponToInventory(*character.getCurrentWeapon());
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
void printEnemyCatalogue(const vector<Enemy>& enemies) { // Printing every enemy in game just so that user knows what to deal with
    cout << "\n\n\n==================================================\n";
    cout <<       "                   ENEMIES MANUAL";
    cout <<     "\n==================================================\n";
    {
        int i = 1;
        for (const auto& enemy : enemies) {
            cout << "\n-------------------------------------------\n";
            cout << "| " << i++ << ". " << enemy.getName() << ":\n";
            cout << "| HP: " << enemy.getMaxHp() << "\n";
            cout << "| Basic damage: " << enemy.getMinDamage() << "-" << enemy.getMaxDamage()<< "\n";
            cout << "| Critical damage chance: " << enemy.getCritChance() << "%\n";
            cout << "| Armor class: " << enemy.getArmor()<< "\n";
            cout << "| Money drop: " << enemy.getMoney()<< "$\n";
            cout << "| EXP drop: " << enemy.getXpReward();
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
            cout << "| " << i++ << ". " << weapon.getName() << ":\n";
            cout << "| Basic damage: " << weapon.getMinDMG()<< "-" << weapon.getMaxDMG()<< "\n";
            cout << "| Critical damage chance: " << weapon.getCritChance()<< "%\n";
            cout << "| Price: " << weapon.getPrice()<< "$\n";
            cout << "| Available on player level: " << weapon.getLvlReq()<< "\n";
            if (weapon.getIsBought()) {
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
    cout << "| " << player.getName() << ":\n";
    cout << "| Current HP: " << player.getHp()<< "\n";
    cout << "| Max HP: " << player.getMaxHp()<< "\n";
    cout << "| Level: " << player.getLevel()<< "\n";
    cout << "| Equipped Weapon: " << player.getCurrentWeapon()->getName() << "\n";
    cout << "| Damage: " << player.getMinDamage() << "-" << player.getMaxDamage() << "\n";
    cout << "| Kills: "<< player.getKills()<<"\n";
    cout << "| Armor class: " << player.getArmor()<< "\n";
    cout << "| Money: " << player.getMoney()<< "\n";
    cout << "| XP: " << player.getPlayerXp()<< "\n";
    cout << "| XP left for next level: " << player.getXpToNextLvl();
    cout << "\n-------------------------------------------\n\n";

}
void inventorySystem(Player& player ) {
    cout << "\n\n\n==================================================\n";
    cout << "                CHARACTER INVENTORY";
    cout << "\n==================================================\n";
    string choice;
    bool isLeaving = false;

    while (!isLeaving) {
        cout << "\nYou're in inventory menu.\nType '-1' to leave this menu\nType number of weapon or its name to choose it";
        {
            int i = 1;
            for (const Weapon& weapon : player.getInventory()) {
                cout << "\n-------------------------------------------\n";
                cout << i++ << ". " << weapon.getName();
                if (weapon == *player.getCurrentWeapon()) {
                    cout << ". This weapon is equipped now!";
                }
                cout << "\n-------------------------------------------\n";
            }

        }
        getline(cin >> std::ws, choice);
        {
            int i = 1;
            bool isFound = false;
            if (choice == "-1") {
                break;
                isLeaving = true;
            }
            else {

                for (Weapon& weapon : player.getInventory()) {
                    if (toLowerString(choice)==toLowerString(weapon.getName()) or choice == std::to_string(i)) {
                        isFound = true;
                        if(weapon == *player.getCurrentWeapon()){
                            cout << "\n-------------------------------------------\n";
                            cout << "Already equipped.";
                            cout << "\n-------------------------------------------\n";
                        }
                        else {
                        player.setCurrentWeapon(weapon);
                        cout << "\n-------------------------------------------\n";
                        cout << "Succesffuly equipped " << weapon.getName();
                        cout << "\n-------------------------------------------\n";
                        }                        
                        break;
                    }
                    i++;
                }
                if (!isFound) {
                    cout << "\n-------------------------------------------\n";
                    cout << "Couldn't find a weapon";
                    cout << "\n-------------------------------------------\n";
                }
            }
        }
    }

    cout << "-------------------------------------------\n";
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
                cout << i++ << ". " << weapon.getName();
                if (!weapon.getIsBought()) {
                    cout << "; Price: " << weapon.getPrice() << "; Level required: " << weapon.getLvlReq()<< "; Can buy - " << ((player.getLevel() >= weapon.getLvlReq() && player.getMoney() >= weapon.getPrice()) ? "Yes" : "No");
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
                if ((toLowerString(choice) == toLowerString(weapon.getName()) || indexStr == choice)) {
                    found = true;
                    if (weapon.getIsBought()) {
                        cout << "You already own " << weapon.getName()<< "!\nDo you want to equip it? 'Y' for yes, 'N' for no:\n";
                        std::getline(cin >> std::ws, choice);
                        if (toLowerString(choice) == "y") {
                            player.setCurrentWeapon(weapon) ;
                            cout << "Successfully equipped " << weapon.getName()<< "!\n";
                        }
                        break;
                    }
                    if (player.getMoney() >= weapon.getPrice()) {
                        if (player.getLevel() >= weapon.getLvlReq()) {
                            cout << "You have enough money to buy " << weapon.getName()<< ". Type 'Y' if you want to buy it; Type 'N' if you don't want to buy it\n";
                            std::getline(cin >> std::ws, choice);
                            if (toLowerString(choice) == "y") {
                                weapon.setIsBought(true);
                                player.spendMoney(weapon.getPrice());
                                player.setCurrentWeapon(weapon);
                                cout << "Successfully bought " << weapon.getName()<< " for " << weapon.getPrice()<< "$\nThis weapon is now equipped. (if you want to change equipped weapon, go to inventory from menu)\n";
                                player.addWeaponToInventory(weapon);
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
                            cout << "Your level is not enough to buy " << weapon.getName()<< "!\n";
                        }
                    }
                    else {
                        cout << "You have not enough money to buy " << weapon.getName() << "!\n";
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
void armorShop(Player& player) {
    cout << "\n\n==================================================\n";
    cout <<     "                     ARMOR SHOP";
    cout <<   "\n==================================================\n\n";
    cout << "\n-------------------------------------------\n";
    bool isLeaving = false;
    char choice;
    while (!isLeaving) {
        cout << "Your current Armor class is " << player.getArmor() << "\n";
        if (player.getArmor() > 0) {
            cout << "Your armor reflects " << armorClassFormula(player.getArmor()) * 100 << "% damage\n";
        }
        if (player.getArmor() < 4) {
            cout << "To buy " << player.getArmor() + 1 << " armor class you have to spend " << player.getArmorPrice(player.getArmor() + 1) << "$ and it will reflect " << armorClassFormula(player.getArmor() + 1) * 100 << "% damage\n";
            if (player.getArmorPrice(player.getArmor() + 1) > player.getMoney()) {
                cout << "You have not enough money to buy " << player.getArmor() + 1 << " armor class!\n";
                isLeaving = true;
                continue;
            }
        }
        else {
            cout << "You own max level of armor! It deflects " << armorClassFormula(player.getArmor()) * 100 << "% damage\n";
            isLeaving = true;
            continue;
        }
        cout << "Type 'Y' if you want to buy next armor class\nType 'N' if you don't want to buy next armor class\n";
        cout << "-------------------------------------------\n";
        cin >> choice;
        clearInput();
        switch (toupper(choice)) {
        case 'Y':
            player.setArmor(player.getArmor()+1);
            player.spendMoney(player.getArmorPrice(player.getArmor()));
            cout << "You successfully bought " << player.getArmor() << " class for " << player.getArmorPrice(player.getArmor()) << "$\n";
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


std::string toLowerString(std::string str) {
    for (char& c : str) {
        c = std::tolower(static_cast<unsigned char>(c)); // for loop to turn string into a lowercase string obv
    }
    return str;
}
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
double armorClassFormula(short armor) {
    return static_cast<double>(armor) / 5.0;
}
int getRandomNumber(int num1, int num2) {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(num1, num2);
    int randNum = dist(gen);
    return randNum;
}