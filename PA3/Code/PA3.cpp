/*
Author: Wes Beard
Class: CSI-281: Data Structures and Algorithms
Assignment: Programming Assignment 3 Part 2
Date Assigned: 9/23/2019
Due Date: 9/30/2019
Description:
	A program that times the efficiency of multiple sorting algorithms in different scenarios
Certification of Authenticity:
	I certify that this is entirely my own work, except where I have given fully-documented references to the work of others.
	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
		- Reproduce this assignment and provide a copy to another member of academic staff; and/or
		- Communicate a copy of this assignment to a plagiarism checking service
		(which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)
*/

#include "PA3.h"
#include "Timer.h"

int main()
{
	Data data;
	TimerSystem timer;
	ifstream fin;

	//The following statements check if data files already exist to save time in data creation, if they don't exist they create new ones
	//File names can be changed in the header
	fin.open(RANDOM_FILE);
	if (fin.fail())
	{
		data.generateData(maxSize);
	}
	fin.close();

	fin.open(ASCENDING_FILE);
	if (fin.fail())
	{
		data.initialAscendingSort(maxSize);
	}
	fin.close();

	fin.open(DESCENDING_FILE);
	if (fin.fail())
	{
		data.initialDescendingSort(maxSize);
	}
	fin.close();

	//Tests functions based on array data, parameters dictate what type of data each uses

	data.testSmallArray(RANDOM_FILE);
	data.testMediumArray(RANDOM_FILE);
	data.testLargeArray(RANDOM_FILE);

	data.testSmallArray(DESCENDING_FILE);
	data.testMediumArray(DESCENDING_FILE);
	data.testLargeArray(DESCENDING_FILE);

	data.testSmallArray(ASCENDING_FILE);
	data.testMediumArray(ASCENDING_FILE);
	data.testLargeArray(ASCENDING_FILE);
}