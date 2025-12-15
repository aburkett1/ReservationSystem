#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "Menu.h"
#include "Reservation.h"
#include "Resource.h"
#include "MusicRoom.h"
#include "StudyRoom.h"

// Constants
const int LINE_WIDTH = 79;

// Application setup
vector<Menu> setupMenus();

// User Input
void pressEnterToContinue();
int getResourceId();
string getResourceName();
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
void displayResources(vector<Resource*>& results);
void displayReservations(vector<Reservation*>& results);
void displayReservation(Reservation*& selectedReservation);

void clearScreen();

// Utility
string timeConverter(int time24hr);


#endif