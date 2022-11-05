//https://java2blog.com/read-csv-file-in-cpp/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class CSVContoller
{
private:
    /* data */
    string fileName;
public:
    CSVContoller(string fileName);
    ~CSVContoller();
};

CSVContoller::CSVContoller(string fileName)
{
}

CSVContoller::~CSVContoller()
{
}

CSVContoller::readCSV()
{
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream fileIn(fileName.c_str(), ios::in);
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