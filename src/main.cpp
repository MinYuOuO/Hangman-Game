#include <iostream>
#include "function.h"

using namespace std;

void startMenu() {
    title();
    cout << "Welcome to Hangman! Please select your mode" << endl;
    cout << "[1] Single player   (vs. computer)" << endl;
    cout << "[2] Two player      (vs. each other)" << endl;
    cout << "Select mode number : ";

    int mode;
    mode = input(mode);

    system("cls"); // system command clear screen

    title();
    cout << "=====================  M O D E   S E L E C T E D  :  " << mode << "  =====================" << endl;
    
    if (mode == 1) {
        Player player(1);

        cout << "Please enter your name: ";
        player.name = input(player.name);
        cout << "\nGood luck in your game later, player " << player.name << "!" << endl;

        wait(2.0);

        system("cls");

        title();

        cout << "Player " << player.name << ",\n\n";
        cout << "Please choose a category:\n";
        cout << "[1] Food\n";
        cout << "[2] Country\n";
        cout << "[3] Comp. Science\n\n";
        cout << "Category number : ";

        int category;
        category = input(category);

        wait(1.0);

        cout << "=====================  C A T E G O R Y   S E L E C T E D  :  " << category << "  =====================" << endl;

        cout << "Before you start, remember the answer consists of 6 alphabets.\n" << endl;
        cout << "Make sure you answer in UPPERCASE ! !\n" << endl;

        wait(5.0);

    } else if (mode == 2) {
        Player player1(1);
        Player player2(2);

        cout << "Please enter your name\n";
        cout << "Player 1 : ";
        player1.name = input(player1.name);

        cout << "Player 2 : ";
        player2.name = input(player2.name);
        cout << "\nGood luck in your game later, player " << player1.name << " and player " << player2.name << "!" << endl;

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