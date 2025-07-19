#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <SFML/Audio.hpp>

#include "server.h"

// ============================================================================
//                             Utility Functions
// ============================================================================

/// @brief Waits for the user to press any key to continue.
void wait(); 

/**
 * @brief Pauses the program execution for a specified number of seconds.
 * @param seconds The number of seconds to wait.
 */
void wait(float seconds);

/**
 * @brief Prints text centered within a given width, using a specified fill character.
 * @param text The text to center.
 * @param width The total width for centering.
 * @param fillChar The character used to pad the sides.
 */
void printCentered(string text, int width, char fillChar);

// ============================================================================
//                              Input Functions
// ============================================================================

/**
 * @brief Prompts the user to enter an integer value within a specified limit.
 * @param limit The upper limit for the input value.
 * @return int Validated integer input.
 */
int input(int limit);

/**
 * @brief Prompts the user to enter a non-empty string.
 * @param value The prompt message.
 * @return string Validated string input.
 */
string input(string value);

/**
 * @brief Prompts the user to enter a single character.
 * @param value The prompt message.
 * @return char The validated character input from the user.
 */
char input(char value);

// ============================================================================
//                             Game Display Functions
// ============================================================================


/// @brief Displays the game title screen.
void displayTitle();

/// @brief Displays a message when exiting the game.
void displayExitMessage();

/// @brief Displays single-player game rules.
void displayRules(); 

/// @brief Displays two-player game rules.
void displayTwoPlayerRules(); 

/// @brief Displays the current turn message.
/// @param playerName Name of the current player.
/// @param opponentName Name of the opponent.
void displayTurnMessage(const string& playerName, const string& opponentName);

/// @brief Displays the hint and masked word.
/// @param hint The hint for the word.
/// @param maskedWord The masked version of the word.
/// @param chances Remaining chances.
void displayHintAndWord(const string& hint, const string& maskedWord, int chances);

/// @brief 
/// @param categoryName 
/// @param chances 
/// @param masked 
void displayHangmanState(const string& categoryName, int chances, const string& masked);

/// @brief 
/// @param guessed 
/// @param secretWord 
void displayGameResult(bool guessed, const string& secretWord);

// ============================================================================
//                                  Classes
// ============================================================================

// ----------------------------------------------------------------------------
// Music Player
// ----------------------------------------------------------------------------

class MusicPlayer {
    sf::Music music;
    string backgroundMusic;
public:
    MusicPlayer();

    /// @brief Plays looping background music
    void playMusic();

    /// @brief Plays a one-shot sound effect
    void playSound(string audio);

    ~MusicPlayer(); // destructor
};

// ----------------------------------------------------------------------------
// Word Class
// ----------------------------------------------------------------------------

/// @brief Represents a word in the game.
class Word {
public:
    /// @brief The actual secret word that players try to guess.
    string secretWord;
    string maskedWord;

    /// @brief Default constructor.
    Word();

    /**
     * @brief Returns the word with unguessed letters masked (e.g., underscores).
     * @return A string with guessed letters revealed and others hidden.
     */
    string getMaskedWord() const;

    /// @brief Handles guessing logic.
    /// @return True if guess is correct, false otherwise.
    bool processGuess(int& chances);
};

// ----------------------------------------------------------------------------
// Player Class
// ----------------------------------------------------------------------------

/// @brief Represents player in the game.
class Player {
public:
    /// @brief Stores player names (supports 2 players).
    string name[2];

    int chances[2];

    /// @brief Score for each player.
    int score[2];

    /// @brief Default constructor.
    Player(); 

    /// @brief Constructor that initializes number of players.
    /// @param p Number of players.
    Player(int p);

    /// @brief Constructor with player count and name for player 0.
    /// @param p Number of players.
    /// @param n Name of the first player.
    Player(int p, string n);

    /**
     * @brief Gets the score of a specified player.
     * @param i Index of the player (0 or 1).
     * @return The score of the specified player.
     */
    int getScore(int i);
};

/// @brief Global user struct for storing a single user's name.
struct user {
    /// @brief Name of the user.
    std::string name;
};

/// @brief Global instance of user.
extern user globalUser;

// ----------------------------------------------------------------------------
// Abstract Game Class
// ----------------------------------------------------------------------------

/// @brief Abstract base class for a game mode.
class Game { 
public:
    /// @brief Starts the game. Must be implemented by subclasses.
    virtual void start() = 0;

    /// @brief Virtual destructor for safe cleanup.
    virtual ~Game() = default;
};

// ----------------------------------------------------------------------------
// Single Player Game
// ----------------------------------------------------------------------------

/**
 * @class SinglePlayerGame
 * @brief Handles the single-player game mode.
 */
class SinglePlayerGame : public Game {
public:
    /// @brief Starts the single-player game.
    void start() override;
};

// ----------------------------------------------------------------------------
// Two Player Local Setup Game
// ----------------------------------------------------------------------------

/**
 * @class TwoPlayerSetupGame
 * @brief Handles local two-player setup and gameplay.
 */
class TwoPlayerSetupGame : public Game {
public:
    /// @brief Starts the local two-player game.
    void start() override;
};

// ----------------------------------------------------------------------------
// Two Player Online Game (Abstract)
// ----------------------------------------------------------------------------

/// @brief Abstract base class for online multiplayer game modes.
class TwoPlayerOnlineGame : public Game {
public:
    /// @brief Starts the online game. Must be implemented by derived classes.
    virtual void start() override = 0;

    /// @brief Virtual destructor.
    virtual ~TwoPlayerOnlineGame() = default;
};

// ----------------------------------------------------------------------------
// Server Game
// ----------------------------------------------------------------------------

/// @brief Manages the server side of a two-player online game.
class ServerGame : public TwoPlayerOnlineGame{
    /// @brief Sets up and starts the server
    void startServer();

public:
    /// @brief TCP server instance to manage connections.
    TcpServer server;

    /// @brief Constructor for ServerGame.
    ServerGame();

    /// @brief Starts the server-side game loop.
    void start() override;
};

// ----------------------------------------------------------------------------
// Client Game
// ----------------------------------------------------------------------------

/// @brief Manages the client side of a two-player online game.
class ClientGame : public TwoPlayerOnlineGame{
    /// @brief Starts server (used in specific client-server setups).
    void startServer();

public:
    /// @brief TCP client instance to connect to server.
    TcpClient client;

    /// @brief Constructor for ClientGame.
    ClientGame();

    /// @brief Starts the client-side game loop.
    void start() override;
};

// ----------------------------------------------------------------------------
// Category Manager
// ----------------------------------------------------------------------------

/// @brief Manages word categories and provides utility functions for word selection.
class CategoryManager {
    /// @brief Stores category names in insertion order
    vector<string> categoriesName; 

    /// @brief Maps each category name to its list of associated words
    map<string, vector<string>> categories; 
public:
    /// @brief Constructor that initializes categories.
    CategoryManager();

    /**
     * @brief Returns the name of a category given its index.
     * @param categoryID Index of the category.
     * @return The category name.
     */
    string getCategoryName(const int categoryID);

    /**
     * @brief Gets a list of all category names.
     * @return A vector of category names.
     */
    vector<string> getCategoryList() const;

    /**
     * @brief Selects a random word from a specified category.
     * @param category The category to choose from.
     * @return A randomly selected word.
     */
    string getRandomWord(const string category);

    /**
     * @brief Displays the category menu for the user to choose from.
     * @param playerName The name of the player making the choice.
     */
    void displayCategoryMenu(const string& playerName);
};
