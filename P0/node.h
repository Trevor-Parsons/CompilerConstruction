// Trevor Parsons
// 9/22/19
// Description: This file defines the node_h data type

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

using namespace std;

struct node_t {
	char key;
	int level;
	vector<string> words;
	node_t *left;
	node_t *right;
};

#endif
