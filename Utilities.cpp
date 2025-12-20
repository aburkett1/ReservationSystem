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
    int id;
    string idAsString{};
    bool valid = false;

    while (!valid)
    {
        // Get id from user
        cout << "ID: ";
        getline(cin, idAsString);

        try
        {
            // Convert string to int
            id = stoi(idAsString);

            // If successful
            valid = true;
        }
        catch(const exception& _)
        {
            printLine();
            cout << "ID must be an integer." << endl;
            printLine();
        }
        
    }

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
    string startTimeAsString{};
    string endTimeAsString{};
    bool valid = false;

    // Get Starting Time
    while (!valid)
    {
        // Get id from user
        cout << "Opening Time [24hr]: ";
        getline(cin, startTimeAsString);
        
        try
        {
            // Convert string to int
            startTime = stoi(startTimeAsString);

            // If successful
            valid = startTime >= 0 && startTime <= 23;

            if (!valid)
            {
                printLine();
                cout << "Starting time must be between 0 and 23." << endl;
                printLine();
            }
        }
        catch(const exception& _)
        {
            printLine();
            cout << "Starting time must be an integer." << endl;
            printLine();
        }       
    }

    valid = false;

    // Get Ending Time
    while (!valid)
    {
        // Get id from user
        cout << "Closing Time [24hr]: ";
        getline(cin, endTimeAsString);
        
        try
        {
            // Convert string to int
            endTime = stoi(endTimeAsString);

            // If successful
            valid = endTime >= 1 && endTime <= 24 && endTime > startTime;

            if (!valid)
            {
                printLine();
                cout << "Ending time must be between 1 and 24, and must also be later than opening time." << endl;
                printLine();
            }
        }
        catch(const exception& _)
        {
            printLine();
            cout << "Ending time must be an integer." << endl;
            printLine();
        }       
    }

    return TimeRange(startTime, endTime);
}

int getCapacity()
{
    // Variables
    int capacity;
    string capacityAsString{};
    bool valid = false;

    while (!valid)
    {
        // Get id from user
        cout << "Capacity: ";
        getline(cin, capacityAsString);

        try
        {
            // Convert string to int
            capacity = stoi(capacityAsString);

            // If successful
            valid = capacity > 0;

            if (!valid)
            {
                printLine();
                cout << "Capacity must be greater than 0." << endl;
                printLine();
            }
        }
        catch(const exception& _)
        {
            printLine();
            cout << "Capacity must be an integer." << endl;
            printLine();
        }
        
    }

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
    bool valid = false;
    
    while (!valid)
    {
        // Get isSoundproof from user
        cout << "Is this location soundproof? [Y/N]: ";
        cin >> isSoundproof;
        cin.ignore(10000, '\n');

        // Uppercase isSoundproof
        isSoundproof = toupper(isSoundproof);

        // Check input
        valid = isSoundproof == 'Y' || isSoundproof == 'N';

        if (!valid)
        {
            cout << "Must enter Y/N." << endl;
        }
    }

    return isSoundproof == 'Y';
}

int getWhiteboardAmount()
{
    // Variables
    int whiteboardAmount;
    string whiteboardAmountAsString{};
    bool valid = false;

    while (!valid)
    {
        // Get id from user
        cout << "Whiteboard Amount: ";
        getline(cin, whiteboardAmountAsString);

        try
        {
            // Convert string to int
            whiteboardAmount = stoi(whiteboardAmountAsString);

            // If successful
            valid = true;

            if (!valid)
            {
                printLine();
                cout << "Whiteboard Amount must be positive or zero." << endl;
                printLine();
            }
        }
        catch(const exception& _)
        {
            printLine();
            cout << "Whiteboard Amount must be an integer." << endl;
            printLine();
        }
        
    }

    return whiteboardAmount;
}

string getDate()
{
    // Variables
    string date{};
    bool valid = false;
    
    do
    {
        // Get date from user
        cout << "Date [MM/DD/YYYY]: ";
        getline(cin, date);

        try
        {
            int month = stoi(date.substr(0,2));
            int day = stoi(date.substr(3,2));
            int year = stoi(date.substr(6,4));

            valid = month >= 1 && month <= 12 &&
                    day >= 1 && day <= 31 &&
                    year >= 2025 && year <= 9999 &&
                    date.substr(2,1) == "/" &&
                    date.substr(5,1) == "/";
        }
        catch(const exception& _)
        {
            valid = false;
            cout << "Date must be in the format MM/DD/YYYY." << endl;
        }
    } while (!valid);
    
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
        cout << " " << i + 1 << ": ";
        cout << TimeRange::converter24to12(timeSlots[i]) << '\n';
    }
    cout << '\n';
}

int displayEndTimes(vector<int> timeSlots, int indexStartTime)
{
    // Variable
    bool valid = true;
    int options{};

    displayTitle("END TIMES");
    
    for (int i = 0, j = indexStartTime; valid && j < timeSlots.size(); i++, j++)
    {
        cout << " " << i + 1 << ": ";
        cout << TimeRange::converter24to12(timeSlots[j] + 1) << '\n';
        
        // Count options for userSelection
        options++;

        // Check to see if the next time slot is valid.
        valid = timeSlots[j+1] - timeSlots[j] == 1;
    }
    cout << '\n';

    return options;
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

void displayReservation(Reservation* selectedReservation)
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