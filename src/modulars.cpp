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

void displayHangmanState(const string& categoryName, int chances, const string& masked) {
    cout << "\n\n" << endl;
    cout << setfill(' ') << setw(10) << "  +---+" << endl;
    cout << setfill(' ') << setw(10) << "  |   |" << setw(30) << "Subject: " << categoryName << endl;
    cout << setfill(' ') << setw(10) << "      |" << setw(30) << "Chances left: " << chances << endl;
    cout << setfill(' ') << setw(10) << "      |" << setw(30) << "Word: " << masked << endl;
    cout << setfill(' ') << setw(10) << "      |" << endl;
    cout << setfill(' ') << setw(10) << "      |" << endl;
    cout << setfill(' ') << setw(12) << "=========" << endl;
    cout << "\n\n" << endl;
}

void displayGameResult(bool guessed, const string& secretWord) {
    cout << "\n\n" << endl;
    if (guessed) {
        cout << setw(50) << "You Win! The word is: " << secretWord << endl;
    } else {
        cout.fill(' ');
        cout << setfill(' ') << setw(10) << "  +---+" << endl;
        cout << setfill(' ') << setw(10) << "  |   |" << endl;
        cout << setfill(' ') << setw(10) << "  O   | " << setw(10) << "You Loose! The word is: " << secretWord << endl;
        cout << setfill(' ') << setw(10) << " /|/  |" << endl;
        cout << setfill(' ') << setw(10) << " / /  |" << endl;
        cout << setfill(' ') << setw(10) << "      |" << endl;
        cout << setfill(' ') << setw(12) << "=========" << endl;
    }
    wait();
}

bool processGuess(const string& secretWord, string& masked, int& chances) {
    char c = '\0';
    cout << "Letter: ";
    c = input(c);
    
    bool found = false;
    for (size_t i = 0; i < secretWord.length(); ++i) {
        if (secretWord[i] == toupper(c)) {
            masked[i] = secretWord[i];
            found = true;
        }
    }

    if (!found) {
        chances--;
    }

    return masked == secretWord; 
}
