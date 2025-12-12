#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "Menu.h"


// Constants
const int LINE_WIDTH = 79;

// Application setup
vector<Menu> setupMenus();

// User Input
void pressEnterToContinue();

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

void clearScreen();

#endif