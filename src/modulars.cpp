#include <conio.h>
#include <ctime>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <SFML/Audio.hpp>
#include "function.h"

using namespace std;

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

void printCentered(string text, int width, char fillChar = ' ') {
    int padding = (width - text.length()) / 2;
    cout << setfill(fillChar) << setw(padding + text.length()) << text << setw(width - (padding + text.length())) << "" << endl;
}

void displayTitle() {
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

void displayRules() {
    cout << "Now, let's learn the rules of playing hangman before you proceed!" << endl;
    cout << endl;
    cout << "GAME RULES :" << endl;
    cout << "1. This game mode requires 1 player only" << endl;
    cout << "2. The computer will generate a word from your chosen category" << endl;
    cout << "3. You need to guess the word by trying one alphabet or the whole word" << endl;
    cout << "4. You have 5 chances to guess the word" << endl;
    cout << "5. If you fail to guess the word after all chances, the game ends" << endl;
    cout << endl;
    cout << "GOOD LUCK!!" << endl;

    wait();
    system("cls");
}

void displayTwoPlayerRules() {
    system("cls");
    displayTitle();

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

void displayHangmanState(const string& categoryName, int chances, const string& masked) {
    system("cls");
    displayTitle();
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
    displayTitle();
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

void playCorrectSound() {
    static sf::SoundBuffer buffer;
    static sf::Sound correctSound(buffer); 

    static bool loaded = buffer.loadFromFile("audio/Correct.wav");
    if (loaded) {
        correctSound.setBuffer(buffer);
        correctSound.play();
    }
}

void playErrorSound() {
    static sf::SoundBuffer buffer;
    static sf::Sound errorSound(buffer);

    static bool loaded = buffer.loadFromFile("audio/Error.wav");
    if (loaded) {
        errorSound.setBuffer(buffer);
        errorSound.play();
    }

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
            playCorrectSound();
        }
    }

    if (!found) {
        chances--;
        playErrorSound();
    }

    return masked == secretWord; 
}

Player::Player() {
    name[0] = ""; 
    chances[0] = 5; 
}

Player::Player(int p) {
    if (p >= 0 && p <= 2) {
        for (int i = 0; i <= p-1; i++) {
            score[i] = 0;
            name[i] = "";
            chances[i] = 4;
        }
    } else {
        cerr << "Invalid player index: " << p << endl;
    }
}

Player::Player(int p, string n) {
    score[p-1] = 0; 
    name[p-1] = n; 
    chances[p-1] = 5; 
}

int Player::getScore(int i) {
    return ++score[i]; 
};

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

void CategoryManager::displayCategoryMenu(const string& playerName) {
    system("cls");
    displayTitle();
    cout << "" << endl;
    cout << "Player " << playerName << ",\n" << endl;
    cout << "Please choose a category:" << endl;

    for (size_t i = 0; i < getCategoryList().size(); ++i) {
        cout << "[" << i + 1 << "] " << getCategoryName(i) << endl;
    }

    cout << "Category number : ";
}

string Word::getMaskedWord() const {
    string masked = secretWord;
    for (char& c : masked) {
        if (c != '*') c = '*';
    }
    return masked;
}

void SinglePlayerGame::start() {
    Player player(1, globalUser.name);
    CategoryManager categoryManager;

    while (true) {
        system("cls");
        displayTitle();

        cout << "\nGood luck in your game later, player " << player.name[0] << "!" << endl;

        wait(1.0);

        categoryManager.displayCategoryMenu(player.name[0]);
        int category = input(3) - 1;

        Word room;
        string categoryName = categoryManager.getCategoryName(category);
        room.secretWord = categoryManager.getRandomWord(categoryName);

        wait(1.0);

        cout << "\n" << endl;
        cout << "=====================  C A T E G O R Y   S E L E C T E D  :  " << categoryName << "  =====================" << endl;
        cout << "Before you start, remember the answer consists of 6 alphabets.\n" << endl;
        cout << "Make sure you answer in UPPERCASE ! !\n" << endl;

        wait(2.0);

        string masked(room.secretWord.length(), '*');

        int chances = 5;
        bool guessed = false;
        int wrongGuesses;

        while (chances > 0 && !guessed) {
            displayHangmanState(categoryName, chances, masked);
            guessed = processGuess(room.secretWord, masked, chances);
        }
        
        displayGameResult(guessed, room.secretWord);

        break;
    }
}

void TwoPlayerSetupGame::start() {
    Player player(2);

    displayTitle();
    cout << "Please enter your name" << endl;
    cout << "Player 1 : ";
    player.name[0] = input("");
    cout << "\n\nPlayer 2 : ";
    player.name[1] = input("");
    cout << "\nGood luck in your game later, player " << player.name[1] << " and player " << player.name[0] << "!" << endl;

    wait();

    int currentPlayer = 0;
    int opponent = 1;

    while (player.score[0] < 2 && player.score[1] < 2) {
        displayTitle();
        cout << player.name[0] << ": " << player.score[0] << " points" << endl;
        cout << player.name[1] << ": " << player.score[1] << " points" << endl;

        displayTurnMessage(player.name[currentPlayer], player.name[opponent]);

        cout << "Player " << player.name[currentPlayer] << "," << endl;
        cout << "Please enter the word that you want " << player.name[opponent] << " to guess." << endl;
        cout << "TAKE NOTE => Answer MUST be in UPPERCASE" << endl;

        Word room;

        while (true) {
            room.secretWord = input("");
            transform(room.secretWord.begin(), room.secretWord.end(), room.secretWord.begin(), ::toupper);
            if (room.secretWord.length() >= 1) break;
            cout << "Word must be at least 1 letter. Try again." << endl;
        }

        cout << "You entered = [" << room.secretWord << "]" << endl;
        wait(1.0);
        system("cls");

        int chances = 5;
        string masked(room.secretWord.length(), '*');
        bool guessed = false;
        int i;

        while (chances > 0 && !guessed) {
            displayHangmanState("", chances, masked);
            guessed = processGuess(room.secretWord, masked, chances);
        }

        displayGameResult(guessed, room.secretWord);
        if (guessed) {++player.score[opponent];} else {++player.score[currentPlayer];}
        
        swap(currentPlayer, opponent);

        system("cls");
    }

    displayTitle();
    cout << "Game Over! Final Scores:" << endl;
    cout << player.name[0] << ": " << player.score[0] << " points" << endl;
    cout << player.name[1] << ": " << player.score[1] << " points" << endl;
    wait();
}

ServerGame::ServerGame() : server(54000) {}

void ServerGame::startServer() {
    server.start();

    while (!server.connected) {
        server.listenForDiscovery();
        server.update();
    }
}

void ServerGame::start() {
    startServer();
    wait(1);

    Player player(2);
    player.name[0] = globalUser.name;

    while (!server.waitForAck()) {
        server.sendMessage(globalUser.name);
    }
    
    string clientName;
    do {
        clientName = server.update();
        wait(0.1);
    } while (clientName == "false" || clientName.empty() || clientName == "ACK");

    player.name[1] = clientName;

    server.sendingAck();
    wait(1.0);

    clientName.clear();

    system("cls");
    displayTitle();
    cout << "\n\n" << endl;
    cout << "Player " << player.name[0] << "," << endl;
    cout << "Please enter the word that you want " << player.name[1] << " to guess:";

    Word room;

    while (true) {
        room.secretWord = input("");
        transform(room.secretWord.begin(), room.secretWord.end(), room.secretWord.begin(), ::toupper);
        if (room.secretWord.length() >= 1) break;
        cout << "Word must be at least 1 letter. Try again." << endl;
    }

    while (!server.waitForAck())
    {
        server.sendMessage(room.secretWord);
    }

    string message;
    do {
        message = server.update();
        wait(0.1);
    } while (message == "false" || message.empty() || clientName == "ACK");

    system("cls");
    displayTitle();
    printCentered(message, 77, '-');

    server.sendingAck();

    wait();
}

ClientGame::ClientGame() : client(53000) {}

void ClientGame::startServer() {
    const int maxRetries = 15;
    int attempts = 0;

    while (attempts < maxRetries && !client.discoverServer()) {
        cerr << "No response. Retrying (" << (attempts + 1) << "/" << maxRetries << ")..." << endl;
        wait(0.1);
        attempts++;
    }

    if (attempts == maxRetries) {
        cerr << "Server not found: Timeout" << endl;
        wait();
    }

    while (!client.connect()) {
        cerr << "Could not connect to server." << endl;
        wait();
    }
}

void ClientGame::start() {
    startServer();
    wait(1);

    Player player(2);
    player.name[1] = globalUser.name;

    string serverName;
    do {
        serverName = client.update();
        wait(0.1);
    } while (serverName == "false" || serverName.empty() || serverName == "ACK");

    player.name[0] = serverName;
    
    client.sendingAck();
    wait(1.0);

    serverName.clear();

    while (!client.waitForAck()) {
        client.sendMessage(globalUser.name);
    }

    cout << "waiting for " << player.name[0] << endl;
    Word room;

    string message;
    do {
        message = client.update();
        wait(0.1);
    } while (message == "false" || message.empty() || serverName == "ACK");

    room.secretWord = message;
    message.clear();
    client.sendingAck();
    wait(1.0);

    int chances = 5;
    string masked(room.secretWord.length(), '*');
    bool guessed = false;
    int i;

    while (chances > 0 && !guessed) {
        displayHangmanState("", chances, masked);
        guessed = processGuess(room.secretWord, masked, chances);
    }

    while (!client.waitForAck())
    {
        if (guessed) {
            client.sendMessage("You Lose!");
        } else {
            client.sendMessage("You Win!");
        }
    }
    displayGameResult(guessed, room.secretWord);
}
