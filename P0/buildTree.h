// Name: Trevor Parsons
// Date: 9/22/19
// Description: Function prototypes for buildTree.cpp file

#ifndef BUILDTREE_H
#define BUILDTREE_H

#include <string>
#include <fstream>

using namespace std;

struct node_t* buildTree(fstream&);
struct node_t* createNode(string);
struct node_t* insertNode(struct node_t*, string);
struct node_t* treeSearch(node_t*, char);

#endif
