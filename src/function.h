#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Forward declaration of Player class to resolve dependency
class Player;

// Function declarations
//@brief HANGMAN title
void title();
void displayExitMessage();

void printCentered(string text, int width, char fillChar);

//@brief Waits for the user to press any key to continue.
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

// @brief Single-player rules
void displayRules(); 

// @brief Two-player rules
void displayTwoPlayerRules(); 
void displayTurnMessage(const string& playerName, const string& opponentName);
void displayHintAndWord(const string& hint, const string& maskedWord, int chances);
void updateScore(Player& player, bool win);

// Class declarations
// Attribute for secret word, revealed letters; methods to check guesses, update revealed word, check if fully guessed.
class Word {
public:
    string secretWord;
    void checkGuesses();
    string getMaskedWord() const; // Added for masking
};

// Attributes for user, methods to record guesses.
class Player {
public:
    string name[2];
    int chances[2];
    int score;

    Player() : score(0) { name[0] = ""; chances[0] = 4; }
    Player(int i) : score(0) { name[i] = ""; chances[i] = 4; }
    Player(int i, string n) : score(0) { name[i] = n; chances[i] = 4; }
    int getScore() const { return score; }
    void setScore(int s) { score = s; }
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
};


class TwoPlayerSetupGame : public Game {
public:
    void start() override;
};

// @brief Responsible for managing word categories and providing utilities to access category information and randomly retrieve words from each category
class CategoryManager {
    vector<string> categoriesName; // @brief Stores category names in insertion order
    map<string, vector<string>> categories; // @brief Maps each category name to its list of associated words
public:
    CategoryManager();
    string getCategoryName(const int categoryID);
    vector<string> getCategoryList() const;
    string getRandomWord(const string category);
};

void displayHangmanState(const string& categoryName, int chances, const string& masked);
void displayGameResult(bool guessed, const string& secretWord);
bool processGuess(const string& secretWord, string& masked, int& chances);
void showCategoryMenu(const string& playerName, CategoryManager& manager);
