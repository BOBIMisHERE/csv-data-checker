// csvcheck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

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
    while (std::getline(file, line))
    {
        ++rowNumber;
        std::cout << "Row " << rowNumber << ": " << line << "\n";
    }

    std::cout << rowNumber << " rows read\n";
    return 0;
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
