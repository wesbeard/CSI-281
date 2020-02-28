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

#ifndef PA3
#define PA3

#include <iostream>
#include <random>
#include <fstream>

using namespace std;

//Edit to change size of data generation
const int maxSize = 1000000;

//Edit to change size of respective arrays
const int smSize  = 100;
const int medSize = 10000;
const int lgSize  = 1000000;

//Edit to change data storage files
const string RANDOM_FILE = "data.txt";
const string ASCENDING_FILE = "ascending.txt";
const string DESCENDING_FILE = "descending.txt";

struct Data
{
	long int smArray[smSize];
	long int medArray[medSize];
	long int lgArray[lgSize];

	//Templates
	template <typename T>
	void bubbleSort(T list[], int size);

	template <typename T>
	void insertionSort(T list[], int size);

	template <typename T>
	void selectionSort(T list[], int size);

	template <typename T>
	void shellSort(T list[], int size);

	template <typename T>
	void mergeSort(T list[], int lowerBound, int upperBound);

	template <typename T>
	void merge(T list[], int lowerBound, int middle, int upperBound);

	template <typename T>
	void quickSort(T list[], int lowerBound, int upperBound);

	//Data Functions
	void generateData(int size);
	void initialAscendingSort(int size);
	void initialDescendingSort(int size);
	void loadArrays(int size, string fileType);
	void testSmallArray(string fileType);
	void testMediumArray(string fileType);
	void testLargeArray(string fileType);
};

//TEMPLATE DEFINITIONS

/*
	Pre: Function called with array to sort and size of array
	Post: Array is sorted from a random state
	Purpose: To sort an array through the bubble sort method
*/
template <typename T>
void Data::bubbleSort(T list[], int size)
{
	bool swapped = true;
	int i;
	T temp;

	while (swapped == true)
	{
		swapped = false;
		for (i = 0; i < size - 1; i++)
		{
			if (list[i + 1] < list[i])
			{
				temp = list[i + 1];
				list[i + 1] = list[i];
				list[i] = temp;
				swapped = true;
			}
		}
	}
}

/*
	Pre: Function called with array to sort and size of array
	Post: Array is sorted from a random state
	Purpose: To sort an array through the insertion sort method
*/
template <typename T>
void Data::insertionSort(T list[], int size)
{
	int i, j;
	T temp;

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
}

/*
	Pre: Function called with array to sort and size of array
	Post: Array is sorted from a random state
	Purpose: To sort an array through the selection sort method
*/
template <typename T>
void Data::selectionSort(T list[], int size)
{
	int i, j, minimum;
	T temp;

	for (i = 0; i < size - 1; i++)
	{
		minimum = i;
		for (j = i + 1; j < size; j++)
		{
			if (list[j] < list[minimum])
			{
				minimum = j;
			}
		}
		if (minimum != i)
		{
			temp = list[minimum];
			list[minimum] = list[i];
			list[i] = temp;
		}
	}
}

/*
	Pre: Function called with array to sort and size of array
	Post: Array is sorted from a random state
	Purpose: To sort an array through the shell sort method
*/
template <typename T>
void Data::shellSort(T list[], int size)
{
	int i;

	int gap = size / 2;
	bool swapped = true;
	T temp;

	//Shell sort
	while (gap > 0)
	{
		for (i = 0; i < size - gap; i++)
		{
			if (list[i] > list[i + gap])
			{
				temp = list[i];
				list[i] = list[i + gap];
				list[i + gap] = temp;
			}
		}
		gap /= 2;
	}
	//Bubble sort to finish
	while (swapped == true)
	{
		swapped = false;
		for (i = 0; i < size - 1; i++)
		{
			if (list[i + 1] < list[i])
			{
				temp = list[i + 1];
				list[i + 1] = list[i];
				list[i] = temp;
				swapped = true;
			}
		}
	}
}

/*
	Pre: Function called inside merge sort function
	Post: Merge sort arrays are combined to form a sorted array
	Purpose: To combine the seperate arrays
	References: https://appdividend.com/2019/04/30/merge-sort-in-cpp-tutorial-with-example-cpp-merge-sort-program/
*/
template <typename T>
void Data::merge(T list[], int lowerBound, int middle, int upperBound)
{
	int i, j, k;

	int size1 = middle - lowerBound + 1;
	int size2 = upperBound - middle;

	T* tmp1 = new T[size1];
	T* tmp2 = new T[size2];

	for (i = 0; i < size1; i++)
	{
		tmp1[i] = list[lowerBound + i];
	}

	for (j = 0; j < size2; j++)
	{
		tmp2[j] = list[middle + j + 1];
	}

	i = 0;
	j = 0;

	for (k = lowerBound; i < size1 && j < size2; k++)
	{
		if (tmp1[i] <= tmp2[j])
		{
			list[k] = tmp1[i];
			i++;
		}
		else
		{
			list[k] = tmp2[j];
			j++;
		}
	}

	while (i < size1)
	{
		list[k] = tmp1[i];
		k++;
		i++;
	}

	while (j < size2)
	{
		list[k] = tmp2[j];
		k++;
		j++;
	}
	delete[] tmp1;
	delete[] tmp2;
}

/*
	Pre: Function called with array to be sorted, lower bound, and upper bound
	Post: Array is sorted from random state
	Purpose: To sort an array through the merge sort method
*/
template <typename T>
void Data::mergeSort(T list[], int lowerBound, int upperBound)
{
	int middle;

	if (lowerBound < upperBound)
	{
		middle = (lowerBound + upperBound) / 2;

		mergeSort(list, lowerBound, middle);
		mergeSort(list, middle + 1, upperBound);
		merge(list, lowerBound, middle, upperBound);
	}
}

/*
	Pre: Function called with array to be sorted, lower bound, and upper bound
	Post: Array is sorted from random state
	Purpose: To sort an array through the quick sort method
*/
template <typename T>
void Data::quickSort(T list[], int lowerBound, int upperBound)
{
	int i, j;
	T pivot;
	T temp;

	i = lowerBound;
	j = upperBound;

	pivot = list[(lowerBound + upperBound) / 2];

	while (i < j)
	{
		while (list[i] < pivot)
		{
			i++;
		}
		while (list[j] > pivot)
		{
			j--;
		}
		if (i <= j)
		{
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
			i++;
			j--;
		}
	}

	if (lowerBound < j)
	{
		quickSort(list, lowerBound, j);
	}
	if (i < upperBound)
	{
		quickSort(list, i, upperBound);
	}
}

#endif