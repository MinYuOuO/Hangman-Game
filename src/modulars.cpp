#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

//Menu
void title() {
    cout<< "=============================================================================\n";
    cout<< "===========================  H  A  N  G  M  A  N  ===========================\n";
    cout<< "=============================================================================\n\n";
}

void displayExitMessage() {
    cout << "\n===========================================================\n";
    cout << "====================  T H A N K   Y O U  ==================\n";
    cout << "==================  F O R   P L A Y I N G  ================\n";
    cout << "=======================  H A N G M A N  ===================\n";
    cout << "=================  ~ Game Terminated ~  ===================\n";
    cout << "===========================================================\n";
}

void wait() {
    cout << '\n' << "Press any key to continue..." << endl;
    cin.ignore();
    cin.get();
}

void wait(float seconds) {
    clock_t startClock = clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    while(clock() < startClock+secondsAhead);
    return;
}

int input(int value) {
    int insert;
    while (true) {
        cin >> insert;
        if (cin.fail() || value <= 0) {
            cout << "Invalid input. Value must be a non-negative number. Please try again." << endl;
            cin.clear();
        } else {
            return insert;
        }
    }
}

string input(string value) {
    string insert;
    while (true) {
        cin >> insert;
        if (cin.fail() || value == "") {
            cout << "Invalid input. Value must be a non-negative number. Please try again." << endl;
            cin.clear();
        } else {
            return insert;
        }
    }
}

char input(char value) {
    char insert;
    while (true) {
        cin >> insert;
        if (cin.fail() || value <= 0 || value == ' ') {
            cout << "Invalid input. Value must be a non-negative number. Please try again." << endl;
            cin.clear();
        } else {
            return insert;
        }
    }
}

class Word {
    string secretWord;

public:
    void checkGuesses() {

    }
};

class Player {

public:

};

class Game {

public:

};


class CategoryManager {
private:

public:

};
