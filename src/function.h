#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Forward declaration of Player class to resolve dependency
class Player;

// Function declarations
void title();
void displayExitMessage();
void wait();
void wait(float seconds);
int input(int limit);
string input(string value);
char input(char value);
void displayRules(); // Single-player rules
void displayTwoPlayerRules(); // Two-player rules
void displayTurnMessage(const string& playerName, const string& opponentName);
void displayHintAndWord(const string& hint, const string& maskedWord, int chances);
void updateScore(Player& player, bool win);

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

class CategoryManager {
    vector<string> categoriesName;
    map<string, vector<string>> categories;
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

