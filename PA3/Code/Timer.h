/*
Author: Anthony Blake as used by Wes Beard
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

#ifndef Timer
#define Timer

#include <iostream>
#include <windows.h>

class TimerSystem
{
private:
	LARGE_INTEGER start, finish, freq;  //For frequency and high speed timers

public:
	TimerSystem();

	double getTime();  //gets current time since top of frame
	void   startClock();  //Starts the frame counter
};

#endif