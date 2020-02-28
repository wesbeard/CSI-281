/*
Author: Wes Beard
Class: CSI-281: Data Structures and Algorithms
Assignment: Final Programming Assignment
Date Assigned: 11/16/2019
Due Date: 12/6/2019
Description:
	A decryption program that takes a codebook data file of words and numbers and a file to decrypt.
	The codebook information is entered into an AVL tree, after the data is loaded the user is
	prompted for a file to decrypt, once this file is authenticated it is opened and the information
	in it is decoded by searching the codebook AVL for the corresponding number from the decryption file.
	An AVL tree was chosen above an BST or Doubly Linked List due to its speed of search and ensurance of
	balancing no matter the format of the data. It sacrifices some time for inserting data into the tree
	versus a BST but the time saved in finding data was more important.
Certification of Authenticity:
	I certify that this is entirely my own work, except where I have given fully-documented references to the work of others.
	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
		- Reproduce this assignment and provide a copy to another member of academic staff; and/or
		- Communicate a copy of this assignment to a plagiarism checking service
		(which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)
*/

#include "final.h"
#include "avl.h"
#include "timerSystem.h"

/*
PRE: Function called
POST: Name of file to decrypt returned
PURPOSE: To prompt the user for a file name which is validated and returned if openable
*/
string getFileName()
{
	bool validFile = false;
	string tempname;
	ifstream fin;

	//Loop file name input until valid file or "exit" entered as file name
	while (!validFile)
	{
		cout << "Enter a file name to decrypt or 'exit' to quit: " << endl;
		cin >> tempname;
		cout << endl;

		//Opens filename given by user
		fin.close();
		fin.open(tempname);

		//If exit is entered then quit the program
		if (tempname == "exit")
		{
			cout << "Exiting..." << endl;
			Sleep(200);
			exit(0);
		}
		//If the file can't be opened loop back to name prompt
		if (fin.fail())
		{
			cout << "File not found or could not be opened..." << endl;
			cout << "Please enter a valid file or 'exit' to quit..." << endl << endl;
		}
		//Otherwise valid file name is returned
		else
		{
			validFile = true;
			cout << "File found..." << endl;
			return tempname;
		}
	}
}

/*
PRE: Function called in main
POST: Code book data loaded and file is decrypted
PURPOSE: To perform the operations of code book loading and file decryption as well as timing
*/
void loadCodeBook()
{
	string tempWord;
	int tempNum;
	string trash;
	ifstream fin;
	TimerSystem timer;
	AVL avl;

	//Open codebook file as specified in header
	fin.open(CODEBOOK);

	cout << "Loading code book data..." << endl;
	timer.startClock();

	//Loop through code book file and enter data into AVL tree
	while (!fin.eof())
	{
		fin >> tempWord >> tempNum;
		getline(fin, trash);
		avl.insert(tempNum, tempWord);
	}

	cout << fixed << scientific << "Code book data loaded in " << timer.getTime() << " seconds" << endl << endl;

	while (true)
	{
		//Get file name from user and open stream of valid file
		string filename = getFileName();
		fin.close();
		fin.open(filename);
		double timerResult;
		
		cout << endl << "Decrypted file: " << endl;
		timer.startClock();
		//Loop through file and search AVL for corresponding word
		while (fin >> tempNum)
		{
			avl.find(tempNum);
		}
		timerResult = timer.getTime();

		cout << endl;
		cout << fixed << scientific << "File decrypted in " << timerResult << " seconds" << endl;
		cout << endl;
	}
}