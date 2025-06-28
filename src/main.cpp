#include <iostream>

using namespace std;

/**
 * @brief This function will wait for user to continue
 */
void wait() {
    cout << "--------------------------------------------" << endl;
    cout << '\n' << "Press a key to continue..." << endl;
    cin.get();
}

/**
 * @brief start up menu interface 
 */
void startMenu() {
    cout << "Hello World!" << endl;
    wait();
}

int main()
{
    startMenu();
}