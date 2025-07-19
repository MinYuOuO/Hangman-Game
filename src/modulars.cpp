#include "function.h"

#include <conio.h>
#include <ctime>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

// ============================================================================
//                             Utility Functions
// ============================================================================

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

void printCentered(string text, int width, char fillChar = ' ') {
    int padding = (width - text.length()) / 2;
    cout << setfill(fillChar) << setw(padding + text.length()) << text << setw(width - (padding + text.length())) << "" << endl;
}

// ============================================================================
//                              Input Functions
// ============================================================================

int input(int limit) {
    int insert;
    while (true) {
        try {
            cin >> insert;
            if (cin.fail() || insert < 0 || insert > limit) {
                cout << "Invalid input. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return insert;
            }
        } catch(const std::exception& e) {
            cerr << e.what() << '\n';
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

// ============================================================================
//                             Game Display Functions
// ============================================================================

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
    cout << "3. You need to guess the word by trying one alphabet" << endl;
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
    cout << "3. You need to guess the word by trying one alphabet" << endl;
    cout << "4. You have chances 5 to guess the word per round" << endl;
    cout << "5. If you fail to guess after all chances, your opponent scores" << endl;
    cout << "6. The game continues until someone reaches 3 points" << endl;
    cout << "7. The game ends with a ranking display" << endl;
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
    cout << "     " << (chances <= 5 ? "O" : " ") << "   |" << setw(30) << "Chances left: " << chances << endl;
    cout << "    " << (chances <= 4 ? "/" : " ") << (chances <= 3 ? "|" : " ") << (chances <= 2 ? "/" : " ") << "  |" << setw(30) << "Word: " << masked << endl;
    cout << "    " << (chances <= 1 ? "/ ": "  ") << (chances <= 0 ? "/": " ") << "  |" << endl;
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

// ============================================================================
//                                  Classes
// ============================================================================

// ----------------------------------------------------------------------------
// Music Player
// ----------------------------------------------------------------------------

MusicPlayer::MusicPlayer() {
    backgroundMusic = "./audio/background_music.wav";
}

void MusicPlayer::playMusic() {
    if (!music.openFromFile(backgroundMusic)) {
        cerr << "Failed to load background music." << endl;
        return;
    }
        
    music.setLooping(true);
    music.play();
}

void MusicPlayer::playSound(string audio) {
    static sf::SoundBuffer buffer;
    static sf::Sound sound(buffer);
    static bool loaded;

    loaded = buffer.loadFromFile(audio); // this function have bug, dont touch!!!!!

    if (loaded) {
        sound.setBuffer(buffer);
        sound.play();
    }
}

MusicPlayer::~MusicPlayer() {
    music.stop();
}

// ----------------------------------------------------------------------------
// Word Class
// ----------------------------------------------------------------------------

Word::Word() {
    maskedWord = "";
}

string Word::getMaskedWord() const {
    string masked = secretWord;
    for (char& c : masked) {
        if (c != '*') c = '*';
    }
    return masked;
}

bool Word::processGuess(int& chances) {
    char c = '\0';
    cout << "Letter: ";
    c = input(c);

    MusicPlayer soundEffect;
    
    bool found = false;
    for (size_t i = 0; i < secretWord.length(); ++i) {
        if (secretWord[i] == toupper(c)) {
            maskedWord[i] = secretWord[i];
            found = true;
        }
    }

    if (found) {
        soundEffect.playSound("./audio/Correct.wav");
    } else {
        chances--;
        soundEffect.playSound("./audio/Error.wav");
    }

    return maskedWord == secretWord; 
}

// ----------------------------------------------------------------------------
// Player Class
// ----------------------------------------------------------------------------

Player::Player() {
    name[0] = ""; 
    chances[0] = 5;
}

Player::Player(int p) {
    p -= 1;
    if (p >= 0 && p <= 2) {
        for (int i = 0; i <= p-1; i++) {
            score[i] = 0;
            name[i] = "";
            chances[i] = 5;
        }
    } else {
        cerr << "Invalid player index: " << p << endl;
    }
}

Player::Player(int p, string n) {
    p -= 1;
    score[p] = 0; 
    name[p] = n; 
    chances[p] = 5;
}

int Player::getScore(int i) {
    return ++score[i]; 
};

// ----------------------------------------------------------------------------
// Category Manager
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
// Single Player Game
// ----------------------------------------------------------------------------

void SinglePlayerGame::start() {
    Player player(1, globalUser.name);
    CategoryManager categoryManager;

    while (true) {
        system("cls");
        displayTitle();

        categoryManager.displayCategoryMenu(player.name[0]);
        int category = input(3);
        category -= 1;

        Word room;
        string categoryName = categoryManager.getCategoryName(category);
        room.secretWord = categoryManager.getRandomWord(categoryName);

        wait(0.5);

        cout << "\n" << endl;
        cout << "=====================  C A T E G O R Y   S E L E C T E D  :  " << categoryName << "  =====================" << endl;
        cout << "Before you start, remember the answer consists of 6 alphabets.\n" << endl;
        cout << "Make sure you answer in UPPERCASE ! !\n" << endl;

        wait(1.0);

        room.maskedWord = string(room.secretWord.length(), '*');
        player.chances[0] = 5;
        bool guessed = false;

        while (player.chances[0] > 0 && !guessed) {
            displayHangmanState(categoryName, player.chances[0], room.maskedWord);
            guessed = room.processGuess(player.chances[0]);
        }
        
        displayGameResult(guessed, room.secretWord);

        break;
    }
}

// ----------------------------------------------------------------------------
// Two Player Local Setup Game
// ----------------------------------------------------------------------------

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
        system("cls");
        displayTitle();
        cout << player.name[0] << ": " << player.score[0] << " points" << endl;
        cout << player.name[1] << ": " << player.score[1] << " points" << endl;

        cout << "\n" << endl;

        displayTurnMessage(player.name[currentPlayer], player.name[opponent]);

        displayTitle();
        cout << "Player " << player.name[currentPlayer] << "," << endl;
        cout << "Please enter the word that you want " << player.name[opponent] << " to guess: ";

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

        player.chances[opponent] = 5;
        room.maskedWord = string(room.secretWord.length(), '*');
        bool guessed = false;
        int i;

        while (player.chances[opponent] > 0 && !guessed) {
            displayHangmanState("", player.chances[opponent], room.maskedWord);
            guessed = room.processGuess(player.chances[opponent]);
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

// ----------------------------------------------------------------------------
// Server Game
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
// Client Game
// ----------------------------------------------------------------------------

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

    player.chances[0] = 5;
    room.maskedWord = string(room.secretWord.length(), '*');
    bool guessed = false;

    while (player.chances[0] > 0 && !guessed) {
        displayHangmanState("", player.chances[0], room.maskedWord);
        guessed = room.processGuess(player.chances[0]);
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
