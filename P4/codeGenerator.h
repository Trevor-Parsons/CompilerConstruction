#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <fstream>
#include <vector>
#include "token.h"

extern fstream outputFile;
extern vector<token> identifiers;

void initializeTempVar();
string codeGenerator(node_t*, node_t*);
void variableDeclarations();


#endif