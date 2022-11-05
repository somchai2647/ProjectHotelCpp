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
    CSVController(string fileName)
    {
        this->fileName = fileName;
    }

public:
    int readCSV();
};

int CSVController::readCSV()
{
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream fileIn("hotelRoom.csv", ios::in);
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