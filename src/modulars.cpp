#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>
#include "function.h"
#include <limits>

using namespace std;

void title() {
    cout << "=============================================================================\n";
    cout << "===========================  H  A  N  G  M  A  N  ===========================\n";
    cout << "=============================================================================\n\n";
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
    while(clock() < startClock + secondsAhead);
}

int input(int value) {
    int insert;
    while (true) {
        cin >> insert;
        if (cin.fail() || insert < 0) {
            cout << "Invalid input. Value must be a non-negative number. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return insert;
        }
    }
}

string input(string value) {
    string insert;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << value;
        getline(cin, insert);
        if (insert.empty()) {
            cout << "Invalid input. Please enter a non-empty value. Try again." << endl;
        } else {
            return insert;
        }
    }
}

char input(char value) {
    char insert;
    while (true) {
        cin >> insert;
        if (cin.fail() || insert == ' ') {
            cout << "Invalid input. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return insert;
        }
    }
}
