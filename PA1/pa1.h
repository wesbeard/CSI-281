/*
Author: Silver Needle
Class: CSI-281: Data Structures and Algorithms
Assignment: Programming Assignment 1
Date Assigned: 8/26/2019
Due Date: 9/2/2019
Description:
	A program that reads a mushroom dataset file, stores this information, and analyzes it based on what attributes are present, how many, as well as the percentage of the total attributes.
Certification of Authenticity:
	I certify that this is entirely my own work, except where I have given fully-documented references to the work of others.
	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
		- Reproduce this assignment and provide a copy to another member of academic staff; and/or
		- Communicate a copy of this assignment to a plagiarism checking service
		(which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)
*/

#ifndef PA1
#define PA1

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

class Operations
{
	struct Node
	{
		char  mChar;
		int   mNum;
		Node* mNext;

		Node();
		Node(char entryChar, int entryNum);
	};

	private:
		Node* mHead;
		Node* mTail;
		int mCount;
		string mInputFile;
		string mOutputFile;
		char** mFileContents; 
		char* mAttributeCount;
		int mNumAttributes;
		int mNumEntries;

	public:
		Operations();
		~Operations();
		void fileNames();
		void readFile();
		void findNumAttributes();
		void analyzeData();
		bool exitPrompt();

		//Accessors
		string getInputFile();
		string getOutputFile();
		int getNumAttributes();
		int getNumEntries();

		//Mutators
		void setInputFile(string fileName);
		void setOutputFile(string fileName);
		void setNumAttributes(int num);
		void setNumEntries(int num);

		//Linked list
		bool insert(char entryChar, int entryNum);
		bool letterExists(char searchChar);
		void increment(char searchChar);
		void display();
		void clearList();

		//Overloads
		friend ostream& operator << (ostream& output, Operations right);
};

#endif