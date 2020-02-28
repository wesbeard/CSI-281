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

#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

using namespace std;

template <typename T>
class LinkedList
{
	template <typename R>
	struct Node
	{
		R mData;
		Node<R>* mNext;

		Node()
		{
			mData = R();
			mNext = NULL;
		}

		Node(R data)
		{
			mData = data;
			mNext = NULL;
		}
	};


private:
	Node<T>* mHead, * mTail;
	int mCount;

public:
	LinkedList();
	~LinkedList();

	int  getCount();
	T getData(int index);
	void setData(int index, T data);
	void clear();
	void display();
	bool insert(T data);
	bool isEmpty();
	bool isExist(T searchKey);
	bool remove(T searchKey);
	T operator[](int index);
};

/*
	Pre: None
	Post: Member variables initialized
	Purpose: Class constructor
*/
template <typename T>
LinkedList<T>::LinkedList()
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
LinkedList<T>::~LinkedList()
{
	clear();
}

/*
	Pre: None
	Post: Variable mCount returned
	Purpose: To return mCount when called
*/
template <typename T>
int LinkedList<T>::getCount()
{
	return mCount;
}

/*
	Pre: List has data
	Post: Value of index node returned
	Purpose: To obtain the data of a given index
*/
template <typename T>
T LinkedList<T>::getData(int index)
{
	int i;
	Node<T>* temp;
	T       data = T();

	if (index >= 0 && index < mCount)
	{
		temp = mHead;
		for (i = 0; i < index; i++)
			temp = temp->mNext;

		data = temp->mData;
	}

	return data;
}

/*
	Pre: Index and data provided as parameters
	Post: Data is set for specified index
	Purpose: To set the data of a node at a certain index
*/
template <typename T>
void LinkedList<T>::setData(int index, T data)
{
	int     i;
	Node<T>* temp;

	if (index >= 0 && index < mCount)
	{
		temp = mHead;
		for (i = 0; i < index; i++)
			temp = temp->mNext;

		temp->mData = data;
	}
}

/*
	Pre: List has data
	Post: All data cleared from list, reset to empty
	Purpose: To clear the data from the current list
*/
template <typename T>
void LinkedList<T>::clear()
{
	Node<T>* toBeDeleted;
	int i;

	for (i = 0; i < mCount; i++)
	{
		toBeDeleted = mHead;
		mHead = mHead->mNext;
		toBeDeleted->mNext = NULL;
		delete toBeDeleted;
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
void LinkedList<T>::display()
{
	Node<T>* temp;
	int     i;

	temp = mHead;
	for (i = 0; i < mCount; i++)
	{
		cout << temp->mData << endl;
		temp = temp->mNext;
	}
}

/*
	Pre: Data for new node provided as parameter
	Post: Data parameter is added as new node
	Purpose: To add a new node to the list
*/
template <typename T>
bool LinkedList<T>::insert(T data)
{
	Node<T>* newNode;
	Node<T>* oneBefore;
	Node<T>* temp;
	bool added = false;

	newNode = new Node<T>(data);

	if (newNode == NULL)
	{
		return added;
	}

	//Empty List
	if (mHead == NULL)
	{
		mHead = newNode;
		mTail = newNode;
		added = true;
	}

	//Insert at head
	else if (data < mHead->mData)
	{
		newNode->mNext = mHead;
		mHead = newNode;
		added = true;
	}

	//Insert at tail
	else if (data > mTail->mData)
	{
		mTail->mNext = newNode;
		mTail = newNode;
		added = true;
	}

	//Insert in the middle
	else
	{
		oneBefore = mHead;
		temp = mHead;
		while (temp->mData < data)
		{
			oneBefore = temp;
			temp = temp->mNext;
		}

		if (data != temp->mData)
		{
			oneBefore->mNext = newNode;
			newNode->mNext = temp;
			added = true;
		}
	}

	//If node has been added then increment count
	if (added)
	{
		mCount++;
	}
	//Otherwise delete unused new node
	else
	{
		delete newNode;
	}

	return added;
}

/*
	Pre: None
	Post: State of linked list returned
	Purpose: To return if the list is empty or not
*/
template <typename T>
bool LinkedList<T>::isEmpty()
{
	return mHead == NULL;
}

/*
	Pre: Search key for node data provided
	Post: Boolean returned if value from search key exists in list
	Purpose: To return if a value exists in the list
*/
template <typename T>
bool LinkedList<T>::isExist(T searchKey)
{
	return false;
}

/*
	Pre: Search key for node data provided
	Post: Node deleted if found in list based on search key data
	Purpose: To delete a specific node
*/
template <typename T>
bool LinkedList<T>::remove(T searchKey)
{
	Node<T>* temp;
	Node<T>* oneBefore;
	Node<T>* toBeDeleted;
	bool found = false;

	if (mHead != NULL)
	{
		temp = mHead;
		oneBefore = mHead;
		while (temp != NULL && !found)
		{
			if (temp->mData == searchKey)
				found = true;
			else if (temp->mData > searchKey)
				temp = NULL;
			else
			{
				oneBefore = temp;
				temp = temp->mNext;
			}
		}

		if (found)
		{
			toBeDeleted = temp;

			if (temp == mHead)
			{
				if (mHead == mTail)
				{
					mHead = NULL;
					mTail = NULL;
				}
				else
				{
					mHead = temp->mNext;
				}
			}
			else if (temp == mTail)
			{
				mTail = oneBefore;
				mTail->mNext = NULL;
			}
			else
			{
				oneBefore->mNext = temp->mNext;
			}

			toBeDeleted->mNext = NULL;
			delete toBeDeleted;

			mCount--;
		}
	}

	return found;
}

template <typename T>
T LinkedList<T>::operator[](int index)
{
	return getData(index);
}

#endif