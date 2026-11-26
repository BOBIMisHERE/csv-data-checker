// csvcheck.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

// Splits one CSV line into its separate values (split at each comma)
std::vector<std::string> SplitLine(const std::string& line)
{
    std::vector<std::string> fields;
    std::string current;
    for (char c : line)
    {
        if (c == ',')
        {
            fields.push_back(current);
            current.clear();
        }
        else
        {
            current += c;
        }
    }
    fields.push_back(current);
    return fields;
}

// Removes spaces and tabs from both ends, so "  " counts as empty
std::string Trim(const std::string& text)
{
    size_t start = text.find_first_not_of(" \t\r");
    if (start == std::string::npos)
    {
        return "";
    }
    size_t end = text.find_last_not_of(" \t\r");
    return text.substr(start, end - start + 1);
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
    int problemCount = 0;
    std::vector<std::string> headers;
    std::unordered_map<std::string, int> seenIds; // ID -> row where it first appeared

    while (std::getline(file, line))
    {
        ++rowNumber;
        std::vector<std::string> fields = SplitLine(line);

        // row 1 is the header deciding how many columns every row must have
        if (rowNumber == 1)
        {
            headers = fields;
            continue;
        }

        // Check 1: same number of columns as the header
        if (fields.size() != headers.size())
        {
            std::cout << "Row " << rowNumber << ": expected " << headers.size()
                      << " columns but found " << fields.size() << "\n";
            ++problemCount;
            continue; // the other checks need the right column count
        }

        // Check 2: no empty values
        for (size_t i = 0; i < fields.size(); ++i)
        {
            if (Trim(fields[i]).empty())
            {
                std::cout << "Row " << rowNumber << ": column '" << Trim(headers[i])
                          << "' is empty\n";
                ++problemCount;
            }
        }

        // Check 3: the first column (the ID) must be unique
        std::string id = Trim(fields[0]);
        if (!id.empty())
        {
            auto found = seenIds.find(id);
            if (found != seenIds.end())
            {
                std::cout << "Row " << rowNumber << ": duplicate ID '" << id
                          << "' (first seen on row " << found->second << ")\n";
                ++problemCount;
            }
            else
            {
                seenIds[id] = rowNumber;
            }
        }
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
