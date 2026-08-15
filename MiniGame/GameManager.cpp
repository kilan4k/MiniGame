#include "GameManager.h"
#include "Enemy.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <random>
#include <limits>
#include <utility>
#include <memory>
#include <array>

using std::cout, std::cin, std::string, std::endl, std::vector, std::array;

GameManager::GameManager() {}
GameManager::~GameManager() {}

void GameManager::declareData() {
   //Declaring different objects
   //Enemy types

    Enemy rat = Enemy("Rat", 25, 5, 10, 10, 0, 10, 10, DifficultyLevel::EASY); // 0
    Enemy spider = Enemy("Spider", 50, 15, 25, 50, 0, 20, 20, DifficultyLevel::EASY);// 1
    Enemy rogue = Enemy("Rogue", 75, 25, 35, 15, 0, 20, 20, DifficultyLevel::EASY);// 2
    Enemy skeleton = Enemy("Skeleton", 75, 20, 30, 60, 0, 30, 30, DifficultyLevel::EASY);// 3
    Enemy zombie = Enemy("Zombie", 100, 20, 30, 15, 1, 30, 30, DifficultyLevel::EASY);// 4
    Enemy goblin = Enemy("Goblin", 75, 30, 40, 10, 0, 50, 30, DifficultyLevel::EASY);// 5
    Enemy barbarian = Enemy("Barbarian", 100, 20, 40, 5, 1, 60, 50, DifficultyLevel::NORMAL);// 6
    Enemy bear = Enemy("Bear", 75, 40, 70, 25, 2, 105, 75, DifficultyLevel::NORMAL);// 7
    Enemy juggernaut = Enemy("Juggernaut", 250, 15, 20, 10, 3, 100, 100, DifficultyLevel::NORMAL);// 8
    Enemy knight = Enemy("Knight", 150, 40, 65, 25, 2, 150, 100, DifficultyLevel::HARD);// 9
    Enemy dragon = Enemy("Dragon", 300, 30, 60, 35, 1, 200, 120, DifficultyLevel::HARD);// 10
    Enemy demon = Enemy("Demon", 400, 60, 100, 40, 1, 240, 200, DifficultyLevel::HARD);// 11

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

    //Player types
    Player empty = Player(1, 0, &weapons[WeaponIndex::FISTS], 0, "New character");
    Player bandit = Player(1, 50, &weapons[WeaponIndex::KNIFE], 0, "Bandit");
    Player punchman = Player(1, 0, &weapons[WeaponIndex::FISTS], 1, "Punchman");
    Player archer = Player(1, 0, &weapons[WeaponIndex::BOW], 0, "Archer");
    Player lumberjack = Player(1, 0, &weapons[WeaponIndex::AXE], 0, "Lumberjack");
    Player robber = Player(1, 100, &weapons[WeaponIndex::FISTS], 0, "Robber");

    players = { empty, bandit, punchman, archer, lumberjack, robber };
}
void GameManager::run() {
    declareData();
    playerCreation();
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
        case '1': battleSystem();
            break;
        case '2': openShop();
            break;
        case 'S': printPlayerStats(*myPlayer);
            break;
        case 'H': myPlayer->HealPlayer();
            break;
        case 'I': inventorySystem();
            break;
        case 'A': armorShop();
            break;
        case 'E': printEnemyCatalogue();
            break;
        case 'Q': LeavingGame = true;
            break;
        default:
            cout << "Error! Try again!\n";
            break;
        }


    }
}
void GameManager::quit() {
    cout << "\n[GAME ENDS]\n\n";
    clearInput();
    cin.get();
}
void GameManager::battleSystem() {
    cout << "\n\n==================================================\n";
    cout << "                    BATTLE MENU";
    cout << "\n==================================================\n";
    char choice;
    constexpr short fleeingChance = 75;
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
    std::unique_ptr<Enemy> enemy = getRandomEnemy();
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
                enemy->Attack(*myPlayer);
                myPlayer->Attack(*enemy);
            }
        }
        else {
            myPlayer->Attack(*enemy);
            enemy->Attack(*myPlayer);
        }
        if (myPlayer->getHp() <= 0) {
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
    if (myPlayer->getHp() <= 0) {
        cout << "YOU DIED\n";
        cout << myPlayer->getName() << " was defeated.\n\n";

    }
    if (enemy != nullptr) {
        if (enemy->getHp() <= 0) {
            cout << "YOU WON\n";
            cout << enemy->getName() << " was defeated.\n\n";
            cout << "You get " << enemy->getXpReward() << "xp\nYou get " << enemy->getMoney() << "$\n";
            myPlayer->addMoney((enemy->getMoney()) * (myPlayer->getLevel() * 7 + 100) / 100);
            myPlayer->AddXp((enemy->getXpReward()) * (myPlayer->getLevel() * 5 + 100) / 100);
            myPlayer->addKills(1);
        }
    }
    cout << "\n-------------------------------------------\n\n\n";
}
std::unique_ptr<Enemy> GameManager::getRandomEnemy() {

    short randDifficulty = getRandomNumber(1, 100);

    const short RAND_EASY_PERC = currentConfig.easyEnemyChance; // from 0 to 100 percents of easy chance
    const short RAND_MED_PERC = currentConfig.easyEnemyChance+currentConfig.medEnemyChance; // medium number gap equals easy + med
    const short RAND_HARD_PERC = currentConfig.easyEnemyChance+currentConfig.medEnemyChance+currentConfig.hardEnemyChance; // same way there's hard number gap
    int easyNum = 0, medNum = 0, hardNum = 0;
    for (const auto& enemy : enemies) { // finding out number of every diffuclty type for each enemy
        if (enemy.getDifficulty() == DifficultyLevel::EASY) {
            easyNum++;
            medNum++;
            hardNum++;
        }
        else if (enemy.getDifficulty() == DifficultyLevel::NORMAL) {
            medNum++;
            hardNum++;
        }
        else if (enemy.getDifficulty() == DifficultyLevel::HARD) {
            hardNum++;
        }
    }
    const short MAX_EASY_ENEMY_INDEX=easyNum-1;
    const short MAX_MEDIUM_ENEMY_INDEX = medNum-1;
    const short MAX_HARD_ENEMY_INDEX = hardNum-1;
    if (randDifficulty <= RAND_EASY_PERC) {
        //cout << "EASY ";
        //cout << randDifficulty << "\n";
        int enemyNum = getRandomNumber(0, MAX_EASY_ENEMY_INDEX);
        return std::make_unique<Enemy>(enemies[enemyNum]);
    }
    else if (randDifficulty <= RAND_MED_PERC) {
        //cout << "MEDIUM ";
        //cout << randDifficulty << "\n";
        int enemyNum = getRandomNumber(MAX_EASY_ENEMY_INDEX + 1, MAX_MEDIUM_ENEMY_INDEX);
        return std::make_unique<Enemy>(enemies[enemyNum]);

    }
    else {
        //cout << "HARD ";
        //cout << randDifficulty<<"\n";
        int enemyNum = getRandomNumber(MAX_MEDIUM_ENEMY_INDEX + 1, MAX_HARD_ENEMY_INDEX);
        return std::make_unique<Enemy>(enemies[enemyNum]);
    }
}
void GameManager::playerCreation() {// creating player's character
    cout << "\n==================================================\n";
    cout << "           WELCOME TO CHARACTER CREATOR";
    cout << "\n==================================================\n";
    bool hasChosen = false;
    char choice;
    string cName;
    string nickname;
    while (!hasChosen) { //we'll be asking everytime till user chooses a character

        cout << "You can choose any of these characters: \n\n";
        {
            cout << "-------------------------------------------\n";
            int i = 1;
            for (const auto& character : players) { // showing every character
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
            cout << "\nEnter its name or its number: ";
            std::getline(cin >> std::ws, cName);
            {
                int i = 1;
                for (const auto& character : players) {
                    string indexStr = std::to_string(i++);
                    if ((toLowerString(character.getName()) == toLowerString(cName)) || (indexStr == cName)) { // checking if user's input equals any name of a character
                        hasChosen = true;
                        cout << "\nExcellent choice!\n\n======You have successfully chosen a character called " << character.getName() << ".======\n\nNow enter your nickname: ";
                        std::getline(cin >> std::ws, nickname);

                        cout << "Welcome to this dangerous world, " << nickname << " and I wish you good luck on this journey!\n\n";
                        myPlayer = std::make_unique<Player>(character.getLevel(), character.getMoney(), character.getCurrentWeapon(), character.getArmor(), nickname);
                        myPlayer->getCurrentWeapon()->setIsBought(true);
                        myPlayer->addWeaponToInventory(character.getCurrentWeapon());
                        std::cout << "-------------------------------------------\n";
                        break;
                    }

                }
            }
            if (!hasChosen) {
                cout << "\nError! Try again.\n"; // Error in case user inputs some dumb stuff
            }
            break;
        case '2':
            for (const auto& character : players) {
                printPlayerStats(character);// if user asks to show stats we show him stats for every character
            }
            break;
        default:
            cout << "\nError! Try again.\n";
            break;
        }

    }
    std::cout << "-------------------------------------------\n";
}
void GameManager::printEnemyCatalogue()const { // Printing every enemy in game just so that user knows what to deal with
    cout << "\n\n\n==================================================\n";
    cout << "                   ENEMIES MANUAL";
    cout << "\n==================================================\n";
    {
        int i = 1;
        DifficultyLevel difficultyD;
        string difficultyS;
        for (const auto& enemy : enemies) {
            difficultyD = enemy.getDifficulty();
            switch (difficultyD) {
            case DifficultyLevel::EASY:
                difficultyS = "Easy";
                break;
            case DifficultyLevel::NORMAL:
                difficultyS = "Normal";
                break;
            case DifficultyLevel::HARD:
                difficultyS = "Hard";
                break;
            }
            cout << "\n-------------------------------------------\n";
            cout << "| " << i++ << ". " << enemy.getName() << ":\n";
            cout << "| HP: " << enemy.getMaxHp() << "\n";
            cout << "| Basic damage: " << enemy.getMinDamage() << "-" << enemy.getMaxDamage() << "\n";
            cout << "| Critical damage chance: " << enemy.getCritChance() << "%\n";
            cout << "| Armor class: " << enemy.getArmor() << "\n";
            cout << "| Money drop: " << enemy.getMoney() << "$\n";
            cout << "| EXP drop: " << enemy.getXpReward()<<"\n";
            cout << "| Difficulty: " << difficultyS;
        }
    }
    cout << "\n-------------------------------------------\n\n\n";
}
void GameManager::printWeaponCatalogue()const { // Printing Weapon catalogue which may also be used as a shop
    {
        cout << "\n\n\n==================================================\n";
        cout << "                    WEAPON STATS";
        cout << "\n==================================================\n";
        int i = 1;
        for (const auto& weapon : weapons) {
            cout << "\n-------------------------------------------\n";
            cout << "| " << i++ << ". " << weapon.getName() << ":\n";
            cout << "| Basic damage: " << weapon.getMinDMG() << "-" << weapon.getMaxDMG() << "\n";
            cout << "| Critical damage chance: " << weapon.getCritChance() << "%\n";
            cout << "| Price: " << weapon.getPrice() << "$\n";
            cout << "| Available on player level: " << weapon.getLvlReq() << "\n";
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
void GameManager::printPlayerStats(const Player& player)const { // Printing character or player stats 
    cout << "\n\n\n==================================================\n";
    cout << "                CHARACTER STATS";
    cout << "\n==================================================\n";
    cout << "\n-------------------------------------------\n";
    cout << "| " << player.getName() << ":\n";
    cout << "| Current HP: " << player.getHp() << "\n";
    cout << "| Max HP: " << player.getMaxHp() << "\n";
    cout << "| Level: " << player.getLevel() << "\n";
    cout << "| Equipped Weapon: " << player.getCurrentWeapon()->getName() << "\n";
    cout << "| Damage: " << player.getMinDamage() << "-" << player.getMaxDamage() << "\n";
    cout << "| Kills: " << player.getKills() << "\n";
    cout << "| Armor class: " << player.getArmor() << "\n";
    cout << "| Money: " << player.getMoney() << "\n";
    cout << "| XP: " << player.getPlayerXp() << "\n";
    cout << "| XP left for next level: " << player.getXpToNextLvl();
    cout << "\n-------------------------------------------\n\n";

}
void GameManager::inventorySystem() {
    cout << "\n\n\n==================================================\n";
    cout << "                CHARACTER INVENTORY";
    cout << "\n==================================================\n";
    string choice;
    bool isLeaving = false;

    while (!isLeaving) {
        cout << "\nYou're in inventory menu.\nType '-1' to leave this menu\nType number of weapon or its name to choose it";
        {
            int i = 1;
            for (auto weapon : myPlayer->getInventory()) {
                cout << "\n-------------------------------------------\n";
                cout << i++ << ". " << weapon->getName();
                if (*weapon == *myPlayer->getCurrentWeapon()) {
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
                isLeaving = true;
                break;
            }
            else {

                for (Weapon*& weapon : myPlayer->getInventory()) {
                    if (toLowerString(choice) == toLowerString(weapon->getName()) or choice == std::to_string(i)) {
                        isFound = true;
                        if (*weapon == *myPlayer->getCurrentWeapon()) {
                            cout << "\n-------------------------------------------\n";
                            cout << "Already equipped.";
                            cout << "\n-------------------------------------------\n";
                        }
                        else {
                            myPlayer->setCurrentWeapon(weapon);
                            cout << "\n-------------------------------------------\n";
                            cout << "Succesffuly equipped " << weapon->getName();
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
void GameManager::openShop() {
    cout << "\n\n\n==================================================\n";
    cout << "                     WEAPON SHOP";
    cout << "\n==================================================\n";
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
                    cout << "; Price: " << weapon.getPrice() << "; Level required: " << weapon.getLvlReq() << "; Can buy - " << ((myPlayer->getLevel() >= weapon.getLvlReq() && myPlayer->getMoney() >= weapon.getPrice()) ? "Yes" : "No");
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
                        cout << "You already own " << weapon.getName() << "!\nDo you want to equip it? 'Y' for yes, 'N' for no:\n";
                        std::getline(cin >> std::ws, choice);
                        if (toLowerString(choice) == "y") {
                            myPlayer->setCurrentWeapon(&weapon);
                            cout << "Successfully equipped " << weapon.getName() << "!\n";
                        }
                        break;
                    }
                    if (myPlayer->getMoney() >= weapon.getPrice()) {
                        if (myPlayer->getLevel() >= weapon.getLvlReq()) {
                            cout << "You have enough money to buy " << weapon.getName() << ". Type 'Y' if you want to buy it; Type 'N' if you don't want to buy it\n";
                            std::getline(cin >> std::ws, choice);
                            if (toLowerString(choice) == "y") {
                                weapon.setIsBought(true);
                                myPlayer->spendMoney(weapon.getPrice());
                                myPlayer->setCurrentWeapon(&weapon);
                                cout << "Successfully bought " << weapon.getName() << " for " << weapon.getPrice() << "$\nThis weapon is now equipped. (if you want to change equipped weapon, go to inventory from menu)\n";
                                myPlayer->addWeaponToInventory(&weapon);
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
                            cout << "Your level is not enough to buy " << weapon.getName() << "!\n";
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
        case 2: printWeaponCatalogue();
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
void GameManager::armorShop() {
    cout << "\n\n==================================================\n";
    cout << "                     ARMOR SHOP";
    cout << "\n==================================================\n\n";
    cout << "\n-------------------------------------------\n";
    bool isLeaving = false;
    char choice;
    while (!isLeaving) {
        cout << "Your current Armor class is " << myPlayer->getArmor() << "\n";
        if (myPlayer->getArmor() > 0) {
            cout << "Your armor reflects " << armorClassFormula(myPlayer->getArmor()) * 100 << "% damage\n";
        }
        if (myPlayer->getArmor() < 4) {
            cout << "To buy " << myPlayer->getArmor() + 1 << " armor class you have to spend " << myPlayer->getArmorPrice(myPlayer->getArmor() + 1) << "$ and it will reflect " << armorClassFormula(myPlayer->getArmor() + 1) * 100 << "% damage\n";
            if (myPlayer->getArmorPrice(myPlayer->getArmor() + 1) > myPlayer->getMoney()) {
                cout << "You have not enough money to buy " << myPlayer->getArmor() + 1 << " armor class!\n";
                isLeaving = true;
                continue;
            }
        }
        else {
            cout << "You own max level of armor! It deflects " << armorClassFormula(myPlayer->getArmor()) * 100 << "% damage\n";
            isLeaving = true;
            continue;
        }
        cout << "Type 'Y' if you want to buy next armor class\nType 'N' if you don't want to buy next armor class\n";
        cout << "-------------------------------------------\n";
        cin >> choice;
        clearInput();
        switch (toupper(choice)) {
        case 'Y':
            myPlayer->setArmor(myPlayer->getArmor() + 1);
            myPlayer->spendMoney(myPlayer->getArmorPrice(myPlayer->getArmor()));
            cout << "You successfully bought " << myPlayer->getArmor() << " class for " << myPlayer->getArmorPrice(myPlayer->getArmor()) << "$\n";
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