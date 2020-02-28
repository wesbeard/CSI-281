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

#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList
{
private:
	template <typename R>
	struct Node
	{
		R mData;
		Node<R>* mNext;
		Node<R>* mPrevious;
		Node()
		{
			mData = R();
			mNext = NULL;
			mPrevious = NULL;
		}
		Node(R data)
		{
			mData = data;
			mNext = NULL;
			mPrevious = NULL;
		}
	};

	Node<T>* mHead, * mTail;
	int     mCount;

public:
	DoublyLinkedList();
	~DoublyLinkedList();

	int  getCount();
	T getData(int index);
	void setData(int index, T data);

	void clear();
	void display();
	void insert(T data);
	bool isEmpty();
	bool isExist(T searchKey);
	bool remove(T searchKey);
};

/*
	Pre: None
	Post: Member variables are initialized
	Purpose: Class constructor
*/
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	mHead = NULL;
	mTail = NULL;
	mCount = 0;
}

/*
	Pre: None
	Post: Member variables are deconstructed by calling clear function
	Purpose: Class desconstructed
*/
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();
}

/*
	Pre: None
	Post: Variable mCount returned
	Purpose: To return mCount when called
*/
template <typename T>
int DoublyLinkedList<T>::getCount()
{
	return mCount;
}

/*
	Pre: List has data
	Post: Value of index node returned
	Purpose: To obtain the data of a given index
*/
template <typename T>
T DoublyLinkedList<T>::getData(int index)
{
	int i;
	Node<T>* temp;

	temp = mHead;
	for (i = 0; i < index; i++)
	{
		temp = temp->mNext;
	}

	return temp->mData;
}

/*
	Pre: Index and data provided as parameters
	Post: Data is set for specified index
	Purpose: To set the data of a node at a certain index
*/
template <typename T>
void DoublyLinkedList<T>::setData(int index, T data)
{
	int i;
	Node<T>* temp;

	temp = mHead;
	for (i = 0; i < index; i++)
		temp = temp->mNext;

	temp->mData = data;
}

/*
	Pre: List has data
	Post: All data cleared from list, reset to empty
	Purpose: To clear the data from the current list
*/
template <typename T>
void DoublyLinkedList<T>::clear()
{
	int i;
	Node<T>* temp;
	for (i = 0; i < mCount; i++)
	{
		temp = mHead;
		mHead = mHead->mNext;
		delete temp;
	}
	mHead = NULL;
	mTail = NULL;
	mCount = 0;
}

/*
	Pre: None
	Post: Data of list is displayed to console, if no data exists in the list then it displays no data
	Purpose: To display the contents of the list
*/
template <typename T>
void DoublyLinkedList<T>::display()
{
	Node<T>* temp;

	if (mHead == NULL)
	{
		cout << "The list is empty" << endl;
		return;
	}

	temp = mHead;
	while (temp != NULL)
	{
		cout << temp->mData << " ";
		temp = temp->mNext;
	}
	cout << endl;
}

/*
	Pre: Data for new node provided as parameter
	Post: Data parameter is added as new node
	Purpose: To add a new node to the list
*/
template <typename T>
void DoublyLinkedList<T>::insert(T data)
{
	Node<T>* newNode, * temp, * oneBefore;

	newNode = new Node<T>(data);

	if (mHead == NULL)
	{
		mHead = newNode;
		mTail = newNode;
	}
	else
	{

		if (data <= mHead->mData)
		{
			newNode->mNext = mHead;
			mHead->mPrevious = newNode;
			mHead = newNode;
		}
		else if (data >= mTail->mData)
		{
			mTail->mNext = newNode;
			newNode->mPrevious = mTail;
			mTail = newNode;
		}
		else
		{
			temp = mHead;
			while (temp->mData < data)
				temp = temp->mNext;

			oneBefore = temp->mPrevious;

			oneBefore->mNext = newNode;
			newNode->mPrevious = oneBefore;

			newNode->mNext = temp;
			temp->mPrevious = newNode;
		}
	}

	mCount++;
}

/*
	Pre: None
	Post: State of linked list returned
	Purpose: To return if the list is empty or not
*/
template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
	return mCount == 0;
}

/*
	Pre: Search key for node data provided
	Post: Boolean returned if value from search key exists in list
	Purpose: To return if a value exists in the list
*/
template <typename T>
bool DoublyLinkedList<T>::isExist(T searchKey)
{
	bool found = false;
	Node<T>* temp = mHead;
	int lowerBound = 0;
	int upperBound = mCount - 1;
	int mid, previous = 0, i;

	while (lowerBound <= upperBound)
	{
		mid = (lowerBound + upperBound) / 2;

		if (mid > previous)
		{
			for (i = previous; i < mid; i++)
			{
				temp = temp->mNext;
			}
		}
		else
		{
			for (i = previous; i > mid; i--)
			{
				temp = temp->mPrevious;
			}
		}
		if (temp->mData == searchKey)
		{
			found = true;
			break;
		}
		else
		{
			if (temp->mData < searchKey)
			{
				lowerBound = mid + 1;
			}
			else
			{
				upperBound = mid - 1;
			}

			previous = mid;
		}
	}

	return found;
}

/*
	Pre: Search key for node data provided
	Post: Node deleted if found in list based on search key data
	Purpose: To delete a specific node
*/
template <typename T>
bool DoublyLinkedList<T>::remove(T searchKey)
{
	Node<T>* temp;
	Node<T>* oneBefore;
	Node<T> *toBeDeleted;
	bool found = false;
	toBeDeleted = mHead;

	if (mHead != NULL)
	{
		if (searchKey < mHead->mData);
		else if (searchKey > mTail->mData);
		else if (searchKey == mHead->mData)
		{
			found = true;
			toBeDeleted = mHead;

			if (mCount == 1)
			{
				mHead = NULL;
				mTail = NULL;
			}
			else
			{
				mHead = mHead->mNext;
				mHead->mPrevious = NULL;
			}
		}
		else if (searchKey == mTail->mData)
		{
			found = true;
			toBeDeleted = mTail;
			mTail = mTail->mPrevious;
			mTail->mNext = NULL;
			toBeDeleted->mPrevious = NULL;
		}
		else
		{
			temp = mHead;
			while (temp != NULL && !found)
			{
				if (temp->mData == searchKey)
				{
					found = true;
					break;
				}
				else
					temp = temp->mNext;
			}

			if (found)
			{
				toBeDeleted = temp;
			}
		}

		if (found)
		{
			oneBefore = toBeDeleted->mPrevious;

			if (oneBefore != NULL)
				oneBefore->mNext = toBeDeleted->mNext;
			if (toBeDeleted->mNext != NULL)
				toBeDeleted->mNext->mPrevious = oneBefore;

			toBeDeleted->mNext = NULL;
			toBeDeleted->mPrevious = NULL;

			delete toBeDeleted;

			mCount--;
		}
	}

	return found;
}

#endif