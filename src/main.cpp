#include <iostream>
#include <string>
#include "function.h"
#include <SFML/Audio.hpp>

using namespace std;

CategoryManager categoryManager;

void SinglePlayerGame::start() {
    Player player;

    while (true) {
        cout << "Please enter your name: ";
        player.name[0] = input("");
        cout << "\nGood luck in your game later, player " << player.name[0] << "!" << endl;

        wait(1.0);

        system("cls");
        title();

        cout << "Player " << player.name[0] << ",\n\n";
        showCategoryMenu(player.name[0], categoryManager);
        int category = input(3) - 1;

        int category = input(3) - 1;

        Word room;
        string categoryName = categoryManager.getCategoryName(category);
        room.secretWord = categoryManager.getRandomWord(categoryName);

        wait(1.0);

        cout << "\n" << endl;
        cout << "=====================  C A T E G O R Y   S E L E C T E D  :  " << categoryName << "  =====================" << endl;
        cout << "Before you start, remember the answer consists of 6 alphabets.\n" << endl;
        cout << "Make sure you answer in UPPERCASE ! !\n" << endl;

        wait(2.0);

        cout << "\n\n\n" << endl;
        string masked(room.secretWord.length(), '*');

        int chances = 15;
        bool guessed = false;

        while (chances > 0 && !guessed) {
            system("cls");
            title();

            displayHangmanState(categoryName, chances, masked);

            guessed = processGuess(room.secretWord, masked, chances);


        system("cls");
        title();

        displayGameResult(guessed, room.secretWord);
        break;


    }
}

void TwoPlayerSetupGame::start() {
    Player player(1);

    cout << "Please enter your name" << endl;
    cout << "Player 1 : ";
    player.name[0] = input("");
    cout << "Player 2 : ";
    player.name[1] = input("");
    cout << "\nGood luck in your game later, player " << player.name[0] << " and player " << player.name[1] << "!" << endl;

    int currentPlayer = 0;
    int opponent = 1;
    while (player.getScore() < 5 && player.getScore() < 5) { // Simplified score check; adjust for both players
        displayTurnMessage(player.name[currentPlayer], player.name[opponent]);

        cout << "Player " << player.name[currentPlayer] << "," << endl;
        cout << "Please enter the word that you want " << player.name[opponent] << " to guess." << endl;
        cout << "TAKE NOTE => Answer MUST be in UPPERCASE" << endl;
        string word;
        while (true) {
            word = input("");
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            if (word.length() >= 1) break;
            cout << "Word must be at least 1 letter. Try again." << endl;
        }

        cout << "You entered = [" << word << "]" << endl;
        // Removed hint input; using opponent's name instead
        Word room;
        room.secretWord = word;

        displayTurnMessage(player.name[opponent], player.name[currentPlayer]);

        int chances = 4;
        string masked(room.secretWord.length(), '*');
        bool guessed = false;

        while (chances > 0 && !guessed) {
            displayHintAndWord(player.name[opponent], masked, chances); // Use opponent's name as hint
            int choice = input(2);
            if (choice == 1) {
                char c = '\0';
                cout << "Letter: ";
                c = input(c);
                bool found = false;
                for (size_t i = 0; i < room.secretWord.length(); i++) {
                    if (room.secretWord[i] == toupper(c)) {
                        masked[i] = room.secretWord[i];
                        found = true;
                    }
                }
                if (!found) chances--;
                guessed = (masked == room.secretWord);
            } else if (choice == 2) {
                cout << "Guess the word: ";
                string guess = input("");
                transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
                if (guess == room.secretWord) guessed = true;
                else chances--;
            }
        }

        system("cls");
        title();
        cout << "\n\n" << endl;
        if (guessed) {
            cout << "Congratulations! Your man is saved." << endl;
            cout << "The answer is [" << room.secretWord << "] !" << endl;
            cout << "You earn 4 points from this game!" << endl;
            updateScore(player, true);
        } else {
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   | You Lose! The word is: " << room.secretWord << endl;
            cout << " /|/  |" << endl;
            cout << " / /  |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
        }
        wait();
        swap(currentPlayer, opponent);
    }

    cout << "Game Over! Final Scores:" << endl;
    cout << player.name[0] << ": " << player.getScore() << " points" << endl;
    cout << player.name[1] << ": " << 0 << " points" << endl; // Placeholder; adjust scoring
}

int main() {
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("audio/background_music.wav")) {
        cerr << "Failed to load background music." << endl;
    } else {
        backgroundMusic.setLooping(true);
        backgroundMusic.play();
    }

    while (true) {
        system("cls");
        title();
        cout << "Welcome to Hangman! Please select your mode" << endl;
        cout << "[1] Single player   (vs. computer)" << endl;
        cout << "[2] Two player      (vs. each other)" << endl;
        cout << "[3] Quit Game" << endl;
        cout << "Select mode number : ";

        int mode;
        mode = input(3);
        cin.clear();

        system("cls");
        title();
        cout << "=====================  M O D E   S E L E C T E D  :  " << mode << "  =====================" << endl;

        if (mode == 1) {
            displayRules();
            Game* game = new SinglePlayerGame();
            game->start();
            delete game;
        } else if (mode == 2) {
            displayTwoPlayerRules();
            Game* game = new TwoPlayerSetupGame();
            game->start();
            delete game;
        } else if (mode == 3) {
            displayExitMessage();
            break;
        } else {
            cout << "Invalid Error, Restarting..." << endl;
            wait();
        }
    }
    return 0;
}