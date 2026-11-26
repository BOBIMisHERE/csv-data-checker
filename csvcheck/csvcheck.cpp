// csvcheck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

// Counts how many columns a CSV line has (number of commas + 1)
int CountColumns(const std::string& line)
{
    int columns = 1;
    for (char c : line)
    {
        if (c == ',')
        {
            ++columns;
        }
    }
    return columns;
}

int main(int argc, char* argv[])
{
    // minimum required is 2 arguments
    if (argc < 2)
    {
        std::cout << "Usage: csvcheck <file.csv>\n";
        return 1;
    }

    // trying to open the file
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cout << "Error: could not open " << argv[1] << "\n";
        return 1;
    }

    // read the file one line at a time and print it with the row number
    std::string line;
    int rowNumber = 0;
    int expectedColumns = 0;
    int problemCount = 0;

    while (std::getline(file, line))
    {
        ++rowNumber;

        // row 1 is the header deciding how many columns every row must have
        if (rowNumber == 1)
        {
            expectedColumns = CountColumns(line);
            continue;
        }

        int columns = CountColumns(line);
        if (columns != expectedColumns)
        {
            std::cout << "Row " << rowNumber << ": expected " << expectedColumns
                      << " columns but found " << columns << "\n";
            ++problemCount;
        }
        std::cout << "Row " << rowNumber << ": " << line << "\n";
    }

    if (rowNumber == 0)
    {
        std::cout << "Error: the file is empty\n";
        return 1;
    }

    int dataRows = rowNumber - 1;
    std::cout << problemCount << " problems found in " << dataRows << " rows\n";
    return (problemCount == 0) ? 0 : 1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
