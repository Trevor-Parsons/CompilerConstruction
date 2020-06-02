// Name: Trevor Parsons
// Date: 9/22/19
// Description: Function prototypes for traversals.cpp file

#ifndef TRAVERSALS_H
#define TRAVERSALS_H

#include "node.h"
#include <stdio.h>

void traverseLevelOrder(node_t*, int, FILE*);
void traversePreOrder(node_t*, int, FILE*);
void traverseInOrder(node_t*, int, FILE*);

#endif 
