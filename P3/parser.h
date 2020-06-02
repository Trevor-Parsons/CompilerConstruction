#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "token.h"

extern fstream inputFile;

// Generates an error status on a bad node
node_t* error(node_t*);

// Retruns an intialized new node_t structure
node_t* getNode(string);

// Main Parser function that starts the calls to the nonterminal functions
node_t* parser();

// Nonterminal functions
node_t* S();
node_t* B();
node_t* V();
node_t* M();
node_t* M1();
node_t* H();
node_t* R();
node_t* Q();
node_t* T();
node_t* A();
node_t* A1();
node_t* W();
node_t* I();
node_t* G();
node_t* E();
node_t* Z();

#endif