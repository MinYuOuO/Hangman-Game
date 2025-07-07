#include <iostream>
#include "function.h"

using namespace std;

void startMenu() {
    system("cls");
    title();
    cout << "Welcome to Hangman! Please select your mode" << endl;
    cout << "[1] Single player   (vs. computer)" << endl;
    cout << "[2] Two player      (vs. each other)" << endl;
    cout << "Select mode number : ";

    int mode;
    mode = input(2);
    cin.clear();

    system("cls"); // system command clear screen

    title();
    cout << "=====================  M O D E   S E L E C T E D  :  " << mode << "  =====================" << endl;
    
    if (mode == 1) {
        Player player;

        cout << "Please enter your name: ";
        player.name[0] = input("");
        cout << "\nGood luck in your game later, player " << player.name[0] << "!" << endl;

        wait(1.0);

        system("cls");

        title();

        cout << "Player " << player.name[0] << ",\n\n";
        cout << "Please choose a category:\n";
        cout << "[1] Food\n";
        cout << "[2] Country\n";
        cout << "[3] Comp. Science\n\n";
        cout << "Category number : ";

        int category;
        category = input(3);

        wait(1.0);

        cout << "=====================  C A T E G O R Y   S E L E C T E D  :  " << category << "  =====================" << endl;

        cout << "Before you start, remember the answer consists of 6 alphabets.\n" << endl;
        cout << "Make sure you answer in UPPERCASE ! !\n" << endl;

        wait(2.0);

    } else if (mode == 2) {
        Player player(1);

        cout << "Please enter your name" << endl;
        cout << "Player 1 : ";
        player.name[0] = input("");

        cout << "Player 2 : ";
        player.name[1] = input("");
        cout << "\nGood luck in your game later, player " << player.name[0] << " and player " << player.name[1] << "!" << endl;

    } else {
        cout << "Invalid mode..." << endl;
        wait();
        return startMenu();
    }
}

int main() {
    startMenu();
    return 0;
}