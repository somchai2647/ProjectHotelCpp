#include <iostream>
#include <string>
#include <fstream>
#include "libs/Hotel.h"

using namespace std;

void clear();
void intro();
int adminLogin();
int readCSV();

Hotel hotel("myHotel", 700.00);

int main()
{
    intro();
    adminLogin();
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

    ifstream fileIn("staffList.txt", ios::in);
    if (!fileIn)
    {
        cout << "Error opening file";
        exit(1);
    }

    string readUsername, readPassword;
    bool foundUser = false;
    while (fileIn >> readUsername >> readPassword)
    {
        if (username == readUsername && password == readPassword)
        {
            hotel.setStaffUsername(readUsername);
            foundUser = true;
            break;
        }
    }

    if (!foundUser)
    {
        cout << "Login Failed";
        getch();
        return main();
    }
    return 0;
}

void clear()
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}
