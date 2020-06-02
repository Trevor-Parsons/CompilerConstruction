// Trevor Parsons
// 9/22/19
// Description: Main driver for traversal printing program P0

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <string.h>

#include "node.h"
#include "traversals.h"
#include "buildTree.h"

using namespace std;

int main(int argc, char* argv[]) {
	// Handling input file
	fstream inputFile;
	string inputFileName;

	// Reading command line input
	string fileContents;
	string buff[1000];

	// Handling output files
	FILE* outputFile;
	string outputFileName;
	string outFileName;

	struct node_t *root = NULL;
	int count = 0;

	// Redirection opterator error check
	if (argc < 2) {
		while (cin >> buff[count]) {
			count++;
		}
		
		// Error checking for empty file
		if (buff[0] == "") {
			cout << ("Fatal: Improper Usage\nUsage: P0 [filename]\n");
			return -1;
		}
		
		// Create input file for stdin to print to
		inputFileName = "InputFile.txt";
		inputFile.open(inputFileName.c_str(), ios::out);
		
		// Print stdin to input file
		for (int i = 0; i < count; i++) {
			inputFile << buff[i] << " ";
		}

		inputFile.close();

		// Give the output file appropriate prefix
		outputFileName = "out";
	}

	// Command line input error check
	if (argc > 2) {
		// Create input file for stdin to print to
		inputFileName = "InputFile.txt";
		inputFile.open(inputFileName.c_str(), ios::out);
		
		// Print command line input to input file
		for (int i = 1; i < argc; i++) {
			inputFile << argv[i] << " ";
		}

		inputFile.close();
		outputFileName = "out";
	} 

	// Input file specified error check
	if (argc == 2) {
		// Open specified input file for error checking
		inputFileName = argv[1];
		inputFile.open(inputFileName.c_str(), ios::in);
		
		// Verify that file exists
		if (!inputFile.is_open()) {
			cout << "Error: File not found!";
			return -1;
		}

		// Error check if file is empty
		if (inputFile.peek() == std::ifstream::traits_type::eof()) {
			cout << "File Error: File is empty!\n";
			return -1;
		}

		inputFile.close();
		outputFileName = inputFileName;
	}

	// File Contents Error Checking 
	inputFile.open(inputFileName.c_str(), ios::in);

	while (inputFile >> fileContents) {
		for (int i = 0; i < fileContents.size(); i++) {
			if (!((isalpha(fileContents[i]) && islower(fileContents[i])) 
				 || isspace(fileContents[i]))) {
					  cout << "File Error: Improper file contents!\n";
					  return -1;
			}
		}	
	}

	inputFile.close();
	
	//Build binary search tree using input file 
	inputFile.open(inputFileName.c_str(), ios::in);
	root = buildTree(inputFile);
	inputFile.close();
	
	// Print preoder tree traversal to console and file
	outFileName = outputFileName + ".preorder";
	cout << "-Preorder Traversal-" << endl;
	outputFile = fopen(outFileName.c_str(), "a+");
	traversePreOrder(root, 0, outputFile);
	fclose(outputFile);
	cout << endl;

	// Print inorder tree travrsal to console and file
	outFileName = outputFileName + ".inorder";
	cout << "-Inorder Traversal-" << endl;
	outputFile = fopen(outFileName.c_str(), "a+");
	traverseInOrder(root, 0, outputFile);
	fclose(outputFile);
	cout << endl;
	
	// Print level order traversal to console and file
	outFileName = outputFileName + ".levelorder";
	cout << "-Level Order Traversal-" << endl;
	outputFile = fopen(outFileName.c_str(), "a+");
	traverseLevelOrder(root, 0, outputFile);
	fclose(outputFile);
	cout << endl;

	inputFile.close();

	return 0;
}
