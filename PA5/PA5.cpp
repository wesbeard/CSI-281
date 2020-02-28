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

#include "PA5.h"
#include "bst.h"

int main()
{
	run();
	return 0;
}

//Prevents direct output in main
void run()
{
	BST<int> tree;
	int nodeToFind = 1;

	tree.insert(5);
	tree.insert(3);
	tree.insert(4);
	tree.insert(2);
	tree.insert(1);
	tree.insert(7);
	tree.insert(6);
	tree.insert(8);
	tree.insert(9);

	cout << "Tree:" << endl;
	tree.showTree();
	cout << endl;

	cout << "Total number of nodes: " << tree.nodesCount() << endl;
	cout << "Total number of leaves: " << tree.leavesCount() << endl;
	cout << "Height of tree: " << tree.getHeight() << endl << endl;

	cout << "Path to node " << nodeToFind << ": ";
	tree.printPath(nodeToFind);
	cout << endl << endl;

	cout << "Tree in order: ";
	tree.showInOrder();
	cout << endl;

	cout << "Tree post order: ";
	tree.showPostOrder();
	cout << endl;

	cout << "Tree pre order: ";
	tree.showPreOrder();
	cout << endl << endl;

	tree.dfs(9);
	cout << endl;
	tree.bfs(4);
	cout << endl;

	system("Pause");
}