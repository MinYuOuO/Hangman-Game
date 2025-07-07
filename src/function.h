#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

/**
 * @brief HANGMAN title
 */
void title();

void displayExitMessage();

/**
 * @brief Waits for the user to press any key to continue.
 */
void wait();

/**
 * @brief Pauses the program execution for a specified number of seconds.
 * @param seconds The number of seconds to wait.
 */
void wait(float seconds);

/**
 * @brief Prompts the user to enter an integer value within a specified limit.
 * @param limit The upper limit for the input value.
 * @return int The validated integer input from the user.
 */
int input(int limit);

/**
 * @brief Prompts the user to enter a non-empty string.
 * @param value The prompt message to display.
 * @return string The validated string input from the user.
 */
string input(string value);

/**
 * @brief Prompts the user to enter a single character.
 * @param value The prompt message to display.
 * @return char The validated character input from the user.
 */
char input(char value);

// Attribute for secret word, revealed letters; methods to check guesses, update revealed word, check if fully guessed.
class Word {
public:
    void checkGuesses();
};

// Attributes for user, methods to record guesses.
class Player {
public:
    string name[3];
    int chances[3];

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

// @brief Manages game flow, word selection, interaction with Word and Player objects, user input, game state, win/loss conditions.
class Game { 
public:
    string secretWord;
};


// @brief Manages categories and word list
class CategoryManager {
    map<string, vector<string>> categories;
public:
    CategoryManager();

    vector<string> getCategoryList() const;

    string getRandomWord(const string category);
};