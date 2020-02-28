/*
Author: Wes Beard
Class: CSI-281: Data Structures and Algorithms
Assignment: Programming Assignment 5
Date Assigned: 11/4/2019
Due Date: 11/18/2019
Description:
	A binary search tree that can be used to add nodes, search for nodes, print the tree, and list various statistics about it
Certification of Authenticity:
	I certify that this is entirely my own work, except where I have given fully-documented references to the work of others.
	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
		- Reproduce this assignment and provide a copy to another member of academic staff; and/or
		- Communicate a copy of this assignment to a plagiarism checking service
		(which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)
*/

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <queue>

using namespace std;

template <typename T>
class BST
{
	private:
      template <typename R>
      struct Node
      {
         R       mData;
         Node<R> *mLeft, *mRight;

         Node()
         {
            mData = R();
            mLeft = NULL;
            mRight = NULL;
         }

         Node(R data)
         {
            mData = data;
            mLeft = NULL;
            mRight = NULL;
         }

         Node(R data, Node<R> *left, Node<R> *right)
         {
            mData = data;
            mLeft = left;
            mRight = right;
         }
      };

		Node<T> *mRootNode;

      BST(T data, Node<T> *left, Node<T> *right);

		void destroySubtree(Node<T> *&node);
		void displayInOrder(Node<T> *node);
		void displayPreOrder(Node<T> *node);
		void displayPostOrder(Node<T> *node);
        void displayTree(Node<T> *node, int tab);
		void insert(Node<T> *&node, const T &data);
		void makeDeletion(Node<T> *&node);
		void remove(Node<T> *&node, const T &searchKey);
		void recursiveNodes(Node<T>* node, int &numNodes);
		void recursiveLeaves(Node<T>* node, int &numLeaves);
		bool recursivePath(Node<T>* root, T &findNode);
		int  recursiveHeight(Node<T>* node);
		bool recursiveDFS(Node<T>* node, T searchKey);

	public:
		BST();
		~BST();

      bool bfs(T searchKey);
      void clear();
      bool dfs(T searchKey);
      int  getHeight();
	  void insert(T data);
      bool isEmpty();
	  bool isExists(T searchKey);
      int  leavesCount();
      int  nodesCount();
	  void remove(T searchKey);
      void printPath(T nodeToFind);
	  void showInOrder();
      void showPreOrder();
	  void showPostOrder();
      void showTree();
};

/*
PRE: None
POST: Member variables initialized
PURPOSE: Class constructor
*/
template <typename T>
BST<T>::BST()
{
	mRootNode = NULL;
}

/*
PRE: None
POST: Member variables initialized to parameters
PURPOSE: Class constructor
*/
template <typename T>
BST<T>::BST(T data, Node<T> *left, Node<T> *right)
{
   Node<T> *newNode;

   newNode = new Node<T>(data, left, right);
   if (newNode != NULL)
	   mRootNode = newNode;
}

/*
PRE: None
POST: Member variables deleted by calling destroy subtree function
PURPOSE: Class deconstructor
*/
template <typename T>
BST<T>::~BST()
{
	destroySubtree(mRootNode);

   mRootNode = NULL;
}

/*
PRE: Tree created with valid data and data to search for
POST: If node is found true is returned and path to node is printed otherwise return false
PURPOSE: To search the tree using the BFS method
*/
template <typename T>
bool BST<T>::bfs(T searchKey)
{
	queue<Node<T>*> nodes;
	Node<T>* temp;
	bool found = false;

	//Return if root is null
	if (mRootNode == NULL)
	{
		return found;

	}
	else
	{
		//Start with root node
		nodes.push(mRootNode);

		do
		{
			//Set temp equal to last node
			temp = nodes.front();
			nodes.pop();

			//Check current node information
			if (temp->mData == searchKey)
			{
				found = true;
			}
			if (temp->mLeft != NULL)
			{
				nodes.push(temp->mLeft);
			}
			if (temp->mRight != NULL)
			{
				nodes.push(temp->mRight);
			}

		} while (!nodes.empty());

		//Evaluated if found or not
		if (found)
		{
			cout << "BFS: Node found" << endl;
			cout << "Path to node " << searchKey << ": ";
			printPath(searchKey);
			return found;
		}
		else
		{
			cout << "Node not found..." << endl;
			return found;
		}
	}
}

/*
PRE: Tree with valid data
POST: Tree cleared of all data using destroy subtree function
PURPOSE: To clear the tree
*/
template <typename T>
void BST<T>::clear()
{
   destroySubtree(mRootNode);
}

/*
PRE: Tree with valid data and node to start
POST: Data cleared of all subtrees from given node
PURPOSE: To destroy all descending information from a node
*/
template <typename T>
void BST<T>::destroySubtree(Node<T> *&node)
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
PRE: Tree with valid data and data to search for
POST: Returns true and prints path to node if found otherwise returns false
PURPOSE: To search the tree for a search terms and return based on results
*/
template <typename T>
bool BST<T>::dfs(T searchKey)
{
	bool found = recursiveDFS(mRootNode, searchKey);

	if (found)
	{
		return true;
	}
	else
	{
		cout << "Node not found...";
	}
}

/*
PRE: Tree with valid data and node to start with
POST: Prints tree data to console in order from left to right
PURPOSE: To display tree data in the in order format
*/
template <typename T>
void BST<T>::displayInOrder(Node<T> *node)
{
	//Return if node is null
	if (node == NULL)
	{
		return;
	}

	//Goes through left nodes first
	displayInOrder(node->mLeft);
	//prints current node data
	cout << node->mData << " ";
	//Goes through right nodes
	displayInOrder(node->mRight);
}

/*
PRE: Tree with valid data and node to start with
POST: Prints pre order tree data
PURPOSE: To display tree data in the pre order format
*/
template <typename T>
void BST<T>::displayPreOrder(Node<T> *node)
{
	//Return if node is null
	if (node == NULL)
	{
		return;
	}
	//prints current node data
	cout << node->mData << " ";
	//Goes through left nodes first
	displayPreOrder(node->mLeft);
	//Goes through right nodes
	displayPreOrder(node->mRight);
}

/*
PRE: Tree with valid data and node to start with
POST: Prints post order tree data
PURPOSE: To display tree data in the post order format
*/
template <typename T>
void BST<T>::displayPostOrder(Node<T> *node)
{
	//Return if node is null
	if (node == NULL)
	{
		return;
	}

	//Goes through left nodes first
	displayPostOrder(node->mLeft);
	//Goes through right nodes
	displayPostOrder(node->mRight);
	//prints current node data
	cout << node->mData << " ";
}

/*
PRE: Start node and tab amount
POST: Displays tree data visually
PURPOSE: To recursively display all nodes in the tree and visualize the shape
*/
template <typename T>
void BST<T>::displayTree(Node<T> *node, int tab)
{
	int i;

	//Return if node is NULL
	if (node == NULL)
	{
		return;
	}

	//Increases tab by given amount
	tab += 5;
	
	//Recursive function call for right nodes
	displayTree(node->mRight, tab);

	//Prints number of spaces depending on tab amount and then prints current node data
	cout << endl;
	for (i = 0; i < tab; i++)
	{
		cout << " ";
	}
	cout << node->mData << endl;

	//Recursive function call for left nodes
	displayTree(node->mLeft, tab);
}

/*
PRE: None
POST: Height of tree returned based on results from recursive function
PURPOSE: To call the recursive function which determines the height of the tree
*/
template <typename T>
int BST<T>::getHeight()
{
	int height;
	height = recursiveHeight(mRootNode);
	return height;
}

/*
PRE: None
POST: Insert function called with data and root node as parameters
PURPOSE: To insert data without requiring the root node as a parameter
*/
template <typename T>
void BST<T>::insert(T data)
{
	insert(mRootNode, data);
}

/*
PRE: Starting node and data provided
POST: Data added to tree
PURPOSE: To add given data to the tree based on a start node
*/
template <typename T>
void BST<T>::insert(Node<T> *&node, const T &data)
{
	if (node == NULL)
	{
		node = new Node<T>(data);
		return;
	}
	if (data < node->mData)
	{
		insert(node->mLeft, data);
	}
	else if (data > node->mData)
	{
		insert(node->mRight, data);
	}
}

/*
PRE: None
POST: Boolean returned depending on if root node is null or not
PURPOSE: To determine if the tree is empty
*/
template <typename T>
bool BST<T>::isEmpty()
{
   return (mRootNode == NULL);
}

/*
PRE: Search key for specific node provided
POST: Returns boolean based on if search key is found in tree
PURPOSE: To check whethor or not a piece of data exists in the tree
*/
template <typename T>
bool BST<T>::isExists(T searchKey)
{
	Node<T>* temp = mRootNode;
	bool found = false;

	while (temp != NULL && !found)
	{
		if (temp->mData == searchKey)
		{
			found = true;
		}
		else if (temp->mData > searchKey)
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
PRE: None
POST: Result of recursive function integer returned
PURPOSE: To call the recursive leaf count function which determines total number of leaves on the tree
*/
template <typename T>
int BST<T>::leavesCount()
{
	int numLeaves = 0;
	recursiveLeaves(mRootNode, numLeaves);
	return numLeaves;
}

/*
PRE: Node to delete provided
POST: Node deleted if found
PURPOSE: To delete a node in the tree based on a given node data 
*/
template <typename T>
void BST<T>::makeDeletion(Node<T> *&node)
{
	Node<T> *attachPoint, *nodeToDelete;
	nodeToDelete = node;

	if (node->mRight == NULL)
	{
		node = node->mLeft;
	}
	else if (node->mLeft == NULL)
	{
		node = node->mRight;
	}
	else
	{
		attachPoint = node->mRight;
		while (attachPoint->mLeft != NULL)
		{
			attachPoint = attachPoint->mLeft;
		}
		attachPoint->mLeft = node->mLeft;
		node = node->mRight;
	}
	delete nodeToDelete;
}

/*
PRE: None
POST: Result of recursive function variable returned
PURPOSE: To call the recursive node count function which determines total number of tree nodes
*/
template <typename T>
int BST<T>::nodesCount()
{
	int numNodes = 1;
	recursiveNodes(mRootNode, numNodes);
	return numNodes;
}

/*
PRE: None
POST: If node exists then recursive path finding function called which outputs path information
PURPOSE: To determine if node exists then call the recursive path function if it does
*/
template <typename T>
void BST<T>::printPath(T nodeToFind)
{
	if (isExists(nodeToFind))
	{
		recursivePath(mRootNode, nodeToFind);
	}
	else
	{
		cout << "Node does not exist..." << endl;
	}
}

/*
PRE: Called from nodes count function
POST: Updates number of nodes as it counts which is used in non recursive function
PURPOSE: To count all nodes in the tree
*/
template <typename T>
void BST<T>::recursiveNodes(Node<T>* node, int &numNodes)
{
	//Checks if current node is null
	if (node == NULL)
	{
		return;
	}
	//If left node has data then recurse and count
	if (node->mLeft != NULL)
	{
		numNodes++;
		recursiveNodes(node->mLeft, numNodes);
	}
	//If right node has data then recurse and count
	if (node->mRight != NULL)
	{
		numNodes++;
		recursiveNodes(node->mRight, numNodes);
	}
}

/*
PRE: Called from leaves count function
POST: Updates number of leaves as it counts which is used in non recursive function
PURPOSE: To count all leaves in the tree
*/
template <typename T>
void BST<T>::recursiveLeaves(Node<T>* node, int &numLeaves)
{
	if (node == NULL)
	{
		return;
	}
	if (node->mLeft == NULL && node->mRight == NULL)
	{
		numLeaves++;
		return;
	}
	else
	{
		recursiveLeaves(node->mLeft, numLeaves);
		recursiveLeaves(node->mRight, numLeaves);
	}
}

/*
PRE: Called from print path function
POST: If found prints the path from the root to the node
PURPOSE: To locate and print the path for a given node to find
*/
template <typename T>
bool BST<T>::recursivePath(Node<T>* root, T& findNode)
{
	//Return if node is null
	if (root == NULL)
	{
		return false;
	}
	//Print out the current node if equal to search key or next recursive node
	if (root->mData == findNode || recursivePath(root->mLeft, findNode) || recursivePath(root->mRight, findNode))
	{
		cout << root->mData << "<-";
		return true;
	}
	return false;
}

/*
PRE: Called from get height function
POST: Returns the calculated height to non recursive function
PURPOSE: To find the height of the tree by comparing the total length of the 2 sides
*/
template <typename T>
int BST<T>::recursiveHeight(Node<T>* node)
{
	//Checks if passed node is NULL
	if (node == NULL) 
	{
		return -1;
	}

	//Recurses through left nodes
	int leftHeight = recursiveHeight(node->mLeft);
	//Recurses through right nodes
	int rightHeight = recursiveHeight(node->mRight);

	//If the heigh of the right height is larger than the left then return right
	if (rightHeight > leftHeight) 
	{
		return rightHeight + 1;
	}
	//Otherwise return left
	else 
	{
		return leftHeight + 1;
	}
}

/*
PRE: Called normal dfs function
POST: If node is found path is printed and true is returned otherwise false
PURPOSE: To find a node and print its path
*/
template <typename T>
bool BST<T>::recursiveDFS(Node<T>* node, T searchKey)
{
	//Checks if node is null
	if (node == NULL)
	{
		return false;
	}
	//Checks if current node is equal to search key
	if (node->mData == searchKey)
	{
		cout << "DFS: Node found" << endl;
		cout << "Path to node " << searchKey << ": ";
		printPath(searchKey);
		return true;
	}
	else
	{
		return (recursiveDFS(node->mLeft, searchKey) || recursiveDFS(node->mRight, searchKey));
	}
}

/*
PRE: Search key provided
POST: Remove function called with root node as parameter
PURPOSE: To allow remove to be used without requiring root node as a parameter
*/
template <typename T>
void BST<T>::remove(T searchKey)
{
	remove(mRootNode, searchKey);
}

template <typename T>
void BST<T>::remove(Node<T>*& node, const T& searchKey)
{
}

/*
PRE: None
POST: Display in order function called with root node as a parameter
PURPOSE: To call the recursive display in order function
*/
template <typename T>
void BST<T>::showInOrder()
{
	displayInOrder(mRootNode);
}

/*
PRE: None
POST: Display pre order function called with root node as a parameter
PURPOSE: To call the recursive display pre order function
*/
template <typename T>
void BST<T>::showPreOrder()
{
	displayPreOrder(mRootNode); 
}

/*
PRE: None
POST: Display post order function called with root node as a parameter
PURPOSE: To call the recursive display post order function
*/
template <typename T>
void BST<T>::showPostOrder()
{
	displayPostOrder(mRootNode);
}

/*
PRE: None
POST: Display tree function called with root node to start and 0 as a tab amount
PURPOSE: To call the recursive display tree function
*/
template <typename T>
void BST<T>::showTree()
{
	displayTree(mRootNode, 0);
}

#endif