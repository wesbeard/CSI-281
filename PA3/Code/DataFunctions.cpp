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

/*
	Pre: Function called with a max size parameter
	Post: Random data is generated and printed to the random data file
	Purpose: To generate random data between 1 and a million for a given data size
	References: http://www.cplusplus.com/reference/cstdlib/rand/
*/
void Data::generateData(int size) 
{
	ofstream fout;
	fout.open(RANDOM_FILE);
	random_device rd;
	default_random_engine generator(rd());

	//Generates an integer between 0 and 1M
	uniform_int_distribution<long unsigned> distribution(0, 1000000);

	//Prints data to file
	for (int i = 0; i < size; i++) {
		fout << distribution(generator) << endl;
	}
}

/*
	Pre: Function is called with the data size parameter
	Post: Randomized data is sorted in ascending order and printed to specified file
	Purpose: To sort the previously randomized data in ascending order
*/
void Data::initialAscendingSort(int size)
{
	ifstream fin;
	fin.open(RANDOM_FILE);
	int i;
	int j;
	int temp;

	long int *list;
	list = new long int[maxSize];

	//Loads data from file into a temporary array
	for (i = 0; i < size; i++)
	{
		fin >> temp;
		list[i] = temp;
	}

	//Sorts data and prints it into an ascending data file
	for (i = 1; i < size; i++)
	{
		temp = list[i];
		j = i - 1;

		while (j >= 0 && list[j] > temp)
		{
			list[j + 1] = list[j];
			j -= 1;
		}

		list[j + 1] = temp;
	}

	ofstream fout;
	fout.open(ASCENDING_FILE);
	for (i = 0; i < size; i++)
	{
		fout << list[i] << endl;
	}
}

/*
	Pre: Function is called with the data size parameter
	Post: Randomized data is sorted in descending order and printed to specified file
	Purpose: To sort the previously randomized data in descending order
*/
void Data::initialDescendingSort(int size)
{
	ifstream fin;
	fin.open(RANDOM_FILE);
	int i;
	int j;
	int temp;

	long int* list;
	list = new long int[maxSize];

	//Loads data from file into a temporary array
	for (i = 0; i < size; i++)
	{
		fin >> temp;
		list[i] = temp;
	}

	//Sorts data and prints it into a descending data file
	for (i = 1; i < size; i++)
	{
		temp = list[i];
		j = i - 1;

		while (j >= 0 && list[j] < temp)
		{
			list[j + 1] = list[j];
			j -= 1;
		}

		list[j + 1] = temp;
	}

	ofstream fout;
	fout.open(DESCENDING_FILE);
	for (i = 0; i < size; i++)
	{
		fout << list[i] << endl;
	}
}

/*
	Pre: Function is called with the size of the array and the file type to get the data from
	Post: Specific array size is loaded with data from specified data file
	Purpose: To initially load or refresh the data in the arrays
*/
void Data::loadArrays(int size, string fileType)
{
	int i;
	long int temp;
	ifstream fin;
	fin.open(fileType);

	//Fills array with data from respective data file
	if (size == lgSize)
	{
		for (i = 0; i < lgSize; i++)
		{
			fin >> temp;
			lgArray[i] = temp;
		}
	}
	else if (size == medSize)
	{
		for (i = 0; i < medSize; i++)
		{
			fin >> temp;
			medArray[i] = temp;
		}
	}
	else
	{
		for (i = 0; i < smSize; i++)
		{
			fin >> temp;
			smArray[i] = temp;
		}
	}
	fin.close();
}

/*
	Pre: Function is called with the type of data to be tested as a parameter
	Post: Small array is tested by different sorting algorithms
	Purpose: To test and time the various sorting algorithms with a small data set for a given data type and print the results to the console
*/
void Data::testSmallArray(string fileType)
{
	cout << "Small array test:" << endl;

	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(10);

	Data data;
	TimerSystem timer;

	data.loadArrays(smSize, fileType);
	cout << "Bubble Sort:" << endl;
	timer.startClock();
	data.bubbleSort(data.smArray, smSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(smSize, fileType);
	cout << "Insertion Sort:" << endl;
	timer.startClock();
	data.insertionSort(data.smArray, smSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(smSize, fileType);
	cout << "Selection Sort:" << endl;
	timer.startClock();
	data.selectionSort(data.smArray, smSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(smSize, fileType);
	cout << "Shell Sort:" << endl;
	timer.startClock();
	data.shellSort(data.smArray, smSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(smSize, fileType);
	cout << "Merge Sort:" << endl;
	timer.startClock();
	data.mergeSort(data.smArray, 0, smSize - 1);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(smSize, fileType);
	cout << "Quick Sort:" << endl;
	timer.startClock();
	data.quickSort(data.smArray, 0, smSize - 1);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;
}

/*
	Pre: Function is called with the type of data to be tested as a parameter
	Post: Medium array is tested by different sorting algorithms
	Purpose: To test and time the various sorting algorithms with a medium data set for a given data type and print the results to the console
*/
void Data::testMediumArray(string fileType)
{
	cout << endl << "Medium array test:" << endl;

	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(10);

	Data data;
	TimerSystem timer;

	data.loadArrays(medSize, fileType);
	cout << "Bubble Sort:" << endl;
	timer.startClock();
	data.bubbleSort(data.medArray, medSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(medSize, fileType);
	cout << "Insertion Sort:" << endl;
	timer.startClock();
	data.insertionSort(data.medArray, medSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(medSize, fileType);
	cout << "Selection Sort:" << endl;
	timer.startClock();
	data.selectionSort(data.medArray, medSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(medSize, fileType);
	cout << "Shell Sort:" << endl;
	timer.startClock();
	data.shellSort(data.medArray, medSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(medSize, fileType);
	cout << "Merge Sort:" << endl;
	timer.startClock();
	data.mergeSort(data.medArray, 0, medSize - 1);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(medSize, fileType);
	cout << "Quick Sort:" << endl;
	timer.startClock();
	data.quickSort(data.medArray, 0, medSize - 1);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;
}

/*
	Pre: Function is called with the type of data to be tested as a parameter
	Post: Large array is tested by different sorting algorithms
	Purpose: To test and time the various sorting algorithms with a large data set for a given data type and print the results to the console
*/
void Data::testLargeArray(string fileType)
{
	cout << endl << "Large array test:" << endl;

	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(10);

	Data data;
	TimerSystem timer;

	data.loadArrays(lgSize, fileType);
	cout << "Bubble Sort:" << endl;
	timer.startClock();
	data.bubbleSort(data.lgArray, lgSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(lgSize, fileType);
	cout << "Insertion Sort:" << endl;
	timer.startClock();
	data.insertionSort(data.lgArray, lgSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(lgSize, fileType);
	cout << "Selection Sort:" << endl;
	timer.startClock();
	data.selectionSort(data.lgArray, lgSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(lgSize, fileType);
	cout << "Shell Sort:" << endl;
	timer.startClock();
	data.shellSort(data.lgArray, lgSize);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(lgSize, fileType);
	cout << "Merge Sort:" << endl;
	timer.startClock();
	data.mergeSort(data.lgArray, 0, lgSize - 1);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;

	data.loadArrays(lgSize, fileType);
	cout << "Quick Sort:" << endl;
	timer.startClock();
	data.quickSort(data.lgArray, 0, lgSize - 1);
	cout << "Elapsed time: " << timer.getTime() << endl << endl;
}