#include "Utilities.h"

// =============================================================================
// MARK: Application Setup
// =============================================================================

vector<Menu> setupMenus()
{
    // Variables
    vector<Menu> menus;

    /*
        MENU HIERARCHY
    
        
    */
    
    

    // Return vector of all Menus.
    return menus;
}


// =============================================================================
// MARK: User Input
// =============================================================================

void pressEnterToContinue() {
    cout << "Press [ENTER] to continue...";
    cin.ignore(10000, '\n');
}


// =============================================================================
// MARK: Output
// =============================================================================

void printLine(int lineWidth)
{
    cout << setfill('-');
    cout << setw(lineWidth) << '-' << endl;
    cout << setfill(' ');
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}