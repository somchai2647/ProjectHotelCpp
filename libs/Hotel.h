#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include "CSVController.h"

using namespace std;

class Hotel
{
private:
    string hotelName;              //ชื่อโรงแรม
    string roomNo;                 //เลขห้อง
    string name;                   //ชื่อผู้จอง
    string phone;                  //เบอร์ติดต่อผู้จอง
    int nights;                    //จำนวนวันที่ต้องการจอง
    float fare = 0.00;             //ราคาจ่ายจริง
    float price = 0.00;            //ราคาต่อห้องต่อคืน
    string fileName = "hotel.dat"; //ชื่อไฟล์

    string roomtype;    //ประเภทห้อง
    float addon = 0.00; //ราคาเพิ่มเติม
    int floor;          //ชั้น

    string staffUsername; //ชื่อผู้ใช้งานพนักงาน ได้จากการ Login

    CSVController csv;

public:
    Hotel(string hotelName, float price);
    void setStaffUsername(string staffUsername);

public:
    void add();
    void edit();
    void clear();
    int readCSV();
    void display();
    void mainMenu();
    void modify(string targetRoom);
    int checkRoom(string targetRoom);
    void deleteRecord(string targetRoom);
};
int Hotel::readCSV()
{
    csv.readCSV();
    return 0;
}

Hotel::Hotel(string hotelName, float price)
{
    this->hotelName = hotelName;
    this->price = price;
}

void Hotel::mainMenu()
{
    clear();
    char choice;
    cout << "*************\n";
    cout << "* MAIN MENU *\n";
    cout << "*************\n";
    cout << "1. Add a booking" << endl;
    cout << "2. Edit booking list" << endl;
    cout << "3. Check booking list" << endl;
    cout << "4. Read CSV TEST" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    choice = getch();
    switch (choice)
    {
    case '1':
        add();
        break;
    case '2':
        edit();
        break;
    case '3':
        display();
        break;
    case '4':
        // readCSV();
        break;
    case '0':
        exit(0);
    default:
        cout << "Invalid Choice" << endl;
    }
}

void Hotel::add()
{
    clear();
    ofstream fileOut(fileName.c_str(), ios_base::app);
    cout << "****************\n";
    cout << "* Booking Form *\n";
    cout << "****************\n";
    char key;
    cout << "Enter Room No: ";
    cin >> roomNo;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Phone: ";
    cin >> phone;
    cout << "Enter nights: ";
    cin >> nights;
    fare = nights * price;

    if (checkRoom(roomNo) == 1)
    {
        cout << "Room is already booked" << endl;
        getch();
        mainMenu();
    }
    else
    {
        fileOut << roomNo << " " << name << " " << phone << " " << nights << " " << fare << " " << staffUsername << endl;
        cout << "💾 Room is booked successfully" << endl;
        cout << "Press any key to continue...";
        getch();
        fileOut.close();
        mainMenu();
    }
}

void Hotel::display()
{
    clear();
    ifstream fileIn(fileName.c_str(), ios::in);
    if (!fileIn.is_open())
    {
        cout << "File could not opened. " << fileName.c_str() << endl;
        return;
    }
    cout << setfill('*') << setw(55) << "*" << endl;
    while (fileIn >> roomNo >> name >> phone >> nights >> fare >> staffUsername)
    {

        cout << "Room No: " << roomNo << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Price/day: " << price << endl;
        cout << "nights: " << nights << endl;
        cout << "Fare: " << fare << endl;
        cout << "Staff: " << staffUsername << endl;
        cout << endl;
        cout << setfill('*') << setw(55) << "*" << endl;
    }

    fileIn.close();
    cout << "Press any key to main menu...";
    getch();
    mainMenu();
}

void Hotel::edit()
{
    clear();
    int choice;
    cout << "*************\n";
    cout << "* EDIT MENU *\n";
    cout << "*************\n";
    cout << "1. Modify Booking Record" << endl;
    cout << "2. Delete Booking Record" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    clear();
    cout << "Enter Room No: ";
    cin >> roomNo;
    switch (choice)
    {
    case 1:
        modify(roomNo);
        break;

    case 2:
        deleteRecord(roomNo);
        break;

    default:
        break;
    }
}

void Hotel::modify(string targetRoom)
{
    clear();
    fstream fileInOut(fileName.c_str(), ios::in | ios::out);
    ofstream fileOut("temp.dat", ios::out);
    if (!fileInOut.is_open())
    {
        cout << "File could not opened. " << fileName.c_str() << endl;
        return;
    }

    int found = 0;

    while (fileInOut >> roomNo >> name >> phone >> nights >> fare >> staffUsername)
    {
        if (roomNo == targetRoom)
        {
            found = 1;
            cout << "****************\n";
            cout << "* Modify Form *\n";
            cout << "****************\n";
            // roomNo = r;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Phone: ";
            cin >> phone;
            cout << "Enter nights: ";
            cin >> nights;
            fare = nights * price;
            fileOut << roomNo << " " << name << " " << phone << " " << nights << " " << fare << " " << staffUsername << endl;
            cout << "💾 Record is modified successfully" << endl;
            cout << "Press any key to continue...";
        }
        else
        {
            fileOut << roomNo << " " << name << " " << phone << " " << nights << " " << fare << " " << staffUsername << endl;
        }
    }
    fileInOut.close();
    fileOut.close();
    remove(fileName.c_str());
    rename("temp.dat", fileName.c_str());
    getch();
    mainMenu();
}

void Hotel::deleteRecord(string targetRoom)
{
    clear();
    string room, name, phone, nights, fare;
    ifstream fileIn(fileName.c_str(), ios::in);
    ofstream fileOut("temp.dat", ios::out);
    if (!fileIn.is_open())
    {
        cout << "File could not opened. " << fileName.c_str() << endl;
        return;
    }
    while (fileIn >> room >> name >> phone >> nights >> fare)
    {
        if (room != targetRoom)
        {
            fileOut << room << " " << name << " " << phone << " " << nights << " " << fare << endl;
        }
    }
    fileIn.close();
    fileOut.close();
    remove(fileName.c_str());
    rename("temp.dat", fileName.c_str());
    cout << "Record is deleted successfully" << endl;
    cout << "Press any key to main menu...";
    getch();
    mainMenu();
}

int Hotel::checkRoom(string targetRoom)
{
    int flag = 0;
    string room, name, phone, nights, fare;
    ifstream fin(fileName.c_str(), ios::in);
    while (fin >> room >> name >> phone >> nights >> fare)
    {
        if (room == targetRoom)
        {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

void Hotel::setStaffUsername(string staffUsername)
{
    this->staffUsername = staffUsername;
}

void Hotel::clear()
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}
