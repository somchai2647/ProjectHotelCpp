// https://java2blog.com/read-csv-file-in-cpp/
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

class CSVController
{
private:
    string fileName;
    vector<string> row;
    vector<vector<string>> content;
    vector<string> split(string str, char delimiter);
    string line, word;

public:
    CSVController()
    {
    }

public:
    int readCSV();
    int exportCSV(string fileName, string exportName);
};

int CSVController::readCSV()
{
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream fileIn("room.csv", ios::in);
    if (!fileIn.is_open())
    {
        cout << "File could not opened. " << fileName.c_str() << endl;
        return 0;
    }

    while (getline(fileIn, line))
    {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        content.push_back(row);
    }
    fileIn.close();

    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            cout << content[i][j] << " ";
        }
        cout << "\n";
    }

    return 1;
}

int CSVController::exportCSV(string fileName, string exportName)
{
    ifstream fileIn(fileName.c_str(), ios::in);
    ofstream fileOut(exportName.c_str(), ios::out);
    if (!fileIn.is_open())
    {
        cout << "File could not opened. " << fileName.c_str() << endl;
        return 0;
    }
    cout << endl;
    string roomNo, price, name, phone, customer, fare, nights, checkInDate, checkOutDate, staffUsername, maxCustomer;
    fileOut << "Room No,Price,Name,Phone,Customer,Fare,Nights,Check In Date,Check Out Date,Staff Username,Max Customer" << endl;
    while (fileIn >> roomNo >> price >> name >> phone >> customer >> fare >> nights >> checkInDate >> checkOutDate >> staffUsername >> maxCustomer)
    {
        cout << roomNo << " " << price << " " << name << " " << phone << " " << customer << " " << fare << " " << nights << " " << checkInDate << " " << checkOutDate << " " << staffUsername << " " << maxCustomer << endl;
        fileOut << roomNo << "," << price << "," << name << "," << phone << "," << customer << "," << fare << "," << nights << "," << checkInDate << "," << checkOutDate << "," << staffUsername << "," << maxCustomer << endl;
    }
    fileIn.close();
    fileOut.close();

    return 1;
}