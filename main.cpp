#include <iostream>
#include <string>
#include "libs/Hotel.h"

using namespace std;

void clear();
void intro();
int adminLogin();
int readCSV();

int main()
{
    Hotel hotel("myHotel", 700);
    intro();
    // adminLogin();

    hotel.mainMenu();

    return 0;
}

void intro()
{
    cout << endl;
    cout << setfill('*') << setw(55) << "*" << endl;
    cout << endl;
    cout << "     C++ Project On Hotel Management System" << endl;
    cout << "🔥Devopleped By: Saksithon Matcharet and Somchai Borioon🔥" << endl;
    cout << endl;
    cout << setfill('*') << setw(55) << "*" << endl;
}

int adminLogin()
{
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    if (username == "admin" && password == "admin")
    {
        cout << "Login Successful" << endl;
        return 0;
    }
    else
    {
        cout << "Login Failed";
        getch();
        clear();
        return main();
    }
}

void clear()
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

