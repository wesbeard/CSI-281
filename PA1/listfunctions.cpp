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
	Pre: List created and occupied
	Post: List cleared and reset
	Purpose: Deletes list contents so it can be used again
*/
void Operations::clearList()
{
	Node* current = mHead, * nextNode;
	bool deleted = false;

	while (current->mNext != NULL)
	{
		nextNode = current->mNext;
		free(current);
		current = nextNode;
		mCount--;
	}
	mHead = NULL;
}

/*
	Pre: Linked list created
	Post: Contents of linked list displayed to console and output file
	Purpose: To output all nodes in the linked list
*/
void Operations::display()
{
	Node* tmp;
	double percent;
	double currentNum;

	ofstream fout;
	fout.open(mOutputFile, ios::app);

	if (mHead == NULL)
	{
		cout << "Attributes empty..." << endl;
	}
	else
	{
		tmp = mHead;
		while (tmp != NULL)
		{

			currentNum = tmp->mNum;
			percent = (currentNum / mNumEntries) * 100;

			cout << fixed << setprecision(1) << tmp->mChar << " (" << tmp->mNum << ") [" << percent << "%]" << endl;
			fout << fixed << setprecision(1) << tmp->mChar << " (" << tmp->mNum << ") [" << percent << "%]" << endl;
			tmp = tmp->mNext;
		}
		cout << endl;
	}
}

/*
	Pre: Linked list populated and function called
	Post: Counter variable of list data is incremented by 1
	Purpose: To add one to the counter when a new attribute is analyzed
*/
void Operations::increment(char searchChar)
{
	bool found = false;
	Node* tmp;
	tmp = mHead;
	int currentCount;

	while (tmp != NULL && !found)
	{
		if (searchChar == tmp->mChar)
		{
			found = true;
			currentCount = tmp->mNum;
			currentCount++;
			tmp->mNum = currentCount;
		}
		else
		{
			tmp = tmp->mNext;
		}
	}
}

/*
	Pre: Linked list created and function has been called
	Post: A new item is added to the linked list
	Purpose: To insert an item onto the end of the linked list
*/
bool Operations::insert(char entryChar, int entryNum)
{
	Node* newNode;
	newNode = new Node(entryChar, entryNum);

	if (newNode == NULL)
	{
		return false;
	}
	if (mHead == NULL)
	{
		mHead = newNode;
	}
	else
	{
		mTail->mNext = newNode;
	}

	mTail = newNode;

	mCount++;
	return true;
}

/*
	Pre: Linked list has been populated with data
	Post: True returned if letter is found, false if not
	Purpose: To look through the linked list and find a specified search character
*/
bool Operations::letterExists(char searchChar)
{
	bool found = false;
	Node* tmp;
	tmp = mHead;

	while (tmp != NULL && !found)
	{
		if (searchChar == tmp->mChar)
		{
			found = true;
		}
		else
		{
			tmp = tmp->mNext;
		}
	}
	return found;
}

/*
	Pre: None
	Post: Linked list variables initialized to default values
	Purpose: Constructor
*/
Operations::Node::Node()
{
	mChar = ' ';
	mNum = 0;
	mNext = NULL;
}

/*
	Pre: None
	Post: Linked list variables are initialized to specified parameters
	Purpose: Constructor
*/
Operations::Node::Node(char entryChar, int entryNum)
{
	mChar = entryChar;
	mNum = entryNum;
	mNext = NULL;
}