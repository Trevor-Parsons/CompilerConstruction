#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "token.h"
#include "scanner.h"
#include "parser.h"

using namespace std;

token tk;
vector<token> identifiers;
vector<token> numbers;
vector<token> operators;

// Generates a dynamically allocated node_t structure, initialized with basic values
node_t* getNode (string s) {
    node_t* node = new node_t;
    node->label = s;
    node->status = "GOOD";
    node->lineNum = 0;
    node->tkErrorName = "";
    node->tkErrorType = "";

    node->tk1.name = "";
    node->tk1.tkID = "";
    node->tk1.line = 0;

    node->tk2.name = "";
    node->tk2.tkID = "";
    node->tk2.line = 0;

    node->tk3.name = "";
    node->tk3.tkID = "";
    node->tk3.line = 0;

    node->child1 = NULL;
    node->child2 = NULL;
    node->child3 = NULL;
    node->child4 = NULL;

    return node;
}

// Generate error information for a node
node_t* error(node_t* node) {
    node->status = "ERROR";
    node->lineNum = tk.line;
    node->tkErrorName = tk.name;
    node->tkErrorType = tk.tkID;
    return node;
}

// Start of the calls to the nonterminal functions below to build the parse tree
node_t* parser() {
    node_t *root;
    tk = scanner();
    root = S();

    if (tk.tkID != "EOF_TK") {
        return error(root);
    }

    return root;
}

node_t* S() {
    node_t* node = getNode("S");

    if (tk.tkID == "PROGRAM_TK") {
        node->tk1 = tk;
        tk = scanner();
        node->child1 = V();
        node->child2 = B();

        return node; 
    } 

    return error(node);
}

node_t* B() {
    node_t *node = getNode("B");
    
    if (tk.tkID == "BEGIN_TK") {
        node->tk1 = tk;
        tk = scanner();
        node->child1 = V();
        node->child2 = Q();

        if (tk.tkID == "END_TK") {
            node->tk2 = tk;
            tk = scanner();
        } else return error(node);

        return node;
    } 

    return error(node);
}

node_t* V() {
    node_t *node = getNode("V");

    if (tk.tkID == "VAR_TK") {
        node->tk1 = tk;
        tk = scanner();

        if (tk.tkID == "IDENT_TK") {
            node->tk2 = tk;
            tk = scanner();
        
            if (tk.tkID == "PERIOD_TK") {
                node->tk3 = tk;
                tk = scanner();
                node->child1 = V();

                return node;
            } else return error(node);
        } else return error(node);
    }
        
    return node = NULL;
}

node_t* Q() {
    node_t *node = getNode("Q");

    if (tk.tkID == "SCAN_TK" || tk.tkID == "WRITE_TK" ||
        tk.tkID == "IF_TK" || tk.tkID == "REPEAT_TK" ||
        tk.tkID == "LET_TK" || tk.tkID == "BEGIN_TK") {

        node->child1 = T();

        if (tk.tkID == "POUND_TK") {
            node->tk1 = tk;
            tk = scanner();
            node->child2 = Q();
            return node;
        } else return error(node);
    }

    return node = NULL;
}

node_t* T() {
    node_t *node = getNode("T");

    if (tk.tkID == "SCAN_TK") {
        node->child1 = A();

        if (tk.tkID == "COMMA_TK") {
            node->tk1 = tk;
            tk = scanner();
        } else return error(node);

        return node;
    } 

    if (tk.tkID == "WRITE_TK") {
        node->child1 = W();

        if (tk.tkID == "COMMA_TK") {
            node->tk1 = tk;
            tk = scanner();
        } else return error(node);

        return node;
    } 

    if (tk.tkID == "IF_TK") {
        node->child1 = I();

        if (tk.tkID == "COMMA_TK") {
            node->tk1 = tk;
            tk = scanner();
        } else return error(node);

        return node;
    }

    if (tk.tkID == "REPEAT_TK") {
        node->child1 = G();

        if (tk.tkID == "COMMA_TK") {
            node->tk1 = tk;
            tk = scanner();
        } else return error(node);

        return node;
    }

    if (tk.tkID == "LET_TK") {
        node->child1 = E();

        if (tk.tkID == "COMMA_TK") {
            node->tk1 = tk;
            tk = scanner();
        } else return error(node);

        return node;
    }

    if (tk.tkID == "BEGIN_TK") {
        node->child1 = B();

        return node;
    } 
        
    return error(node);
}

node_t* A() {
    node_t *node = getNode("A");

    if (tk.tkID == "SCAN_TK") {
        node->tk1 = tk;
        tk = scanner();
        node->child1 = A1();

        return node;
    }

    return error(node);
}

node_t* A1() {
    node_t *node = getNode("A1");

    if (tk.tkID == "NUM_TK") {
        node->tk1 = tk;
        tk = scanner();
        return node;
    }

    if (tk.tkID == "IDENT_TK") {
        node->tk1 = tk;
        tk = scanner();
        return node;
    }

    return error(node);
}

node_t* W() {
    node_t *node = getNode("W");
    node->tk1 = tk;
    tk = scanner();
    node->child1 = M();
    return node;
}

node_t* I() {
    node_t *node = getNode("I");

    node->tk1 = tk;
    tk = scanner();

    if (tk.tkID == "OPENBK_TK") {
        node->tk2 = tk;
        tk = scanner();
        node->child1 = M();
        node->child2 = Z();
        node->child3 = M();

        if (tk.tkID == "CLOSEBK_TK") {
            node->tk3 = tk;
            tk = scanner();
            node->child4 = T();

            return node;
        } else return error(node);
    }

    return error(node);
}

node_t* G() {
    node_t *node = getNode("G");

    node->tk1 = tk;
    tk = scanner();

    if (tk.tkID == "OPENBK_TK") {
        node->tk2 = tk;
        tk = scanner();
        node->child1 = M();
        node->child2 = Z();
        node->child3 = M();

        if (tk.tkID == "CLOSEBK_TK") {
            node->tk3 = tk;
            tk = scanner();
            node->child4 = T();

            return node;
        } else return error(node);
    }

    return error(node);
}

node_t* E() {
    node_t *node = getNode("E");

    node->tk1 = tk;
    tk = scanner();

    if (tk.tkID == "IDENT_TK") {
        node->tk2 = tk;
        tk = scanner();

        if (tk.tkID == "COLON_TK") {
            node->tk3 = tk;
            tk = scanner();
            node->child1 = M();

            return node;
        } else return error(node);
    } 

    return error(node);
}

node_t* M() {
    node_t *node = getNode("M");
    node->child1 = H();
    node->child2 = M1();

    return node;
}

node_t* M1() {
    node_t *node = getNode("M1");

    if (tk.tkID == "PLUS_TK" || tk.tkID == "MINUS_TK" ||
        tk.tkID == "FDSLASH_TK" || tk.tkID == "ASTRIK_TK") {

        node->tk1 = tk;
        tk = scanner();
        node->child1 = M();

        return node;
    }

    return node = NULL;
}

node_t* H() {
    node_t *node = getNode("H");

    if (tk.tkID == "AMPER_TK") {
        node->tk1 = tk;
        tk = scanner();
        node->child1 = R();

        return node;
    } 

    node->child1 = R();

    return node;
}

node_t* R() {
    node_t *node = getNode("R");

    if (tk.tkID == "IDENT_TK") {
        node->tk1 = tk;
        tk = scanner();

        return node;
    }
    
    if (tk.tkID == "NUM_TK") {
        node->tk1 = tk;
        tk = scanner();

        return node;
    } 

    return error(node);
}

node_t* Z() {
    node_t *node = getNode("Z");

    if (tk.tkID == "GREATER_TK" || tk.tkID == "LESS_TK" || 
        tk.tkID == "COLON_TK" || tk.tkID == "EQUAL_TK" || 
        tk.tkID == "EQUALEQUAL_TK") {

        node->tk1 = tk;
        tk = scanner();

        return node;
    }

    return error(node);
}