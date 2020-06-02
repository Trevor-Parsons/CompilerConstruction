#pragma once

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

// Token structure
struct token {
    string tkID;
    string name;
    int line;
};

// Operator structure
struct operators {
    string symbol;
    string tokenName;
};

struct keywords {
    string name;
    string tokenName;
};

#endif