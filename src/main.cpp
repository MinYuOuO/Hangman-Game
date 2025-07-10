#include <iostream>
#include <string>
#include "function.h"
#include <SFML/Window.hpp>

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
        cout << "Please choose a category:\n";
        cout << "[1] Food\n";
        cout << "[2] Country\n";
        cout << "[3] Comp. Science\n\n";
        cout << "Category number : ";

        int category;
        category = input(3);

        Word room;

        switch (category)
        {
        case 1:
            room.secretWord = categoryManager.getRandomWord("Food");
            break;
            
        case 2:
            room.secretWord = categoryManager.getRandomWord("Country");
            break;

        case 3:
            room.secretWord = categoryManager.getRandomWord("Comp. Science");
            break;

        default:
            cout << "Invalid Error, Restarting..." << endl;
            wait(2.0);
            continue;
        }

        wait(1.0);

        cout << "=====================  C A T E G O R Y   S E L E C T E D  :  " << category << "  =====================" << endl;

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
            cout << "\n\n" << endl;
            cout << "  +---+" << endl;
               cout << "  |   |" << endl;
            cout << "      |            Chances left: "<< chances << endl;
            cout << "      |            Word: " << masked << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            cout << "" << endl;
            
            char c = '\0';
            cout << "Letter: ";
            c = input(c);
            bool found = false;
            for (int i = 0; i < room.secretWord.length(); i++) {
                // room.checkGuesses();
                if (room.secretWord[i] == toupper(c)) {
                    masked[i] = room.secretWord[i];
                    found = true;
                }
            }
            if (!found) {
                chances--;
            }
            guessed = (masked == room.secretWord);
        }

        system("cls");

        title();
        cout << "\n\n" << endl;
        if (guessed) {
            cout << "You Win! The word is: " << room.secretWord << endl;
            wait();
            break;
        } else {

            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |            You Loose! The word is:" << room.secretWord << endl;
            cout << " /|/  |" << endl;
            cout << " / /  |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            wait();
            break;
        }
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
    sf::Window window(sf::VideoMode({800, 600}), "My window");
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