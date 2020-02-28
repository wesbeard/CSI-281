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

#include "Timer.h"

/*      Pre:  None
 *     Post:  The private members are initialized
 *  Purpose:  Default constructor for the TimerSystem
******************************************************************************/
TimerSystem::TimerSystem()
{
	start.QuadPart = 0;
	finish.QuadPart = 0;

	//Sets the clock frequency for the system we are running on
	QueryPerformanceFrequency(&freq);
}


/*      Pre:  The stopwatch must be initialized and started
 *     Post:  The elapse time is returned to the caller
 *  Purpose:  Gets time in seconds since the stopwatch has started
 ******************************************************************************/
double TimerSystem::getTime()
{
	QueryPerformanceCounter(&finish);  //get end cpu cycles

   // return the amount of time elapsed
	return static_cast<double>((finish.QuadPart - start.QuadPart) / static_cast<double>(freq.QuadPart));
}


/*      Pre:  The stopwatch must be initialized
 *     Post:  The start private member is reset
 *  Purpose:  To start the stopwatch
 ******************************************************************************/
void TimerSystem::startClock()
{
	//get the top of the frames CPU count
	QueryPerformanceCounter(&start);
}
