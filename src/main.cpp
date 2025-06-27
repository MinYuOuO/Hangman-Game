#include <iostream>
#include "function.h"
using namespace std;

//@brief This function will wait for user to continue
void wait() {
    cin.get();
    cout << "--------------------------------------------" << endl;
    cout << '\n' << "Press a key to continue..." << endl;
    cin.get();
}

// start up menu interface
/*void startMenu() {
    cout << "Hello World...";
    wait();
}
*/
int main() {
    runGame();
    return 0;
}