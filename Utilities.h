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
TimeRange getAvailability();
int getCapacity();
string getLocation();
bool getSoundproof();
int getWhiteboardAmount();
string getDate();
Resource* createResource(ResourceType type);

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
int displayEndTimes(vector<int> timeSlots, int startTime);
void displayReservations(vector<Reservation*>& results);
void displayReservation(Reservation*& selectedReservation);
void displayTimeSlot(DateAndTimeRange timeSlot);
void displayResources(vector<Resource*>& results);

void clearScreen();

// Utility
template <typename T>
int userSelection(vector<T>& results, int selectionOverride = 0)
{
    // Variables
    int selection{};
    bool valid = false;
    int endRange = (selectionOverride == 0 ? results.size() : selectionOverride);

    while (!valid) {
        cout << "Select option (1-" << endRange << "), enter 0 to cancel: ";

        // Check for numerical input
        if (!(cin >> selection)) {
            cin.clear();
            cin.ignore(10000, '\n');
            printLine();
            cout << "Invalid input.\nPlease select option (1-" << endRange << "), enter 0 to cancel.\n";
            printLine();
        } else {
            cin.ignore(10000, '\n');

            // Allows for user to return to previous page
            if (selection == 0) return -1;

            if (selection < 1 || selection > endRange) {
                printLine();
                cout << "Invalid input.\nPlease select option (1-" << endRange << "), enter 0 to cancel.\n";
                printLine();
            } else {
                valid = true;
            }
        }
    }

    // Return index
    return selection - 1;
}


#endif