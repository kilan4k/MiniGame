#include "Enemy.h"
#include "Weapon.h"
#include "functions.h"
#include "GameManager.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl, std::vector;

int main()
{ 
    GameManager game;
    game.run();
    game.quit();
    return 0;
}