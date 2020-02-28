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

#ifndef PA4
#define PA4

#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <istream>
#include <iomanip>
using namespace std;


void generateData(string fileName, long size);
long generateNumber(long maxSize);

/*
PRE: List, size, and search key provided as parameters
POST: State of boolean found returned
PURPOSE: To search the provided array for a search key
*/
template<typename T>
bool searchArray(T* list, long size, T searchKey)
{
	bool found = false;

	for (long i = 0; i < size; i++)
	{
		if (list[i] == searchKey)
			found = true;
	}

	return found;
}

/*
PRE: a long, an array of data, a filename
POST: reads data from the file into the array
PURPOSE: reads data from a file into an array
*/
template<typename T>
void getData(long size, T data[], string fileName)
{
	const long LINE_LENGTH = 999;
	long i, j = 0;
	string trash;
	ifstream input;

	input.open(fileName);

	for (i = 0; i < size; i++)
	{
		input >> data[i];
		if (j == LINE_LENGTH)
		{
			getline(input, trash);
			j = 0;
		}

		j++;
	}
}
#endif