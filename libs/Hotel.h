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
    string name;         //ชื่อผู้จอง
    string phone;        //เบอร์ติดต่อผู้จอง
    string roomNo;       //เลขห้อง
    string fileName;     //ชื่อไฟล์เก็บรายการจองห้องพัก
    string roomType;     //ประเภทห้อง
    string hotelName;    //ชื่อโรงแรม
    string checkInDate;  //วันที่เข้าพัก
    string checkOutDate; //วันที่ออกจากโรงแรม
    int floor;           //ชั้น
    int nights;          //จำนวนวันที่ต้องการจอง
    int customer;        //จำนวนผู้เข้าพัก
    int maxCustomer;     //จำนวนผู้เข้าพักสูงสุดต่อห้อง
    float fare = 0.00;   //ราคาจ่ายจริง
    float price = 0.00;  //ราคาต่อห้องต่อคืน
    float addon = 0.00;  //ราคาเพิ่มเติม

    string staffUsername; //ชื่อผู้ใช้งานพนักงาน ได้จากการ Login

    CSVController csv;

public:
    Hotel(string hotelName);
    void setStaffUsername(string staffUsername);

public:
    void add();
    void edit();
    void clear();
    int readCSVRoom(string roomFileName);
    void display();
    void mainMenu();
    void initFileRoom();
    void modify(string targetRoom);
    void deleteRecord(string targetRoom);
    void checkInOut(string targetRoom, string status);
    int checkRoom(string targetRoom, string targetPhone);
    string getDateTime();
};

Hotel::Hotel(string hotelName)
{
    this->hotelName = hotelName;
    this->fileName = hotelName + "booking.dat";
}

void Hotel::initFileRoom()
{
    fstream fileStream;
    fileStream.open(fileName.c_str(), ios::in);
    if (fileStream.fail())
    {
        fileStream.open(fileName.c_str(), ios::out);
        fileStream.close();
    }
}

int Hotel::readCSVRoom(string roomFileName)
{
    csv.readCSV();
    return 0;
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
    cout << "4. Export booking list (CSV)" << endl;
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
        if (csv.exportCSV(fileName, hotelName + ".csv") == 1)
        {
            cout << "Exported successfully" << endl;
        }
        else
        {
            cout << "Export failed" << endl;
        }
        getch();
        mainMenu();
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
    ifstream fileIn("room.txt", ios::in);
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
    bool found = false;
    while (fileIn >> roomFound >> price >> roomType >> maxCustomer >> addon >> floor)
    {

        if (checkRoom(roomNo, phone) == 1)
        {
            cout << "Room is already booked" << endl;
            cout << "Press any key to continue...";
            getch();
            mainMenu();
        }

        if (roomNo == roomFound)
        {
            found = true;
            fare = nights * price;
            addon = (customer > maxCustomer) ? ((addon * price) * (customer - maxCustomer)) * nights : 0.00;
            cout << "===================" << endl;
            cout << "Room No: " << roomFound << endl;
            cout << "Room Type: " << roomType << endl;
            cout << "Price: " << price << endl;
            cout << "Night: " << nights << endl;
            cout << "Floor: " << floor << endl;
            cout << "Add-on: " << addon << " " << ((customer > maxCustomer) ? (customer - maxCustomer) : 0) << "/customer/nights " << endl;
            cout << "Total: " << fare + addon << endl;
            checkInDate = "-";
            checkOutDate = "-";
            cout << "Confirm booking? (Y/N): ";
            key = getch();
            if (key == 'Y' || key == 'y')
            {
                fileOut << roomNo << " " << price << " " << name << " " << phone << " " << customer << " " << (fare + addon) << " " << nights << " " << checkInDate << " " << checkOutDate << " " << staffUsername << " " << maxCustomer << endl;
                cout << "Booking success!" << endl;
            }
            else
            {
                cout << "Booking canceled!" << endl;
            }
            fileIn.close();
            fileOut.close();
            cout << "Press any key to continue...";
            getch();
            mainMenu();
        }
    }
    fileIn.close();
    fileOut.close();
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
        cout << "Booking a room first!" << endl;
        cout << "Press any key to continue..." << endl;
        getch();
        mainMenu();
        return;
    }
    cout << setfill('*') << setw(55) << "*" << endl;
    while (fileIn >> roomNo >> price >> name >> phone >> customer >> fare >> nights >> checkInDate >> checkOutDate >> staffUsername >> maxCustomer)
    {

        cout << "Room No: " << roomNo << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Price/night: " << price << endl;
        cout << "Nights: " << nights << endl;
        cout << "Recommended Customer: " << maxCustomer << endl;
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
    char choice;
    cout << "*************\n";
    cout << "* EDIT MENU *\n";
    cout << "*************\n";
    cout << "1. Modify Booking Record" << endl;
    cout << "2. Checkin Room" << endl;
    cout << "3. Checkout Room" << endl;
    cout << "4. Delete Booking Record" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    choice = getch();
    clear();
    switch (choice)
    {
    case '1':
        cout << "Enter Room No: ";
        cin >> roomNo;
        modify(roomNo);
        break;

    case '2':
        cout << "Enter Room No: ";
        cin >> roomNo;
        checkInOut(roomNo, "checkin");
        break;

    case '3':
        cout << "Enter Room No: ";
        cin >> roomNo;
        checkInOut(roomNo, "checkout");
        break;

    case '4':
        cout << "Enter Room No: ";
        cin >> roomNo;
        deleteRecord(roomNo);
        break;

    case '0':
        mainMenu();
        break;

    default:
        edit();
        break;
    }
}

void Hotel::modify(string targetRoom)
{
    clear();
    fstream fileInOut(fileName.c_str(), ios::in | ios::out);
    ofstream fileOut("temp.dat", ios::in | ios::out);
    if (!fileInOut.is_open())
    {
        cout << "File could not opened. " << fileName.c_str() << endl;
        return;
    }

    bool found = false;

    while (fileInOut >> roomNo >> price >> name >> phone >> customer >> fare >> nights >> checkInDate >> checkOutDate >> staffUsername >> maxCustomer)
    {
        if (roomNo == targetRoom && checkOutDate == "-")
        {
            found = true;
            cout << "****************\n";
            cout << "* Modify Form *\n";
            cout << "****************\n";
            // roomNo = r;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Phone: ";
            cin >> phone;
            cout << "Enter number of customer: ";
            cin >> customer;
            cout << "Enter nights: ";
            cin >> nights;
            fare = nights * price;
            addon = (customer > maxCustomer) ? ((addon * price) * (customer - maxCustomer)) * nights : 0.00;
            fare = fare + addon;
            fileOut << roomNo << " " << name << " " << phone << " " << nights << " " << fare << " " << staffUsername << " " << maxCustomer << endl;
            cout << "💾 Record is modified successfully" << endl;
            cout << "Press any key to continue...";
        }
        else
        {
            fileOut << roomNo << " " << name << " " << phone << " " << nights << " " << fare << " " << staffUsername << " " << maxCustomer << endl;
        }
    }

    fileInOut.close();
    fileOut.close();
    if (!found)
    {
        cout << "Room not found!" << endl;
        cout << "Press any key to continue...";
        remove("temp.dat");
    }
    else
    {
        remove(fileName.c_str());
        rename("temp.dat", fileName.c_str());
    }
    getch();
    mainMenu();
}

void Hotel::deleteRecord(string targetRoom)
{
    clear();
    ifstream fileIn(fileName.c_str(), ios::in);
    ofstream fileOut("temp.dat", ios::out);
    if (!fileIn.is_open())
    {
        cout << "File could not opened. " << fileName.c_str() << endl;
        return;
    }
    while (fileIn >> roomNo >> price >> name >> phone >> customer >> fare >> nights >> checkInDate >> checkOutDate >> staffUsername >> maxCustomer)
    {
        if (roomNo != targetRoom)
        {
            fileOut << roomNo << " " << price << name << " " << phone << " " << customer << " " << fare << " " << nights << " " << checkInDate << " " << checkOutDate << " " << staffUsername << " " << maxCustomer << endl;
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

void Hotel::checkInOut(string targetRoom, string status)
{
    clear();
    fstream fileInOut(fileName.c_str(), ios::in | ios::out);
    ofstream fileOut("temp.dat", ios::out);
    if (!fileInOut.is_open())
    {
        cout << "File could not opened. " << fileName.c_str() << endl;
        return;
    }

    bool found = false;

    while (fileInOut >> roomNo >> price >> name >> phone >> customer >> fare >> nights >> checkInDate >> checkOutDate >> staffUsername >> maxCustomer)
    {
        if (roomNo == targetRoom && (checkInDate == "-" || checkOutDate == "-"))
        {
            found = true;
            if (status == "checkin")
            {
                checkInDate = getDateTime();
                fileOut << roomNo << " " << price << " " << name << " " << phone << " " << customer << " " << fare << " " << nights << " " << checkInDate << " " << checkOutDate << " " << staffUsername << " " << maxCustomer << endl;
                cout << "💾 Record is modified successfully" << endl;
                cout << "Press any key to continue...";
            }
            else
            {
                if (checkInDate != "-")
                {
                    checkOutDate = getDateTime();
                    fileOut << roomNo << " " << price << " " << name << " " << phone << " " << customer << " " << fare << " " << nights << " " << checkInDate << " " << checkOutDate << " " << staffUsername << " " << maxCustomer << endl;
                    cout << "💾 Record is modified successfully" << endl;
                    cout << "Press any key to continue...";
                }
                else
                {
                    cout << "Room is not checked in yet!" << endl;
                    cout << "Press any key to continue...";
                }
            }
        }
        else
        {
            fileOut << roomNo << " " << price << " " << name << " " << phone << " " << customer << " " << fare << " " << nights << " " << checkInDate << " " << checkOutDate << " " << staffUsername << " " << maxCustomer << endl;
        }
    }
    fileInOut.close();
    fileOut.close();
    remove(fileName.c_str());
    rename("temp.dat", fileName.c_str());
    if (!found)
    {
        cout << "Room not found!" << endl;
        cout << "Press any key to continue...";
        remove("temp.dat");
    }

    getch();
    mainMenu();
}

int Hotel::checkRoom(string targetRoom, string targetPhone)
{
    int flag = 0;
    ifstream fin(fileName.c_str(), ios::in);
    int userCouter = 0;
    string roomFound = "";
    string foundPhone = "";
    while (fin >> roomFound >> price >> name >> foundPhone >> customer >> fare >> nights >> checkInDate >> checkOutDate >> staffUsername >> maxCustomer)
    {
        if (foundPhone == targetPhone && checkOutDate == "-")
        {
            userCouter++;
            if (userCouter > 2)
            {
                flag = 1;
                break;
            }
        }
        if (roomFound == targetRoom && checkOutDate == "-")
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