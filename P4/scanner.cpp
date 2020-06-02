#include "scanner.h"
#include "token.h"
#include "parser.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int lineNum = 1;

const operators opts[15] = {
    {"=", "EQUAL_TK"},
    {"==", "EQUALEQUAL_TK"},
    {">", "GREATER_TK"},
    {"<", "LESS_TK"},
    {":", "COLON_TK"},
    {"&", "AMPER_TK"},
    {"+", "PLUS_TK"},
    {"-", "MINUS_TK"},
    {"*", "ASTRIK_TK"},
    {"/", "FDSLASH_TK"},
    {"#", "POUND_TK"},
    {".", "PERIOD_TK"},
    {"[", "OPENBK_TK"},
    {"]", "CLOSEBK_TK"},
    {",", "COMMA_TK"}
}; 

const keywords kwds[12] = {
    {"begin", "BEGIN_TK"},
    {"end", "END_TK"},
    {"repeat", "REPEAT_TK"},
    {"if", "IF_TK"},
    {"then", "THEN_TK"},
    {"let", "LET_TK"},
    {"void", "VOID_TK"},
    {"return", "RETURN_TK"},
    {"scan", "SCAN_TK"},
    {"write", "WRITE_TK"},
    {"program", "PROGRAM_TK"},
    {"var", "VAR_TK"}
};

// Define FSA table
// COLUMN IDENTIFIERS:
// 1 = Lower case letter a-z
// 2 = Upper case letter A-Z
// 3 = Number 0-9
// 4 = Operator (from defined list)
// 5 = EOF
// 6 = Other  
//
// ROW IDENTIFIERS - Column 0 corresponds to possible states
// TOKEN IDENTIFIERS
// 100 - Identifier Token
// 101 - Number Token
// 102 - Operator Token
// 103 - EOF Token
// 
// ERROR IDENTIFIERS
// -1 - Error Token

const int FSATable[6][7] = { {0, 1,   2,   3,   4,   5,   6},
                             {1, 2,   -1,  4,   5,   103, -1},
                             {2, 3,   3,   3,   -1,  -1,  -1},
                             {3, 3,   3,   3,   100, 100, 100},
                             {4, 101, 101, 4,   101, 101, 101},
                             {5, 102, 102, 102, 102, 102, 102} };


// Determine if input is an operator 
bool isOperator(string op) {
    for (int i = 0; i < 15; i++) {
        if (op == opts[i].symbol) {
            return true;
        }
    }
        
    return false; 
}

// Function to return the FSA column of the input character
int getStateCol (int c) {
    string s(1, c);

    if (c >= 97 && c <= 122) return 1;

    if (c >= 65 && c <= 90) return 2;

    if (c >= 48 && c <= 57) return 3;

    if (isOperator(s)) return 4;

    if (c == -1) return 5;

    return 6;
}

// Return the corresponding token name with the final FSA table state 
string findToken(int state, string text) {
    // Identifier or Keyword Token
    if (state == 100) {
        for (int i = 0; i < 12; i++) {
            if (kwds[i].name == text) {
                return kwds[i].tokenName;
            }
        }

        return "IDENT_TK";
    }

    // Number Token
    if (state == 101) return "NUM_TK";

    // Operator token
    if (state == 102) {
        for (int i = 0; i < 15; i++) {
            if (opts[i].symbol == text) {
                return opts[i].tokenName;
            }
        }

        return "OP_ERR_TK";
    }

    if (state == 103) return "EOF_TK";
    if (state == -1) return "ERROR_TK";

    return "ERROR_TK";
}

// Scan in one token and return the token
token scanner() {
    prepareFile();
    int nextChar = inputFile.get();
    string tokenText = "";
    tokenText.append(1, nextChar);
    token tk;

    // Log the starting state in FSA table
    int stateCol = getStateCol(nextChar);
    int stateRow = FSATable[1][stateCol];

    // Counter to determine if identifier or number is 8 digits
    int numChar = 1;

    // Check for end of file
    if (nextChar == EOF) {
        tk.tkID = "EOF_TK";
        tk.name = "EOF";
        tk.line = lineNum;

        return tk;
    }

    while (FSATable[stateRow][stateCol] > 0 && 
           FSATable[stateRow][stateCol] < 100 && 
           numChar <= 8) {

        numChar++;
        nextChar = inputFile.peek();
        stateCol = getStateCol(nextChar);
        stateRow = FSATable[stateRow][stateCol];
        
        if (stateRow < 100 && stateRow > 0) {
            tokenText.append(1, nextChar);
            nextChar = inputFile.get();
        } else {
            break;
        }
    }

    // Error check string that was longer than 8 characters
    if (stateRow == 3) {
        stateRow = 100;
    }

    if (stateRow == 4) {
        stateRow = 101;
    }

    if (stateRow == 5) {
        stateRow = 102;
    }

    // Check for == operator
    if (inputFile.peek() == '=') {
        inputFile.get();
        tokenText.append(1, '=');

        tk.tkID = findToken(stateRow, tokenText);
        tk.name = tokenText;
        tk.line = lineNum;
    }

    // Determine the token returned in the final state
    tk.tkID = findToken(stateRow, tokenText);
    tk.name = tokenText;
    tk.line = lineNum;

    if (tk.tkID == "ERROR_TK") {
        cout << "Scanner Error: Invalid Token -> " << tk.name 
             << ", Line: " << tk.line << endl;
    }

    return tk;
}

// Return proper file pointer location to scanner funciton
void prepareFile() {
    int nextChar;
    string commentString;
    bool validCharacter = false;

    // Find next valid character and call scanner from that point in the file
    while (!validCharacter) {
        nextChar = inputFile.peek();

        // Check for end of line character 
        if (nextChar == '\n') {
            nextChar = inputFile.get();
            lineNum++;
            continue;
        }

        // Ignore whitespace filter
        if (nextChar == ' ') {
            while ((nextChar = inputFile.peek()) == ' ') {
                nextChar = inputFile.get();
            }

            continue;
        }

        // Ignore comments filter
        if (nextChar == '%') {
            nextChar = inputFile.get();
            commentString.append(1, nextChar);
            // Iterate over file until end comment or EOF
            while ((nextChar = inputFile.get()) != '%') {
                if (nextChar == EOF) {
                    inputFile.unget();
                    cout << "Scanner Error: Missing Close Comment, Line:" 
                         << lineNum << endl;
                    okParse = false;
                    break;
                }
                commentString.append(1, nextChar);
            }
            continue;
        }
        
        validCharacter = true;
    }
}