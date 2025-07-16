#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include "function.h"
#include <locale>
#include <codecvt>
#include <SFML/Audio.hpp>

#include "server.h"

using namespace std;

user globalUser;

int main() {
    system("cls");
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("audio/background_music.wav"))
        cerr << "Failed to load background music." << endl;

    backgroundMusic.setLooping(true);
    backgroundMusic.play();

    displayTitle();
    cout << "\n" << endl;
    printCentered("Hello World!", 77, ' ');
    wait(1.0);
    cout << "\n\n\n\n" << endl;
    printCentered("Game production by Li Wei, Min Yu, Jia Jun and Ren Yi", 77, ' ');
    wait(1.0);
    cout << "\n\n" << endl;

    wstring chinese_string = L"新世纪 - 在虚无中永存";

    // Set locale to support wide output
    setlocale(LC_ALL, "");
    wcout.imbue(locale(""));

    wcout << L"Background Music: " << chinese_string << endl;
    wait(1.5);

    if (filesystem::exists("user.txt")) {
        ifstream inFile("user.txt");
        getline(inFile, globalUser.name);
        inFile.close();
    } else {
        system("cls");
        displayTitle();
        cout << "\n\nPlease enter your name: ";
        globalUser.name = input("");

        ofstream outFile("user.txt");
        outFile << globalUser.name;
        outFile.close();

        cout << "Username saved to file." << std::endl;
    }
    
    wait(1);

    while (true) {
        system("cls");
        displayTitle();
        cout << "Welcome to Hangman! " << globalUser.name << std::endl;
        cout << "Please select your mode" << endl;
        cout << "[1] Single player   (vs. computer)" << endl;
        cout << "[2] Two player      (vs. each other)" << endl;
        cout << "[3] Two player      (LAN)" << endl;
        cout << "[4] Quit Game" << endl;
        cout << "Select mode number : ";

        int mode;
        mode = input(4);
        cin.clear();

        system("cls");
        displayTitle();
        string title = "M O D E   S E L E C T E D  : " + mode;
        printCentered(title, 77, '=');

        if (mode == 1) {
            displayRules();
            Game* game = new SinglePlayerGame();
            game->start();
            delete game;
        } else if (mode == 2) {
            displayTwoPlayerRules();
            Game* game = new TwoPlayerSetupGame();
            game->start();
            delete game;
        } else if (mode == 3) {
            cout << "Please select an option " << endl;
            cout << "[1] Open Room" << endl;
            cout << "[2] Join Game" << endl;

            int select;
            select = input(2);

            if (select == 1) {
                Game* game = new ServerGame();
                game->start();
            } else if (select == 2) {
                Game* game = new ClientGame();
                game->start();
            }
        }else if (mode == 4) {
            displayExitMessage();
            break;
        } else {
            backgroundMusic.stop();
            cout << "Invalid Error, Restarting..." << endl;
            wait();
        }
    }
    return 0;
}