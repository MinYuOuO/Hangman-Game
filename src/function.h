#pragma once
#include <iostream>
using namespace std;


//Menu
void displayTitle();
void displayExitMessage();
void waitForKey();
void runGame();

class Word {
public:
    void checkGuesses();
};

class Player;

class Game;

class CategoryManager;