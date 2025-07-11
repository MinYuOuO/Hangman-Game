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

/**
 * @brief Displays the rules and regulations of the Hangman game.
 */
void displayRules();

// Attribute for secret word, revealed letters; methods to check guesses, update revealed word, check if fully guessed.
class Word {
public:
    string secretWord;
    void checkGuesses();
};

// Attributes for user, methods to record guesses.
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

// @brief Manages game flow, word selection, interaction with Word and Player objects, user input, game state, win/loss conditions.
class Game { 
public:
    virtual void start() = 0;
    virtual ~Game() = default;
};

class SinglePlayerGame : public Game {
public:
    void start() override;
    // Add single player specific members and methods
};

class TwoPlayerSetupGame : public Game {
public:
    void start() override;
    // Add two player specific members and methods
};

// @brief Responsible for managing word categories and providing utilities to access category information and randomly retrieve words from each category
class CategoryManager {
    // @brief Stores category names in insertion order
    vector<string> categoriesName;

    // @brief Maps each category name to its list of associated words
    map<string, vector<string>> categories;
public:
    CategoryManager();
    
    string getCategoryName(const int categoryID);

    // @brief a list of all category names in alphabetical order
    vector<string> getCategoryList() const;

    /**
     * @brief Get the Random Word object
     * @param category the specified category
     * @return string category, a random word from the specified category.
     */
    string getRandomWord(const string category);
};