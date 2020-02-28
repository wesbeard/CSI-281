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

#ifndef FINAL_H
#define FINAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

const string CODEBOOK = "codes.txt";

void loadCodeBook();
string getFileName();

#endif