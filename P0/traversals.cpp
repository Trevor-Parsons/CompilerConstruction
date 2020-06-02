// Name: Trevor Parsons
// Date: 9/22/19
// Description: Function definitions used to print various traversals of the 
// BST generated form the input file.

#include "traversals.h"
#include "node.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

// Function for printing a level order traversal of the tree
void traverseLevelOrder(node_t *root, int level, FILE* outputFile) {
	if (root == NULL)  return; 

	queue<node_t *> getInLine; 
   
   getInLine.push(root); 
     
	while (getInLine.empty() == false) { 
      node_t *node = getInLine.front(); 
		
		// Print current node
      fprintf(outputFile, "%*s%d (%c):", node->level * 2, "", node->level + 1, node->key);
		printf("%*s%d (%c): ", node->level * 2, "", node->level + 1, node->key);

		for (int i = 0; i < node->words.size(); i++) {
			fprintf(outputFile, "%s ", node->words.at(i).c_str());
			cout << node->words.at(i) << ' ';
		}
		
		fprintf(outputFile, "\n");
		cout << endl;

      getInLine.pop(); 

		if (node->left != NULL) 
         getInLine.push(node->left); 
      
      if (node->right != NULL) 	  
			 getInLine.push(node->right); 
   } 	
}

void traversePreOrder(node_t *root, int level, FILE *outputFile) {
	if (root != NULL) {
		// Print current node
		fprintf(outputFile, "%*s%d (%c): ", level * 2, "", level + 1, root->key);
		printf("%*s%d (%c): ", level * 2, "", level + 1, root->key);

		for (int i = 0; i < root->words.size(); i++) {
			fprintf(outputFile, "%s ", root->words.at(i).c_str());
			cout << root->words.at(i) << ' ';
		}

		fprintf(outputFile, "\n");
		cout << endl;
		
		root->level = level;

		traversePreOrder(root->left, level + 1, outputFile);
		traversePreOrder(root->right, level + 1, outputFile);
	}
}

void traverseInOrder(node_t *root, int level, FILE *outputFile) {
	if (root != NULL) {
		traverseInOrder(root->left, level + 1, outputFile);

		// Print current node
		fprintf(outputFile, "%*s%d (%c): ", level * 2, "", level + 1, root->key);
		printf("%*s%d (%c): ", level * 2, "", level + 1, root->key);

		for (int i = 0; i < root->words.size(); i++) {
			fprintf(outputFile, "%s ", root->words.at(i).c_str());
			cout << root->words.at(i) << ' ';
		}

		fprintf(outputFile, "\n");
		cout << endl;

		traverseInOrder(root->right, level + 1, outputFile);
	}
}
