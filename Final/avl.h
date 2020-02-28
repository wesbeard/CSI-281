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

#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <algorithm>

using namespace std;

class AVL
{
private:

	struct Node
	{
		int mNumber, mHeight;
		string mWord;
		Node* mLeft, * mRight;

		Node()
		{
			mNumber = 0;
			mWord = "";
			mHeight = 1;
			mLeft = NULL;
			mRight = NULL;
		}

		Node(int num, string word)
		{
			mNumber = num;
			mWord = word;
			mHeight = 1;
			mLeft = NULL;
			mRight = NULL;
		}

		Node(int num, string word, Node* left, Node* right)
		{
			mNumber = num;
			mWord = word;
			mHeight = 1;
			mLeft = NULL;
			mRight = NULL;
		}
	};

	Node* mRootNode;

	void insert(Node*& node, const int& num, const string& word);
	void destroySubtree(Node*& node);
	int  getBalance(Node* node);
	int  getHeight(Node* node);
	int  maxHeight(Node* node1, Node* node2);
	void rotateLeft(Node*& node);
	void rotateLeftRight(Node*& node);
	void rotateRight(Node*& node);
	void rotateRightLeft(Node*& node);

public:

	AVL();
	~AVL();

	bool find(int searchKey);
	void insert(int num, string word);
};

/*
PRE: None
POST: Member variables initialized
PURPOSE: Class constructor
*/
AVL::AVL()
{
	mRootNode = NULL;
}

/*
PRE: None
POST: Member variables deleted by calling destroy subtree function
PURPOSE: Class deconstructor
*/

AVL::~AVL()
{
	destroySubtree(mRootNode);

	mRootNode = NULL;
}

/*
PRE: Tree with valid data and node to start
POST: Data cleared of all subtrees from given node
PURPOSE: To destroy all descending information from a node
*/
void AVL::destroySubtree(Node*& node)
{
	if (node == NULL)
	{
		return;
	}

	destroySubtree(node->mLeft);
	destroySubtree(node->mRight);

	delete node;
	node = NULL;
}

/*
PRE: Search key for specific node provided
POST: Returns boolean based on if search key is found in tree
PURPOSE: To check whethor or not a piece of data exists in the tree
*/
bool AVL::find(int searchKey)
{
	Node* temp = mRootNode;
	bool found = false;

	while (temp != NULL)
	{
		if (temp->mNumber == searchKey)
		{
			cout << temp->mWord << " ";
			found = true;
			return found;
		}
		else if (temp->mNumber > searchKey)
		{
			temp = temp->mLeft;
		}
		else
		{
			temp = temp->mRight;
		}
	}
	return found;
}

/*
PRE: Node provided as parameter
POST: Balance for given node returned
PURPOSE: To get the balance factor for a given node
*/
int AVL::getBalance(Node* node)
{
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return getHeight(node->mRight) - getHeight(node->mLeft);
	}
}

/*
PRE: Node provided as parameter
POST: Height for given node returned
PURPOSE: To get the height for a given node
*/
int AVL::getHeight(Node* node)
{
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return node->mHeight;
	}
}

/*
PRE: None
POST: Insert function called with data and root node as parameters
PURPOSE: To insert data without requiring the root node as a parameter
*/
void AVL::insert(int num, string word)
{
	insert(mRootNode, num, word);
}

/*
PRE: Starting node and data provided
POST: Data added to tree
PURPOSE: To add given data to the tree based on a start node
*/
void AVL::insert(Node*& node, const int& num, const string& word)
{
	if (node == NULL)
	{
		node = new Node(num, word);
		return;
	}

	if (node->mNumber == num)
	{
		return;
	}

	if (num < node->mNumber)
	{
		insert(node->mLeft, num, word);

		if (getBalance(node) == -2)
		{
			if (getBalance(node->mLeft) == -1)
			{
				rotateRight(node);
			}
			else
			{
				rotateLeftRight(node);
			}
		}
	}
	else
	{
		insert(node->mRight, num, word);

		if (getBalance(node) == 2)
		{
			if (getBalance(node->mRight) == 1)
			{
				rotateLeft(node);
			}
			else
			{
				rotateRightLeft(node);
			}
		}
	}
	node->mHeight = maxHeight(node->mLeft, node->mRight) + 1;
}

/*
PRE: Two nodes given as parameters
POST: Returns height of taller node
PURPOSE: To compare node heights
*/
int AVL::maxHeight(Node* node1, Node* node2)
{
	int heightNode1, heightNode2;

	if (node1 == NULL)
	{
		heightNode1 = 0;
	}
	else
	{
		heightNode1 = node1->mHeight;
	}

	if (node2 == NULL)
	{
		heightNode2 = 0;
	}
	else
	{
		heightNode2 = node2->mHeight;
	}

	if (heightNode1 >= heightNode2)
	{
		return heightNode1;
	}
	else
	{
		return heightNode2;
	}
}

/*
PRE: Node to be rotated given as parameter
POST: Node structure rotated to the left
PURPOSE: To balance the tree by rotating nodes left
*/
void AVL::rotateLeft(Node*& node)
{
	Node* tmp = node->mRight;

	node->mRight = tmp->mLeft;
	tmp->mLeft = node;
	node->mHeight = maxHeight(node->mLeft, node->mRight) + 1;
	tmp->mHeight = max(getHeight(tmp->mRight), node->mHeight) + 1;
	node = tmp;
}

/*
PRE: Node to be rotated given as parameter
POST: Rotates left of node to the left and then parameter node to the right
PURPOSE: To perform a left-right rotation to balance the tree
*/
void AVL::rotateLeftRight(Node*& node)
{
	rotateLeft(node->mLeft);
	rotateRight(node);
}

/*
PRE: Node to be rotated given as parameter
POST: Node structure rotated to the right
PURPOSE: To balance the tree by rotating nodes right
*/
void AVL::rotateRight(Node*& node)
{
	Node* tmp = node->mLeft;

	node->mLeft = tmp->mRight;
	tmp->mRight = node;
	node->mHeight = max(getHeight(node->mLeft), getHeight(node->mRight)) + 1;
	tmp->mHeight = max(getHeight(tmp->mLeft), node->mHeight) + 1;
	node = tmp;
}

/*
PRE: Node to be rotated given as parameter
POST: Rotates right of node to the right and then parameter node to the left
PURPOSE: To perform a right-left rotation to balance the tree
*/
void AVL::rotateRightLeft(Node*& node)
{
	rotateRight(node->mRight);
	rotateLeft(node);
}

#endif