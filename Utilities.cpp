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

    // Resource Type Menu
    vector<string> resourceTypeMenuOptions = {
        "Music Room",
        "Study Room"
    };
    Menu resourceTypeMenu = Menu("RESOURCE TYPE", resourceTypeMenuOptions);
    menus.push_back(resourceTypeMenu);
    

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

int getResourceId()
{
    // Variables
    int id{};

    // Get id from user
    cout << "ID: ";
    cin >> id;
    cin.ignore(10000, '\n');

    return id;
}

string getResourceName()
{
    // Variables
    string name{};

    // Get name from user
    cout << "Name: ";
    getline(cin, name);

    return name;
}

TimeRange getAvailability()
{
    // Variables
    int startTime{};
    int endTime{};

    // Get opening time from user
    cout << "Opening Time [24hr]: ";
    cin >> startTime;
    cin.ignore(10000, '\n');

    // Get closing time from user
    cout << "Closing Time [24hr]: ";
    cin >> endTime;
    cin.ignore(10000, '\n');

    return TimeRange(startTime, endTime);
}

int getCapacity()
{
    // Variables
    int capacity{};

    // Get capacity from user
    cout << "Capacity: ";
    cin >> capacity;
    cin.ignore(10000, '\n');

    return capacity;
}

string getLocation()
{
    // Variables
    string location{};

    // Get location from user
    cout << "Location: ";
    getline(cin, location);

    return location;
}

bool getSoundproof()
{
    // Variables
    char isSoundproof{};

    // Get isSoundproof from user
    cout << "Is this location soundproof? [Y/N]: ";
    cin >> isSoundproof;
    cin.ignore(10000, '\n');

    return toupper(isSoundproof) == 'Y';
}

int getWhiteboardAmount()
{
    // Variables
    int whiteboardAmount{};

    // Get whiteboardAmount from user
    cout << "Whiteboard Amount: ";
    cin >> whiteboardAmount;
    cin.ignore(10000, '\n');

    return whiteboardAmount;
}

string getDate()
{
    // Variables
    string date{};

    // Get date from user
    cout << "Date [MM/DD/YYYY]: ";
    getline(cin, date);

    return date;
}

Resource* createResource(ResourceType type)
{
    // Variables
    string title{};
    TimeRange availability{};
    int capacity;
    string location;
    bool soundproof;
    int whiteboardAmount;

    title = getResourceName();
    availability = getAvailability();
    capacity = getCapacity();
    location = getLocation();
    
    switch (type)
    {
    case MUSIC_ROOM:
        soundproof = getSoundproof();
        return new MusicRoom(title, availability, capacity, location, soundproof);
    
    case STUDY_ROOM:
        whiteboardAmount = getWhiteboardAmount();
        return new StudyRoom(title, availability, capacity, location, whiteboardAmount);
    
    default:
        return nullptr;
    }
    

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

void displayStartTimes(vector<int> timeSlots)
{
    displayTitle("START TIMES");
    
    for (int i = 0; i < timeSlots.size(); i++)
    {
        displayTitle(i+1);
        cout << TimeRange::converter24to12(timeSlots[i]);
    }

}

void displayEndTimes(vector<int> timeSlots, int startTime)
{
    displayTitle("END TIMES");
    
    for (int i = timeSlots[startTime]; i != -1; i++)
    {
        displayTitle(i+1);
        cout << TimeRange::converter24to12(timeSlots[i] + 1);
    }
}

void displayReservations(vector<Reservation*>& results)
{
    displayTitle("SELECT RESERVATION");
    
    for (int i = 0; i < results.size(); i++)
    {
        displayTitle(i+1);
        cout << results[i]->getResource()->getTitle() << endl;
        displayTimeSlot(results[i]->getTimeSlot());
    }
}

void displayReservation(Reservation*& selectedReservation)
{
    //dynamically cast resource as a new musicRoom pointer
	MusicRoom* musicRoom = dynamic_cast<MusicRoom*>(selectedReservation->getResource());

    //dynamically cast resource as a new studyRoom pointer
	StudyRoom* studyRoom = dynamic_cast<StudyRoom*>(selectedReservation->getResource());
    
    // Print Resource
    if (musicRoom)
    {
        musicRoom->print();
    }
    else if (studyRoom)
    {
        studyRoom->print();
    }

    cout << "Reserved on ";
    displayTimeSlot(selectedReservation->getTimeSlot());
}

void displayTimeSlot(DateAndTimeRange timeSlot)
{
    cout << timeSlot.date << " from "
         << TimeRange::converter24to12(timeSlot.startHour) << "-"
         << TimeRange::converter24to12(timeSlot.endHour)
         << endl;
}

void displayResources(vector<Resource*>& results)
{
    displayTitle("SELECT RESOURCE");
    
    for (int i = 0; i < results.size(); i++)
    {
        displayTitle(i+1);
        results[i]->print();
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}