#include <iostream>
#include <fstream>
#include <string>

#include "scanner.h"
#include "testScanner.h"
#include "token.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Input file handling
    fstream inputFile;
    string inputFileName;

    if (argc > 2) {
        // Improper program usage
        cout << "Too many arguments!\nFormat: P1 [file]\n";
        return 0;
    } else if (argc == 2) {
        // Read tokens from file
        inputFileName = argv[1];
        inputFile.open(inputFileName.c_str(), fstream::in);

        // Error check file opening
        if (!inputFile.is_open()) {
            cout << "Error opening file! Ending program.";
            return 0;
        }

        // Run the test scanner with the input file
        testScan(inputFile);
        inputFile.close();

    } else if (argc == 1) {
        // Read arguments from the command line
        string commandLine;
        inputFile.open("Input.txt", fstream::out | fstream::trunc);

        if (!inputFile) {
            cout << "no inputfile...";
            return 0;
        }

        cout << "Input text, press ctrl + d to end input:\n\n";
        while (cin >> commandLine) {
            // Write command line input to file
            inputFile << commandLine;
        }

        inputFile.close();
        inputFile.open("Input.txt", fstream::in);

        testScan(inputFile);
    } else {
        cout << "File/Command line input error.\nFormat: P1 [file]";
    }

    return 0;
}
