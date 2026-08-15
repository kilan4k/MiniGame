#include "functions.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#include <random>

std::string toUpperString(std::string str) {
    for (char& c : str) {
        c = std::toupper(static_cast<unsigned char>(c)); // for loop to turn string into a uppercase string obv
    }
    return str;
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
int getRandomNumber(int num1, int num2) {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(num1, num2);
    int randNum = dist(gen);
    return randNum;
}