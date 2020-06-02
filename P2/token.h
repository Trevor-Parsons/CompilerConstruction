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

// Keword structure
struct keywords {
    string name;
    string tokenName;
};

struct node_t {
    // Deterine if the node is valid or not (error checking)
    string status;
    string tkErrorName;
    string tkErrorType;
    int lineNum;

    // Store the function that created the node
    string label;

    // Associated terminals
    token tk1;
    token tk2;
    token tk3;

    // Child notdes
    node_t* child1;
    node_t* child2;
    node_t* child3;
    node_t* child4;   
};

#endif