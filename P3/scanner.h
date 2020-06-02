#pragma once

#ifndef SCANNER_H
#define SCANNER_H

#include <string>

#include "token.h"

using namespace std;

extern fstream inputFile;
extern bool okParse;

// Determine if a character is a known operator
bool isOperator(string);

// Determine which FSA table column an input corresponds to
int getStateCol (int);

// Determine what token corresponds with a FSA state
string findToken(int, string);

// Scanner function
token scanner();

// Returns proper file pointer location and line number
void prepareFile();

#endif