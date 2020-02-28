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

int main()
{
	Operations operations;
	bool exit = false;

	do
	{
		operations.fileNames();

		operations.findNumAttributes();

		operations.readFile();

		operations.analyzeData();

		exit = operations.exitPrompt();

	} while (exit == false);
}