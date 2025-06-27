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
    displayTitle();
    cout << "Game started...\n";
    waitForKey();
    displayExitMessage();
}
