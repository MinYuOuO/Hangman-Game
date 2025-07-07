#pragma once
#include <iostream>
#include <string>
using namespace std;

//Menu

/**
 * @brief HANGMAN title
 */
void title();

void displayExitMessage();

/**
 * @brief This function will wait for user to continue
 */
void wait();

/**
 * @brief sleep function
 * @param seconds sleep how many seconds
 */
void wait(float seconds);

/**
 * @brief User input int
 */
int input(int value);
string input(string value);
char input(char value);

void runGame();

class Word {
public:
    void checkGuesses();
};

class Player {
public:
    string name[2];
    int chances[2];

    Player() {
        name[0] = "";
    }

    Player(int i) {
        name[i];
    }

    Player(int i, string n) {
        name[i] = n;
    } 
};

class Game;

class CategoryManager;