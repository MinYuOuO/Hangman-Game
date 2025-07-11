#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <limits>
#include <iomanip>
#include "function.h"

using namespace std;

void printCentered(string text, int width, char fillChar = ' ') {
    int padding = (width - text.length()) / 2;
    cout << setfill(fillChar) << setw(padding + text.length()) << text << setw(width - (padding + text.length())) << "" << endl;
}

void title() {
    const int width = 77;

    cout << setfill('=') << setw(width) << "=" << endl;
    printCentered("H  A  N  G  M  A  N", width);
    cout << setfill('=') << setw(width) << "=" << endl;
    cout << endl;
}

void displayExitMessage() {
    const int width = 77;

    cout << setfill('=') << setw(width) << "=" << endl;
    printCentered("T H A N K   Y O U", width);
    printCentered("F O R   P L A Y I N G", width);
    printCentered("H A N G M A N", width);
    printCentered("~ Game Terminated ~", width);
    cout << setfill('=') << setw(width) << "=" << endl;
    cout << endl;
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
    categoriesName = {"Food", "Country", "Comp. Science"};
    categories[categoriesName[0]] = {"PIZZA", "BURGER", "SUSHI", "NOODLE"};
    categories[categoriesName[1]] = {"CANADA", "BRAZIL", "FRANCE", "JAPAN"};
    categories[categoriesName[2]] = {"PYTHON", "ALGORITHM", "BINARY", "OBJECT"};
}

vector<string> CategoryManager::getCategoryList() const {
    vector<string> categoryList;
    for (const auto& pair : categories) {
        categoryList.push_back(pair.first);
    }
    return categoryList;
}

string CategoryManager::getCategoryName(int categoryID) {
    if (categoryID < 0 || categoryID >= categoriesName.size()) {
        return "";
    }
    return categoriesName[categoryID];
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
