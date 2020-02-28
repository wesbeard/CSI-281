/*
Author: Wes Beard & Louis Vinton
Class: CSI-281: Data Structures and Algorithms
Assignment: Programming Assignment 4 Part 3
Date Assigned: 10/28/2019
Due Date: 11/4/2019
Description:
	A program that uses multiple data structures (array, linked list, and doubly linked list)
Certification of Authenticity:
	I certify that this is entirely my own work, except where I have given fully-documented references to the work of others.
	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
		- Reproduce this assignment and provide a copy to another member of academic staff; and/or
		- Communicate a copy of this assignment to a plagiarism checking service
		(which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)
*/

#include "PA4.h"

/*
PRE: a filename and a long
POST: generate an amount of random data equal to size and saves it to a file. Data is between 0-1000000.
PURPOSE: generates data and stores it in the given file.
*/
void generateData(string fileName, long size)
{
	const long MAX_NUM = 10000;
	const int LINE_LENGTH = 999;
	long i, j = 0;
	ofstream output;

	output.open(fileName);

	for (i = 0; i < size; i++)
	{
		output << generateNumber(MAX_NUM) << " ";
		if (j == LINE_LENGTH)
		{
			output << endl;
			j = 0;
		}

		j++;
	}
}

/*
PRE: a long
POST: returns a random number using uniform real distribution using the given long as the largest it could be
PURPOSE: generates a random number
*/
long generateNumber(long maxSize) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, maxSize + 1);
	return dis(gen);
}