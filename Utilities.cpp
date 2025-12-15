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

        Main Menu
            Load System Details
                Login
                    if (Student)
                        View Resources
                            List all
                                Select Resource
                                    Create Reservation
                            Search by ID
                                Select Resource
                                    Create Reservation
                            Search by Name
                                Select Resource
                                    Create Reservation
                            Filter By Resource Type
                                Select Resource
                                    Create Reservation
                        View Reservations
                            Modify Reservation
                            Cancel Reservation
                        Save System Details
                    if (Admin)
                        Add Resource
                        View Resources
                            List all
                                Select Resource
                                    Edit Resource
                                    Remove Resource
                            Search by ID
                                Select Resource
                                    Edit Resource
                                    Remove Resource
                            Search by Name
                                Select Resource
                                    Edit Resource
                                    Remove Resource
                            Filter By Resource Type
                                Select Resource
                                    Edit Resource
                                    Remove Resource
                        Save System Details
                Register
            New System
        
    */
    
    // Main Menu
    vector<string> mainMenuOptions = {
        "Load System Details",
        "New System"
    };
    Menu mainMenu = Menu("MAIN MENU", mainMenuOptions);
    menus.push_back(mainMenu);

    // Login Menu
    vector<string> loginMenuOptions = {
        "Login",
        "Register"
    };
    Menu loginMenu = Menu("LOGIN MENU", loginMenuOptions);
    menus.push_back(loginMenu);

    // Student Menu
    vector<string> studentMenuOptions = {
        "View Resources",
        "View Reservations",
        "Save System Details"
    };
    Menu studentMenu = Menu("RESOURCE SYSTEM", studentMenuOptions);
    menus.push_back(studentMenu);

    // Admin Menu
    vector<string> adminMenuOptions = {
        "Add Resource",
        "View Resources",
        "Save System Details"
    };
    Menu adminMenu = Menu("RESOURCE SYSTEM", adminMenuOptions);
    menus.push_back(adminMenu);

    // View Resources Menu
    vector<string> viewResourcesMenuOptions = {
        "List all",
        "Search by ID",
        "Search by Name",
        "Filter By Resource Type"
    };
    Menu viewResourcesMenu = Menu("RESOURCES", viewResourcesMenuOptions);
    menus.push_back(viewResourcesMenu);

    // Reservation Creation Menu
    vector<string> reservationCreationMenuOptions = {
        "Create Reservation"
    };
    Menu reservationCreationMenu = Menu("RESOURCE DETAILS", reservationCreationMenuOptions);
    menus.push_back(reservationCreationMenu);

    // View Reservations Menu
    vector<string> viewReservationsMenuOptions = {
        "Modify Reservation",
        "Cancel Reservation"
    };
    Menu viewReservationsMenu = Menu("RESERVATIONS", viewReservationsMenuOptions);
    menus.push_back(viewReservationsMenu);

    // Modify Resource Menu
    vector<string> modifyResourceMenuOptions = {
        "Edit Resource",
        "Remove Resource"
    };
    Menu modifyResourceMenu = Menu("RESOURCE DETAILS", modifyResourceMenuOptions);
    menus.push_back(modifyResourceMenu);
    

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