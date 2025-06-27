#include <iostream>
using namespace std;

//Menu
void displayTitle(){
    cout<< "==============================================================\n";
    cout<< "===========================  H  A  N  G  M  A  N  =============\n";
    cout<< "==============================================================\n\n";
}

void displayExitMessage() {
    cout << "\n===========================================================\n";
    cout << "====================  T H A N K   Y O U  ==================\n";
    cout << "==================  F O R   P L A Y I N G  ================\n";
    cout << "=======================  H A N G M A N  ===================\n";
    cout << "=================  ~ Game Terminated ~  ===================\n";
    cout << "===========================================================\n";
}

void waitForKey() {
    cout << "Press ENTER to continue...";
    cin.ignore();
    cin.get();
}

class Word {
private:
    string secretWord;


public:
    void checkGuesses() {

    }
};

class Player {
private:

public:

};

class Game {
private:

public:

};


class CategoryManager {
private:

public:

};

void runGame() {
    int mode;
    string player1, player2;

    cout << "\033[2J\033[1;1H"; // Clear screen (ANSI escape code for VS Code)
    displayTitle();
    cout << "Welcome to Hangman! Please select your mode\n\n";
    cout << "[1] Single player   (vs. computer)\n";
    cout << "[2] Two player      (vs. each other)\n\n";
    cout << "Select mode number : ";
    cin >> mode;

    cout << "\033[2J\033[1;1H"; // Clear screen again
    displayTitle();
    cout << "====================  M O D E   S E L E C T E D  :  " << mode << "  =====================\n\n";

    if (mode == 1) {
        cout << "Please enter your name: ";
        cin >> player1;
        cout << "\nGood luck in your game later, player " << player1 << "!\n";
    } else if (mode == 2) {
        cout << "Please enter your name\n";
        cout << "Player 1 : ";
        cin >> player1;
        cout << "Player 2 : ";
        cin >> player2;
        cout << "\nGood luck in your game later, player " << player1 << " and player " << player2 << "!\n";
    } else {
        cout << "Invalid mode. Exiting...\n";
        return;
    }

    waitForKey();
}
