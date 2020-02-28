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
#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "timerSystem.h"

int main() 
{
	const long SMALL = 1000;
	const long MEDIUM = 10000;
	const long LARGE = 100000;
	const int PRECISION = 2;
	
	const string OUTPUT_FILE = "data\\output.txt";
	TimerSystem timer;
	int i, runNumber;
	long random1, random2, random3;

	LinkedList<long> linkedList;
	DoublyLinkedList<long> doublyLinkedList;
	long* data = new long[LARGE];

	generateData(OUTPUT_FILE, LARGE);



	//test array add
	cout << "Array add" << endl << endl;
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{
		cout << "Test " << runNumber << ": " << endl << endl;
		
		cout << "Add: 1000\n";
		timer.startClock();
		getData(SMALL, data, OUTPUT_FILE);
		cout << "Array add and sort: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Add: 10000\n";
		timer.startClock();
		getData(MEDIUM, data, OUTPUT_FILE);
		cout << "Array add and sort: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Add: 100000\n";
		timer.startClock();
		getData(LARGE, data, OUTPUT_FILE);
		cout << "Array add and sort: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;
	}

	//array find
	cout << "Array find\n\n";
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{
		random1 = generateNumber(SMALL);
		random2 = generateNumber(MEDIUM);
		random3 = generateNumber(LARGE);

		cout << "Test " << runNumber << ": " << endl << endl;


		cout << "Random 1:" << endl;
		timer.getTime();
		cout << "Finding number " << random1 << ": " << ((searchArray(data, SMALL, random1)) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 2:" << endl;
		timer.getTime();
		cout << "Finding number " << random2 << ": " << (searchArray(data, MEDIUM, random2) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 3:" << endl;
		timer.getTime();
		cout << "Finding number " << random3 << ": " << (searchArray(data, MEDIUM, random3) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;		
	}


	//ngl this is basically the same exact things as find
	//array delete
	cout << "Array delete\n\n";
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{

	}
	

	//linked list add
	cout << "\nLinked list add" << endl << endl;
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{
		cout << "Test " << runNumber << ": " << endl << endl;

		cout << "Add: 1000\n";
		getData(SMALL, data, OUTPUT_FILE);
		timer.startClock();
		for (i = 0; i < SMALL; i++)
		{
			linkedList.insert(data[i]);
		}
		cout << "Linked list add: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;
		linkedList.clear();

		cout << "Add: 10000\n";
		getData(MEDIUM, data, OUTPUT_FILE);
		timer.startClock();
		for (i = 0; i < MEDIUM; i++)
		{
			linkedList.insert(data[i]);
		}
		cout << "Linked list add: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;
		linkedList.clear();

		cout << "Add: 100000\n";
		getData(LARGE, data, OUTPUT_FILE);
		timer.startClock();
		for (i = 0; i < LARGE; i++)
		{
			linkedList.insert(data[i]);
		}
		cout << "Linked list add: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;
		linkedList.clear();
	}


	//linked list find

	//load a fresh list to search in
	for (i = 0; i < MEDIUM; i++)
	{
		linkedList.insert(data[i]);
	}
	
	cout << "\nLinked List Find" << endl << endl;
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{
		random1 = generateNumber(SMALL);
		random2 = generateNumber(MEDIUM);
		random3 = generateNumber(LARGE);

		cout << "Test " << runNumber << ": " << endl << endl;


		cout << "Random 1:" << endl;
		timer.getTime();
		cout << "Finding number " << random1 << ": " << ((linkedList.isExist(random1)) ? "true" : "false") << "\n" 
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 2:" << endl;
		timer.getTime();
		cout << "Finding number " << random2 << ": " << (linkedList.isExist(random2) ? "true" : "false") << "\n" 
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 3:" << endl;
		timer.getTime();
		cout << "Finding number " << random3 << ": " << (linkedList.isExist(random3) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

	}

	//linked list delete
	cout << "Linked list delete" << endl << endl;
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{

		random1 = generateNumber(SMALL);
		random2 = generateNumber(MEDIUM);
		random3 = generateNumber(LARGE);

		cout << "Test " << runNumber << ": " << endl << endl;

		cout << "Random 1:" << endl;
		timer.getTime();
		cout << "Deleting number " << random1 << ": " << ((linkedList.remove(random1)) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 2:" << endl;
		timer.getTime();
		cout << "Deleting number " << random2 << ": " << (linkedList.remove(random2) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 3:" << endl;
		timer.getTime();
		cout << "Deleting number " << random3 << ": " << (linkedList.remove(random3) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

	}


	//double linked list
	cout << "Doubly Linked List" << endl << endl;

	//double linked list add
	cout << "\nDoubly Linked list add" << endl << endl;
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{
		cout << "Test " << runNumber << ": " << endl << endl;

		cout << "Add: 1000\n";
		getData(SMALL, data, OUTPUT_FILE);
		timer.startClock();
		for (i = 0; i < SMALL; i++)
		{
			doublyLinkedList.insert(data[i]);
		}
		cout << "Doubly linked list add: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;
		doublyLinkedList.clear();


		cout << "Add: 10000\n";
		getData(MEDIUM, data, OUTPUT_FILE);
		timer.startClock();
		for (i = 0; i < MEDIUM; i++)
		{
			doublyLinkedList.insert(data[i]);
		}
		cout << "Doubly linked list add: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;
		doublyLinkedList.clear();

		cout << "Add: 100000\n";
		getData(LARGE, data, OUTPUT_FILE);
		timer.startClock();
		for (i = 0; i < LARGE; i++)
		{
			doublyLinkedList.insert(data[i]);
		}
		cout << "Doubly linked list add: " << fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;
		doublyLinkedList.clear();
		
	}


	//doubly linked list find

	//load a fresh list to search in
	for (i = 0; i < MEDIUM; i++)
	{
		doublyLinkedList.insert(data[i]);
	}

	cout << "\nDoubly linked List find" << endl << endl;
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{
		random1 = generateNumber(SMALL);
		random2 = generateNumber(MEDIUM);
		random3 = generateNumber(LARGE);

		cout << "Test " << runNumber << ": " << endl << endl;


		cout << "Random 1:" << endl;
		timer.getTime();
		cout << "Finding number " << random1 << ": " << ((doublyLinkedList.isExist(random1)) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 2:" << endl;
		timer.getTime();
		cout << "Finding number " << random2 << ": " << (doublyLinkedList.isExist(random2) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 3:" << endl;
		timer.getTime();
		cout << "Finding number " << random3 << ": " << (doublyLinkedList.isExist(random3) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

	}


	//doubly linked list delete
	cout << "\nDoubly linked list delete" << endl << endl;
	for (runNumber = 1; runNumber <= 3; runNumber++)
	{

		random1 = generateNumber(SMALL);
		random2 = generateNumber(MEDIUM);
		random3 = generateNumber(LARGE);

		cout << "Test " << runNumber << ": " << endl << endl;

		cout << "Random 1:" << endl;
		timer.getTime();
		cout << "Deleting number " << random1 << ": " << ((doublyLinkedList.remove(random1)) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 2:" << endl;
		timer.getTime();
		cout << "Deleting number " << random2 << ": " << (doublyLinkedList.remove(random2) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

		cout << "Random 3:" << endl;
		timer.getTime();
		cout << "Deleting number " << random3 << ": " << (doublyLinkedList.remove(random3) ? "true" : "false") << "\n"
			<< fixed << scientific << setprecision(PRECISION) << timer.getTime() << endl << endl;

	}

	system("pause");
	return 1;
}