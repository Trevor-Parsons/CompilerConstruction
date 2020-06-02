#include "testScanner.h"
#include "scanner.h"
#include "token.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Call scanner and print token until EOF
void testScan(fstream& input) {
    int nextChar;
    int lineNum = 1;
    string commentString;

    // Find next valid character and call scanner from that point in the file
    while(1) {
        nextChar = input.peek();
        // Check for end of line character 
        if (nextChar == '\n') {
            nextChar = input.get();
            lineNum++;
            continue;
        }

        // Ignore comments filter
        if (nextChar == '%') {
            commentString.append(1, input.get());
            // Iterate over file until end comment or EOF
            while ((nextChar = input.peek()) != EOF) {
                if ((nextChar = input.get()) == '%') break;
            }

            if (nextChar == EOF) { 
                cout << "ERROR: MISSING CLOSE COMMENT\n" << commentString;
                input.unget();
            }

            continue;
        }

        // Ignore whitespace filter
        if ((nextChar = input.peek()) == ' ') {
            nextChar = input.get();

            while ((nextChar = input.peek()) == ' ') {
                nextChar = input.get();
            }

            continue;
        }
        
        // Send file and line number to scanner
        token currentToken = scanner(input, lineNum);
  
        // Print token
        cout << "Token: " << currentToken.tkID << " | Instance: \"" << currentToken.name << "\" | Line Number: " << currentToken.line << endl;

        if (currentToken.tkID == "EOF_TK") {
            break;
        }
    }

    input.close();
}