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

#include "pa1.h"

/*
	Pre: Data loaded into array and linked list intialized
	Post: Data is entered into a linked list and analyzed
	Purpose: To take data from the array to sort and count it
*/
void Operations::analyzeData()
{
	int i;
	int j;
	int k;
	int attributeNum = 1;
	int numColumns = getNumAttributes();
	int numRows = getNumEntries();
	char tempChar;
	const int START_NUM = 1;
	Node node;
	Operations attributeIndex;

	ofstream fout;
	fout.open(mOutputFile, ios::app);

	//Puts contents of array into a linked list and counts number of occurences
	for (i = 0; i < numColumns; i++)
	{
		cout << endl << "Attribute #" << attributeNum << endl
			<< "============" << endl;

		fout << endl << "Attribute #" << attributeNum << endl
			<< "============" << endl;

		for (j = 0; j < numRows; j++)
		{
			tempChar = mFileContents[j][i];

			for (k = 0; k < j; k++)
			{
				if (j == 0)
				{
					insert(tempChar, START_NUM);
				}
				else if (!letterExists(tempChar))
				{
					insert(tempChar, START_NUM);
				}
				else
				{
					increment(tempChar);
					break;
				}
			}
		}
		display();

		clearList();
		attributeNum++;
	}
}

/*
	Pre: Program has run and completed
	Post: Program is either exited or runs again
	Purpose: To prompt the user if they want to run the program again
*/
bool Operations::exitPrompt()
{
	int choice;
	bool validChoice = false;
	bool exit;

	cout << endl;
	cout << "Analysis finished and printed to file..." << endl;

	do
	{
		cout << "[1] Analyze another file" << endl;
		cout << "[0] Exit program" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
			exit = false;
			validChoice = true;
			break;
		case 0:
			exit = true;
			validChoice = true;
			break;
		default:
			cout << "Invalid choice, try again... " << endl;
			validChoice = false;
			break;
		}
	} while (validChoice == false);

	return exit;
}

/*
	Pre: None
	Post: File names for input and output are both obtained and verified
	Purpose: To get names for the files used to get the dataset as well as store the analyzed data
*/
void Operations::fileNames()
{
	ifstream fin;
	string tempInputFile;
	string tempOutputFile;
	bool validFile = false;
	Operations overload;
	
	do
	{
		//Couldn't find anywhere else where I wanted to use an overload so I used it here
		cout << overload;
		cin >> tempInputFile;

		fin.open(tempInputFile);
		if (fin.fail())
		{
			cout << "Failed to load file, please try again..." << endl;
		}
		else
		{
			cout << "File loaded successfully..." << endl;
			validFile = true;
		}
	} while (validFile == false);

	setInputFile(tempInputFile);

	cout << "Enter an analysis output file: " << endl;
	cin >> tempOutputFile;

	cout << "Output file set to " << tempOutputFile << "..." << endl << endl;

	setOutputFile(tempOutputFile);
}

/*
	Pre: Input file loaded successfully
	Post: Number of attributes and entries recorded
	Purpose: To get the dimensions of the data file to create a 2D dynamic array
*/
void Operations::findNumAttributes()
{
	
	ifstream fin;
	fin.open(getInputFile());

	char current = '?';
	int tempNumAttributes = 0;
	int tempNumEntries = 0;

	//Finds number of attributes (columns)
	while (current != '\n')
	{
		fin.get(current);
		if (current != ' ')
		{
			tempNumAttributes++;
		}
	}

	fin.close();
	fin.open(getInputFile());

	//Finds number of entries (rows)
	do 
	{
		fin.get(current);
		if (current == '\n')
		{
			tempNumEntries++;
		}
	} while (!fin.eof());

	tempNumAttributes--;
	tempNumEntries++;
	cout << "This data file has " << tempNumAttributes << " total attributes & " << tempNumEntries << " total entries.." << endl;

	setNumAttributes(tempNumAttributes);
	setNumEntries(tempNumEntries);

	fin.close();
}

/*
	Pre: None
	Post: Private variables value is returned
	Purpose: To return value when called 
*/
string Operations::getInputFile()
{
	return mInputFile;
}
string Operations::getOutputFile()
{
	return mOutputFile;
}
int Operations::getNumAttributes()
{
	return mNumAttributes;
}
int Operations::getNumEntries()
{
	return mNumEntries;
}

/*
	Pre: Data file successfully loaded
	Post: All data from file is loaded into a 2D dynamic array
	Purpose: To get all of the data to be analyzed from the specified file
*/
void Operations::readFile()
{
	int i;
	int j;
	int k;
	int numColumns = getNumAttributes();
	int numRows = getNumEntries();

	//Creates a 2D dynamic array
	mFileContents = new char* [numRows];
	for (i = 0; i < numRows; i++)
	{
		mFileContents[i] = new char[numColumns];
	}

	ifstream fin;
	fin.open(getInputFile());

	//Enters contents of file into array
	while (!fin.eof())
	{
		for (j = 0; j < numRows; j++)
		{
			for (k = 0; k < numColumns; k++)
			{
				fin >> mFileContents[j][k];
			}
		}
	}
}

/*
	Pre: None
	Post: Initializes all private variables to default values
	Purpose: Constructor
*/
Operations::Operations()
{
	mHead = NULL;
	mTail = NULL;
	mCount = 0;
	mInputFile = "";
	mOutputFile = "";
	mFileContents = NULL;
	mAttributeCount = NULL;
	mNumAttributes = 0;
	mNumEntries = 0;
}

/*
	Pre: None
	Post: Variables set to default values, linked list deleted, and dynamic arrays deleted.
	Purpose: Deconstructor
*/
Operations::~Operations()
{
	Node* toBeDeleted;

	toBeDeleted = mHead;

	while (mHead != NULL)
	{
		mHead = mHead->mNext;
		toBeDeleted->mNext = NULL;
		delete toBeDeleted;
		toBeDeleted = mHead;
	}

	delete[] mFileContents;
	delete[] mAttributeCount;

	mHead = NULL;
	mTail = NULL;
	mCount = 0;
	mInputFile = "";
	mOutputFile = "";
	mFileContents = NULL;
	mAttributeCount = NULL;
	mNumAttributes = 0;
	mNumEntries = 0;
}

/*
	Pre: None
	Post: Output stream printed to console
	Purpose: To output the stream when called
*/
ostream& operator << (ostream& output, Operations right)
{
	output << "Enter an input file name to analyze: " << endl;

	return output;
}

/*
	Pre: None
	Post: Class variables set to parameters
	Purpose: To set private variables to given parameters when called
*/
void Operations::setInputFile(string fileName)
{
	mInputFile = fileName;
}
void Operations::setOutputFile(string fileName)
{
	mOutputFile = fileName;
}
void Operations::setNumAttributes(int num)
{
	mNumAttributes = num;
}
void Operations::setNumEntries(int num)
{
	mNumEntries = num;
}