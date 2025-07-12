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


        int category = 0;
        category = input(3) - 1;

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

        while (chances > 0 && guessed == false) {
            system("cls");
            title();

            displayHangmanState(categoryName, chances, masked);
            
            guessed = processGuess(room.secretWord, masked, chances);

        }

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

        system("cls"); // system command clear screen

        title();
        cout << "=====================  M O D E   S E L E C T E D  :  " << mode << "  =====================" << endl;
        
        if (mode == 1) {
            Game* game = new SinglePlayerGame();
            game->start();
            delete game;
        } else if (mode == 2) {
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