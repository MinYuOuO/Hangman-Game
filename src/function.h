#pragma once
#include <iostream>
#include <string>
using namespace std;
std::string input(std::string value);
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
    int id;
    string name;

    Player() {
        id = 1;
        name = "";
    }

    Player(int i) : id(i) {}

    Player(int i, string n) : id(i), name(n) {} 
};

class Game;

class CategoryManager;