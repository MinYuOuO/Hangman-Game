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

        waitForKey();
        cout << "\033[2J\033[1;1H";
        displayTitle();

        int category;
        cout << "Player " << player1 << ",\n\n";
        cout << "Please choose a category:\n";
        cout << "[1] Food\n";
        cout << "[2] Country\n";
        cout << "[3] Comp. Science\n\n";
        cout << "Category number : ";
        cin >> category;

        cout << "\033[2J\033[1;1H";
        displayTitle();
        cout << "====================  C A T E G O R Y   S E L E C T E D  :  " << category << "  =====================\n\n";

        cout << "Before you start, remember the answer consists of 6 alphabets.\n\n";
        cout << "Make sure you answer in UPPERCASE ! !\n\n";
        waitForKey();
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
