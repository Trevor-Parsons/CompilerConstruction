#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>

#include "testTree.h"
#include "token.h"

using namespace std;

string printNode(node_t* node) {
    string nodeString;

    nodeString = "Label: ";
    nodeString += node->label;

    if (node->tk1.line != 0) {
        nodeString += ", tk1: ";
        nodeString += node->tk1.tkID;
        if (node->status == "ERROR") nodeString += "[ERROR]";
        nodeString += " (Line ";
        nodeString += to_string(node->tk1.line);
        nodeString += ")";
    }

    if (node->tk2.line != 0) {
        nodeString += ", tk2: ";
        nodeString += node->tk2.tkID;
        if (node->status == "ERROR") nodeString += "[ERROR]";
        nodeString += " (Line ";
        nodeString += to_string(node->tk2.line);
        nodeString += ")";
    }

    if (node->tk3.line != 0) {
        nodeString += ", tk3: ";
        nodeString += node->tk3.tkID;
        if (node->status == "ERROR") nodeString += "[ERROR]";
        nodeString += " (Line ";
        nodeString += to_string(node->tk3.line);
        nodeString += ")";
    }

    return nodeString;
}


void printTree(node_t *root, int level) {
	if (root != NULL) {
		// Print current node
		printf("%*s %s", level * 2, "", printNode(root).c_str());
		cout << endl;

        if (root->child1 != NULL) printTree(root->child1, level + 1);
        if (root->child2 != NULL) printTree(root->child2, level + 1);
        if (root->child3 != NULL) printTree(root->child3, level + 1);
        if (root->child4 != NULL) printTree(root->child4, level + 1);
	}
}

bool errorCheckTree(node_t *root) {
	if (root != NULL) {
        if (root->status == "ERROR") {
            cout << "Parser Error: " << root->tkErrorType << ", token: " 
                 << root->tkErrorName << ", Line: " << root->lineNum << endl;
            return false;
        }

        if (root->child1 != NULL) errorCheckTree(root->child1);
        if (root->child2 != NULL) errorCheckTree(root->child2);
        if (root->child3 != NULL) errorCheckTree(root->child3);
        if (root->child4 != NULL) errorCheckTree(root->child4);
	}

    return true;
}


string to_string(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}
