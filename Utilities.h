#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "Menu.h"
#include "Resource.h"


// Constants
const int LINE_WIDTH = 79;

// Application setup
vector<Menu> setupMenus();

// User Input
void pressEnterToContinue();
int getResourceId();
string getFileName();
string getDate();

template <typename T>
int userSelection(vector<T>& results);

// Output
void printLine(int lineWidth = LINE_WIDTH);

template <typename T>
void displayTitle(T title)
{
    // Display Title
    printLine();
	cout << "   " << title << endl;
	printLine();
}

void displayStartTimes(vector<int> timeSlots);
void displayEndTimes(vector<int> timeSlots, int startTime);

void clearScreen();

// Utility
string timeConverter(int time24hr);


#endif