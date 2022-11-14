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
    string phone;                  //เบอร์ติดต่อผู้จอง
    string name;                   //ชื่อผู้จอง
    string roomNo;                 //เลขห้อง
    string fileName = "hotel.dat"; //ชื่อไฟล์
    string roomType;               //ประเภทห้อง
    string hotelName;              //ชื่อโรงแรม
    string checkInDate;            //วันที่เข้าพัก
    string checkOutDate;           //วันที่ออกจากโรงแรม
    int nights;                    //จำนวนวันที่ต้องการจอง
    int customer;                  //จำนวนผู้เข้าพัก
    int maxCustomer;               //จำนวนผู้เข้าพักสูงสุดต่อห้อง
    float fare = 0.00;             //ราคาจ่ายจริง
    float price = 0.00;            //ราคาต่อห้องต่อคืน
    float addon = 0.00;            //ราคาเพิ่มเติม
    int floor;                     //ชั้น

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
    void deleteRecord(string targetRoom);
    int checkRoom(string targetRoom, string targetPhone);
    string getDateTime();
};

int Hotel::readCSV()
{
    csv.readCSV();
    return 0;
}

Hotel::Hotel(string hotelName, float price)
{
    this->hotelName = hotelName;
    // this->price = price;
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
    ifstream fileIn("room.dat", ios::in);
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
    cout << "Enter number of customer: ";
    cin >> customer;
    cout << "Enter nights: ";
    cin >> nights;

    string roomFound = "";
    float addon = 0.00;
    int floor = 1;
    bool found = false;

    while (fileIn >> roomFound >> price >> roomType >> maxCustomer >> addon >> floor)
    {
        if (roomNo == roomFound)
        {
            found = true;
            fare = nights * price;
            addon = (customer > maxCustomer) ? ((addon * price) * (customer - maxCustomer)) * nights : 0.00;
            cout << "===================" << endl;
            cout << "Room No: " << roomNo << endl;
            cout << "Room Type: " << roomType << endl;
            cout << "Price: " << price << endl;
            cout << "Night: " << nights << endl;
            cout << "Floor: " << floor << endl;
            cout << "Add-on: " << addon << " " << (customer - maxCustomer) << " /customer/nights " << endl;
            cout << "Total: " << fare + addon << endl;
            checkInDate = "-";
            checkOutDate = "-";
            cout << "Confirm booking? (Y/N): ";
            key = getch();
            if (key == 'Y' || key == 'y')
            {
                fileOut << roomNo << " " << name << " " << phone << " " << customer << " " << (fare + addon) << " " << nights << " " << checkInDate << " " << checkOutDate << " " << staffUsername << endl;
                cout << "Booking success!" << endl;
                cout << "Press any key to continue...";
                getch();
                mainMenu();
            }
            else
            {
                cout << "Booking canceled!" << endl;
                cout << "Press any key to continue...";
                getch();
                mainMenu();
            }
        }
    }
    if (!found)
    {
        cout << "Room not found!" << endl;
        cout << "Press any key to continue...";
        getch();
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
    while (fileIn >> roomNo >> name >> phone >> customer >> fare >> nights >> checkInDate >> checkOutDate >> staffUsername)
    {

        cout << "Room No: " << roomNo << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Price/night: " << price << endl;
        cout << "nights: " << nights << endl;
        cout << "Customers: " << customer << endl;
        cout << "Fare: " << fare << endl;
        cout << "Check-in Date: " << checkInDate << endl;
        cout << "Check-out Date: " << checkOutDate << endl;
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

int Hotel::checkRoom(string targetRoom, string targetPhone)
{
    int flag = 0;
    string room, name, phone, nights, fare;
    ifstream fin(fileName.c_str(), ios::in);
    int userCouter = 0;
    while (fin >> room >> name >> phone >> nights >> fare)
    {
        if (phone == targetPhone)
        {
            userCouter++;
            if (userCouter > 2)
            {
                flag = 1;
                break;
            }
        }
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

string Hotel::getDateTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string datetime = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday) + "|" + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    return datetime;
}