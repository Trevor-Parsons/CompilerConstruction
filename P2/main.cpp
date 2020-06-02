#include <iostream>
#include <fstream>
#include <string>

#include "token.h"
#include "parser.h"
#include "testTree.h"

using namespace std;

fstream inputFile;
bool okParse;

int main(int argc, char* argv[]) {
    // Input file handling
    string inputFileName;

    // Base for parse tree
    node_t *root = NULL;

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
    } else {
        cout << "File/Command line input error.\nFormat: P1 [file]";
    }

    okParse = true;

    // Call the parser function to generate the parse tree
    root = parser();

    // Error check the parse tree to determine where errors occured
    if (errorCheckTree(root) && okParse) {
        cout << "OK PARSE\n\n";
    } else cout << "\nUNSUCCESSFUL PARSE\n\n";

    // Print the tree to the console
    cout << "===Parse Tree===" << endl;
    printTree(root, 0);

    inputFile.close();
    remove("Input.txt");

    return 0;
}
