#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>
#include "function.h"
#include <limits>

using namespace std;

void title() {
    cout << "=============================================================================" << endl;
    cout << "===========================  H  A  N  G  M  A  N  ===========================" << endl;
    cout << "=============================================================================\n" << endl;
}

void displayExitMessage() {
    cout << "=============================================================================" << endl;
    cout << "===========================  T H A N K   Y O U  =============================" << endl;
    cout << "=========================  F O R   P L A Y I N G  ===========================" << endl;
    cout << "============================  H A N G M A N  ================================" << endl;
    cout << "=========================  ~ Game Terminated ~  =============================" << endl;
    cout << "=============================================================================\n" << endl;
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

int input(int limit) {
    int insert;
    while (true) {
        cin >> insert;
        if (cin.fail() || insert < 0 || insert > limit) {
            cout << "Invalid input. Please try again." << endl;
            cin.clear();
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return insert;
        }
    }
}

string input(string value) {
    string insert;
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return insert;
        }
    }
}

CategoryManager::CategoryManager() {
    categories["Food"] = {"PIZZA", "BURGER", "SUSHI", "NOODLE"};
    categories["Country"] = {"CANADA", "BRAZIL", "FRANCE", "JAPAN"};
    categories["Comp. Science"] = {"PYTHON", "ALGORITHM", "BINARY", "OBJECT"};
}

vector<string> CategoryManager::getCategoryList() const {
    vector<string> categoryList;
    for (const auto& pair : categories) {
        categoryList.push_back(pair.first);
    }
    return categoryList;
}

string CategoryManager::getRandomWord(const string category) {
    auto it = categories.find(category);
    if (it != categories.end() && !it->second.empty()) {
        const vector<string>& words = it->second;
        int idx = rand() % words.size();
        return words[idx];
    }
    return ""; // if category not found or has no words
}
