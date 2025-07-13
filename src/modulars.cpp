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
    printCentered("H  A  N  G  M  A  N", width, '=');
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
    while (clock() < startClock + secondsAhead);
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
    return "";
}


void displayHangmanState(const string& categoryName, int chances, const string& masked) {
    system("cls");
    title();
    cout << "\n\n" << endl;
    cout << setfill(' ') << setw(10) << "  +---+" << endl;
    cout << setfill(' ') << setw(10) << "  |   |" << setw(30) << "Subject: " << categoryName << endl;
    cout << "     " << (chances < 5 ? "O" : " ") << "   |" << setw(30) << "Chances left: " << chances << endl;
    cout << "    " << (chances < 4 ? "/" : " ") << (chances < 3 ? "|" : " ") << (chances < 2 ? "/" : " ") << "  |" << setw(30) << "Word: " << masked << endl;
    cout << "     " << (chances < 1 ? "/": " ") << (chances < 0 ? " /": "  ") << " |" << endl;
    cout << setfill(' ') << setw(10) << "      |" << endl;
    cout << setfill(' ') << setw(12) << "=========" << endl;
    cout << "\n\n" << endl;
}

void displayGameResult(bool guessed, const string& secretWord) {
    system("cls");
    title();
    cout << "\n\n" << endl;
    if (guessed) {
        cout << setfill(' ') << setw(50) << "You Win! The word is: " << secretWord << endl;
    } else {
        cout.fill(' ');
        cout << setfill(' ') << setw(10) << "  +---+" << endl;
        cout << setfill(' ') << setw(10) << "  |   |" << endl;
        cout << setfill(' ') << setw(11) << "  O   | " << setw(15) << "You Loose! The word is: " << secretWord << endl;
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

void showCategoryMenu(const string& playerName, CategoryManager& manager) {
    system("cls");
    title();
    cout << "" << endl;
    cout << "Player " << playerName << ",\n" << endl;
    cout << "Please choose a category:" << endl;

    for (size_t i = 0; i < manager.getCategoryList().size(); ++i) {
        cout << "[" << i + 1 << "] " << manager.getCategoryName(i) << endl;
    }

    cout << "Category number : ";
}

void displayRules() {
    cout << "Now, let's learn the rules of playing hangman before you proceed!" << endl;
    cout << endl;
    cout << "GAME RULES :" << endl;
    cout << "1. This game mode requires 1 player only" << endl;
    cout << "2. The computer will generate a word from your chosen category" << endl;
    cout << "3. You need to guess the word by trying one alphabet or the whole word" << endl;
    cout << "4. You have 15 chances to guess the word" << endl;
    cout << "5. If you fail to guess the word after all chances, the game ends" << endl;
    cout << endl;
    cout << "GOOD LUCK!!" << endl;

    wait();
    system("cls");
}

void displayTwoPlayerRules() {
    system("cls");
    title();

    cout << "Now, let's learn the rules of playing hangman before you proceed!" << endl;
    cout << endl;
    cout << "GAME RULES :" << endl;
    cout << "1. This game mode requires two players" << endl;
    cout << "2. Each player will type a word for the other to guess" << endl;
    cout << "3. You need to guess the word by trying one alphabet or the whole word" << endl;
    cout << "4. You have 4 chances per round" << endl;
    cout << "5. If you fail to guess after all chances, your opponent scores" << endl;
    cout << "6. Correct guesses earn you 4 points" << endl;
    cout << "7. The game continues until someone reaches 5 points" << endl;
    cout << "8. The game ends with a ranking display" << endl;
    cout << endl;
    cout << "GOOD LUCK!!" << endl;

    wait();
    system("cls");
}

void displayTurnMessage(const string& playerName, const string& opponentName) {
    cout << "Player " << playerName << "," << endl;
    cout << "kindly face away while " << opponentName << " is typing." << endl;
    wait();
    system("cls");
}

void displayHintAndWord(const string& hint, const string& maskedWord, int chances) {
    cout << "Hi, " << hint << endl;
    cout << "The word given by " << hint << " is something about => " << maskedWord << endl;
    cout << "It consists of " << maskedWord.length() << " alphabets." << endl;
    cout << "Make sure your answer in UPPERCASE !!" << endl;
    cout << "You have " << chances << " chance(s)." << endl;
    cout << "Try an alphabet [1] or the whole word [2] ? Your choice: ";
}

void updateScore(Player& player, bool win) {
    if (win) player.setScore(player.getScore() + 4);
}

string Word::getMaskedWord() const {
    string masked = secretWord;
    for (char& c : masked) {
        if (c != '*') c = '*';
    }
    return masked;
}
