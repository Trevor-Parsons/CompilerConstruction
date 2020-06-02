#ifndef TESTTREE_H
#define TESTTREE_H

#include "token.h"

#include <string>
using namespace std;

extern bool okParse;

// Used to print an individual node to the console
string printNode(node_t*);

// Used to traverse the parse tree and call the printNode() function at each node
void printTree(node_t*, int);

// Used to print any nodes containing errors to the console
bool errorCheckTree(node_t*);
string to_string(int);

#endif
