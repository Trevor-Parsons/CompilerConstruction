#include <iostream>
#include <fstream>
#include <string>

#include "token.h"
#include "parser.h"
#include "testTree.h"
#include "codeGenerator.h"

using namespace std;

fstream outputFile;
fstream inputFile;
bool okParse;

int main(int argc, char* argv[]) {
    // Input file handling
    string inputFileName;

    // Output file handling
    string outputFileName;

    // Base for parse tree
    node_t *root = NULL;

    if (argc > 2) {
        // Improper program usage
        cout << "Too many arguments!\nFormat: P1 [file]\n";
        return 0;
    } else if (argc == 2) {
        // Read tokens from file
        outputFileName = argv[1];
        outputFileName += ".asm";
        inputFileName = argv[1];
        inputFile.open(inputFileName.c_str(), fstream::in);

        // Error check file opening
        if (!inputFile.is_open()) {
            cout << "Error opening file! Ending program.";
            return 0;
        }
    } else if (argc == 1) {
        // Read arguments from the command line
        outputFileName = "kb.asm";
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
        return 0;
    }

    okParse = true;

    // Call the parser function to generate the parse tree
    root = parser();

    // Error check the parse tree to determine where errors occured
    if (errorCheckTree(root)) {
        if (okParse) cout << "OK PARSE\n\n";
    } else cout << "\nUNSUCCESSFUL PARSE\n\n";

    cout << "Check " << outputFileName << " for assembly code.\n\n";

    // Print the tree to the console
    //cout << "===Parse Tree===" << endl;
    //printTree(root, 0);

    inputFile.close();
    remove("Input.txt");

    // Open output file to write assembly code to
    outputFile.open(outputFileName.c_str(), fstream::out | fstream::trunc);

    initializeTempVar();
    string temp = codeGenerator(root, root);
    variableDeclarations();

    outputFile.close();

    return 0;
}
