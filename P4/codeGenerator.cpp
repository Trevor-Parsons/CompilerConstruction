#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "codeGenerator.h"
#include "token.h"

using namespace std;

vector<string> tempVar;
int tempCounter = 0;
int inLabelCounter = 0;
int outLabelCounter = 0;
bool T0 = false;
bool T1 = false;
bool T2 = false;

string codeGenerator(node_t* node, node_t* reference) {
    node_t* referenceNode;

    if (node->label == "S") {
        if (node->child1 != NULL) codeGenerator(node->child1, node);
        if (node->child2 != NULL) codeGenerator(node->child2, node);
    }

    if (node->label == "B") {
        if (node->child1 != NULL) codeGenerator(node->child1, node);
        if (node->child2 != NULL) codeGenerator(node->child2, node);
    }

    if (node->label == "V") {
        if (node->child1 != NULL) codeGenerator(node->child1, node);
    }

    if (node->label == "Q") {
        if (node->child1 != NULL) codeGenerator(node->child1, node);
        if (node->child2 != NULL) codeGenerator(node->child2, node);
    }

    if (node->label == "T") {
        if (node->child1 != NULL) codeGenerator(node->child1, node);

    }

    if (node->label == "A") {
        outputFile << "READ ";
        if (node->child1 != NULL) codeGenerator(node->child1, node);
        outputFile << endl;
    }

    if (node->label == "A1") {
        outputFile << node->tk1.name;
    }

    if (node->label == "W") {
        if (node->child1 != NULL) codeGenerator(node->child1, node);
    }

    if (node->label == "I") {
        if (codeGenerator(node->child2, node) != "COLON_TK") {
            if (codeGenerator(node->child2, node) != "EQUALEQUAL_TK") {
                T0 = true;
                T1 = true;
                outputFile << "LOAD ";
                if (node->child1 != NULL) codeGenerator(node->child1, node);
                outputFile << endl << "STORE T0" << endl;
                
                outputFile << "LOAD ";
                if (node->child2 != NULL) codeGenerator(node->child3, node);
                outputFile << endl << "STORE T1" << endl;
                outputFile << "LOAD T0" << endl << "SUB T1" << endl;

                if (node->child3 != NULL) outputFile << codeGenerator(node->child2, node);
                outLabelCounter++;
                int outLabelReference = outLabelCounter;
                outputFile << "Out" << outLabelReference << endl;

                if (node->child4 != NULL) codeGenerator(node->child4, node);

                outputFile << "Out" << outLabelReference << ": NOOP" << endl;
            } else {
                T0 = true;
                T1 = true;
                outputFile << "LOAD ";
                if (node->child1 != NULL) codeGenerator(node->child1, node);
                outputFile << endl << "STORE T0" << endl;
                
                outputFile << "LOAD ";
                if (node->child2 != NULL) codeGenerator(node->child3, node);
                outputFile << endl << "STORE T1" << endl;
                outputFile << "LOAD T0" << endl << "SUB T1" << endl;

                outputFile << "BRPOS ";
                outLabelCounter++;
                int outLabelReferencePOS = outLabelCounter;
                outputFile << "Out" << outLabelReferencePOS << endl;

                outputFile << "BRNEG ";
                outLabelCounter++;
                int outLabelReferenceNEG = outLabelCounter;
                outputFile << "Out" << outLabelReferenceNEG << endl;

                if (node->child4 != NULL) codeGenerator(node->child4, node);

                outputFile << "Out" << outLabelReferencePOS << ": NOOP" << endl;
                outputFile << "Out" << outLabelReferenceNEG << ": NOOP" << endl;
            }
        } else {
            if (node->child4 != NULL) codeGenerator(node->child4, node);
        }
    }

    if (node->label == "G") {
        if (codeGenerator(node->child2, node) != "COLON_TK") {
            if (codeGenerator(node->child2, node) != "EQUALEQUAL_TK") {
                T0 = true;
                T1 = true;
                int inLabelReference = inLabelCounter;
                outputFile << "In" << inLabelReference << ": NOOP" << endl;
                inLabelCounter++;

                outputFile << "LOAD ";
                if (node->child1 != NULL) codeGenerator(node->child1, node);
                outputFile << endl << "STORE T0" << endl;
                
                outputFile << "LOAD ";
                if (node->child2 != NULL) codeGenerator(node->child3, node);
                outputFile << endl << "STORE T1" << endl;
                outputFile << "LOAD T0" << endl << "SUB T1" << endl;

                if (node->child3 != NULL) outputFile << codeGenerator(node->child2, node);
                outLabelCounter++;
                int outLabelReference = outLabelCounter;
                outputFile << "Out" << outLabelReference << endl;

                if (node->child4 != NULL) codeGenerator(node->child4, node);
                
                outputFile << "BR In" << inLabelReference << endl;
                outputFile << "Out" << outLabelReference << ": NOOP" << endl;
            } else {
                T0 = true;
                T1 = true;
                int inLabelReference = inLabelCounter;
                outputFile << "In" << inLabelReference << ": NOOP" << endl;
                inLabelCounter++;

                outputFile << "LOAD ";
                if (node->child1 != NULL) codeGenerator(node->child1, node);
                outputFile << endl << "STORE T0" << endl;
                
                outputFile << "LOAD ";
                if (node->child2 != NULL) codeGenerator(node->child3, node);
                outputFile << endl << "STORE T1" << endl;
                outputFile << "LOAD T0" << endl << "SUB T1" << endl;

                outputFile << "BRPOS ";
                outLabelCounter++;
                int outLabelReferencePOS = outLabelCounter;
                outputFile << "Out" << outLabelReferencePOS << endl;

                outputFile << "BRNEG ";
                outLabelCounter++;
                int outLabelReferenceNEG = outLabelCounter;
                outputFile << "Out" << outLabelReferenceNEG << endl;

                if (node->child4 != NULL) codeGenerator(node->child4, node);

                outputFile << "BR In" << inLabelReference << endl;
                outputFile << "Out" << outLabelReferencePOS << ": NOOP" << endl;
                outputFile << "Out" << outLabelReferenceNEG << ": NOOP" << endl;
            }
        } else {
            outputFile << "INFINITE REPEAT LOOP" << endl;
            outputFile << "InX: NOOP" << endl;
            if (node->child4 != NULL) codeGenerator(node->child4, node);
            outputFile << "BR InX" << endl;
        }
    }

    if (node->label == "E") {
        outputFile << "LOAD ";
        if (node->child1 != NULL) codeGenerator(node->child1, node);
        outputFile << endl << "STORE " << node->tk2.name << endl;
    }

    if (node->label == "M") {
        if (reference->label == "W") {
            if (node->child2 == NULL) {
                outputFile << "WRITE ";
                if (node->child1 != NULL) codeGenerator(node->child1, node);
                outputFile << endl;
            } else {
                T0 = true;
                outputFile << "LOAD ";
                if (node->child1 != NULL) codeGenerator(node->child1, node);
                outputFile << endl;
                if (node->child2 != NULL) codeGenerator(node->child2, node);
                outputFile << endl << "STORE T0" << endl;
                outputFile << "WRITE T0" << endl;
            }
        }

        if (reference->label == "I") {
            if (node->child1 != NULL) codeGenerator(node->child1, node);
            if (node->child2 != NULL) {
                outputFile << endl;
                if (node->child2 != NULL) codeGenerator(node->child2, node);
            }
        }

        if (reference->label == "G") {
            if (node->child1 != NULL) codeGenerator(node->child1, node);
            if (node->child2 != NULL) {
                outputFile << endl;
                if (node->child2 != NULL) codeGenerator(node->child2, node);
            }
        }

        if (reference->label == "E") {
            if (node->child1 != NULL) codeGenerator(node->child1, node);
            if (node->child2 != NULL) {
                outputFile << endl;
                if (node->child2 != NULL) codeGenerator(node->child2, node);
            }
        }

        if (reference->label == "M1") {
            if (node->child1 != NULL) codeGenerator(node->child1, node);
            if (node->child2 != NULL) {
                outputFile << endl;
                if (node->child2 != NULL) codeGenerator(node->child2, node);
            }
        }
    }

    if (node->label == "M1") {
        if (node->tk1.tkID == "PLUS_TK") outputFile << "ADD ";
        if (node->tk1.tkID == "MINUS_TK") outputFile << "SUB ";
        if (node->tk1.tkID == "ASTRIK_TK") outputFile << "MULT ";
        if (node->tk1.tkID == "FDSLASH_TK") outputFile << "DIV ";

        if (node->child1 != NULL) codeGenerator(node->child1, node);
    }

    if (node->label == "H") {
        if (node->child1 != NULL) codeGenerator(node->child1, node);
    }

    if (node->label == "R") {
        // if (reference->tk1.tkID == "AMPER_TK") {
        //     if (node->tk1.name.at(0) == '-') {
        //         string temp = node->tk1.name.substr(1);
        //         outputFile << temp;
        //     } else outputFile << node->tk1.name;
        // } else outputFile << node->tk1.name;

        outputFile << node->tk1.name;
    }

    if (node->label == "Z") {
        if (node->tk1.tkID == "LESS_TK") return "BRZPOS ";
        if (node->tk1.tkID == "GREATER_TK") return "BRZNEG ";
        if (node->tk1.tkID == "EQUAL_TK" || node->tk1.tkID == "EQUALEQUAL_TK") return "EQUALEQUAL_TK";
        if (node->tk1.tkID == "COLON_TK") return "COLON_TK";
    }

    return "";
}

void variableDeclarations() {
    outputFile << "STOP" << endl;

    for (int i = 0; i < identifiers.size(); i++) {
        outputFile << identifiers[i].name << " 0" << endl;
    }
    if (T0) outputFile << "T0 0" << endl;
    if (T1) outputFile << "T1 0" << endl;
    if (T2) outputFile << "T2 0" << endl;
}

void initializeTempVar() {
    tempVar.push_back("T1");
    tempVar.push_back("T2");
    tempVar.push_back("T3");
    tempVar.push_back("T4");
    tempVar.push_back("T5");
}