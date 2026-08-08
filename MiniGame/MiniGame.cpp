#include "Enemy.h"
#include "Weapon.h"
#include "functions.h"
#include "GameManager.h"
#include "Player.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
using std::cout, std::cin, std::string, std::endl, std::vector;


int main()
{ 
      
    //gamePlaying(myPlayer, enemies, weapons, players);
    GameManager game;
    game.run();
    cout << "\n[GAME ENDS]\n\n";
    clearInput();
    cin.get();
    //if (myPlayer != nullptr) delete myPlayer;
    return 0;
}
//END OF MAIN



