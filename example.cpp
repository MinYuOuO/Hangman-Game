// Full Hangman Game for VS Code with SFML - Single & Two Player Modes

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
using namespace std;

void displayTitle() {
    cout << "==============================================================\n";
    cout << "===========================  H  A  N  G  M  A  N  =============\n";
    cout << "==============================================================\n\n";
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

int main() {
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("background_music.wav")) {
        cerr << "Failed to load background music.\n";
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic.play();
    }

    int totalScore = 0;
    char playAgain;

    do {
        cout << "\033[2J\033[1;1H";
        displayTitle();
        int mode;
        cout << "[1] Single player (vs. computer)\n";
        cout << "[2] Two player (vs. each other)\n\n";
        cout << "Select mode number: ";
        cin >> mode;
        cin.ignore();

        if (mode == 1) {
            string player;
            cout << "\nEnter your name: ";
            getline(cin, player);
            waitForKey();
            cout << "\033[2J\033[1;1H";

            displayTitle();
            int cat;
            cout << "Choose a category:\n[1] Food\n[2] Country\n[3] Comp. Science\nCategory number: ";
            cin >> cat;
            cin.ignore();
            cout << "\033[2J\033[1;1H";

            displayTitle();
            cout << "RULES:\nYou have 4 chances to guess a 5-letter word.\nUse UPPERCASE.\n";
            waitForKey();
            cout << "\033[2J\033[1;1H";

            string secretWord = "BREAD";
            string masked(secretWord.length(), '*');
            int chances = 4;
            bool guessed = false;

            while (chances > 0 && !guessed) {
                displayTitle();
                cout << "Chances left: " << chances << "\nWord: " << masked << "\n";
                cout << "[1] Guess letter  [2] Guess full word: ";
                string opt;
                cin >> opt;

                if (opt == "1") {
                    char c;
                    cout << "Letter: ";
                    cin >> c;
                    bool found = false;
                    for (int i = 0; i < secretWord.length(); i++) {
                        if (secretWord[i] == toupper(c)) {
                            masked[i] = secretWord[i];
                            found = true;
                        }
                    }
                    if (!found) chances--;
                } else if (opt == "2") {
                    string guess;
                    cout << "Your guess: ";
                    cin >> guess;
                    if (guess == secretWord) {
                        masked = secretWord;
                        guessed = true;
                    } else {
                        chances--;
                    }
                }
                guessed = (masked == secretWord);
                cout << "\033[2J\033[1;1H";
            }

            displayTitle();
            if (guessed) {
                cout << "You Win! The word was: " << secretWord << "\n";
                totalScore += 4;
            } else {
                cout << "You Lose! The word was: " << secretWord << "\n";
            }
        } 
        else if (mode == 2) {
            string player1, player2;
            cout << "Enter Player 1 name: "; getline(cin, player1);
            cout << "Enter Player 2 name: "; getline(cin, player2);

            cout << player1 << ", enter a secret word (UPPERCASE): ";
            string secretWord;
            cin >> secretWord;
            cin.ignore();
            cout << "\033[2J\033[1;1H";

            string masked(secretWord.length(), '*');
            int chances = 4;
            bool guessed = false;

            while (chances > 0 && !guessed) {
                displayTitle();
                cout << player2 << "'s Turn - Chances left: " << chances << "\n";
                cout << "Word: " << masked << "\n";
                cout << "[1] Guess letter  [2] Guess full word: ";
                string opt;
                cin >> opt;

                if (opt == "1") {
                    char c;
                    cout << "Letter: ";
                    cin >> c;
                    bool found = false;
                    for (int i = 0; i < secretWord.length(); i++) {
                        if (secretWord[i] == toupper(c)) {
                            masked[i] = secretWord[i];
                            found = true;
                        }
                    }
                    if (!found) chances--;
                } else if (opt == "2") {
                    string guess;
                    cout << "Your guess: ";
                    cin >> guess;
                    if (guess == secretWord) {
                        masked = secretWord;
                        guessed = true;
                    } else {
                        chances--;
                    }
                }
                guessed = (masked == secretWord);
                cout << "\033[2J\033[1;1H";
            }

            displayTitle();
            if (guessed) {
                cout << player2 << " wins! The word was: " << secretWord << "\n";
                totalScore += 4;
            } else {
                cout << player2 << " loses. The word was: " << secretWord << "\n";
            }
        }
        else {
            cout << "Invalid mode selected.\n";
            break;
        }

        cout << "\nScore: " << totalScore << "\nPlay again? (Y/N): ";
        cin >> playAgain;
        playAgain = toupper(playAgain);
        cin.ignore();

    } while (playAgain == 'Y');

    cout << "\033[2J\033[1;1H";
    displayTitle();
    displayExitMessage();
    return 0;
}
