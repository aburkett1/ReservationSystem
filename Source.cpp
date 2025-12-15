#include "Menu.h"
#include "Utilities.h"
#include "ReservationSystem.h"

// ==== main ===================================================================
//
// =============================================================================
int main()
{
    // Variables
    int selection{};
    ReservationSystem reservationSystem = ReservationSystem();
    User* clientDetails = nullptr;
    Resource* selectedResource = nullptr;
    DateAndTimeRange selectedDateTime{};
    vector<int> availableTimeSlots{};
    int id{};
    string resourceName{};
    ifstream fin;
    ofstream fout;

    // =============================================================================
    // MARK: Menu Creation
    // =============================================================================

    vector<Menu> menus = setupMenus();
    Menu mainMenu = menus[0];
    Menu loginMenu = menus[1];
    Menu studentMenu = menus[2];
    Menu adminMenu = menus[3];
    Menu viewResourcesMenu = menus[4];
    Menu reservationCreationMenu = menus[5];
    Menu viewReservationsMenu = menus[6];
    Menu modifyResourceMenu = menus[7];
    
    /*
        // =========================================================================
        // MARK: MENU HIERARCHY
        // =========================================================================
    
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

    selection = mainMenu.displayMenu();

    while (selection != 0)
    {
        switch (selection)
        {
        case 1: // MARK: Load System Details
            fin.open(getFileName());
            if(fin)
                    {
                        // Reset Reservation System
                        reservationSystem = ReservationSystem();
                        
                        // Import file
                        reservationSystem.importFromFile(fin);
                        fin.close();

                        // Display success message
                        cout << endl << "Data Imported Successfully." << endl;
                        pressEnterToContinue();
                    }
                    else
                    {
                        // Display failure message
                        cout << endl << "File could not be found." << endl;
                        pressEnterToContinue();
                    }
                    break;

        case 2: // New System

            // Reset Reservation System
            reservationSystem = ReservationSystem();

            break;
        
        default:
            break;
        }

        clearScreen();
        selection = loginMenu.displayMenu();

        while (selection != 0)
        {
            switch (selection)
            {
            case 1: // MARK: Login
                // Get client details
                clientDetails = reservationSystem.login();
                
                // Verify User exists
                if (clientDetails)
                {
                    clearScreen();
                    switch (clientDetails->getType())
                    {
                    case STUDENT: // MARK: Student
                        selection = studentMenu.displayMenu();
                        while (selection != 0)
                        {
                            switch (selection)
                            {
                            case 1: // View Resources
                                selection = viewResourcesMenu.displayMenu();

                                while (selection != 0)
                                {
                                    switch (selection)
                                    {
                                    case 1: // List all
                                        reservationSystem.listResources();
                                        pressEnterToContinue();
                                        break;
                                    
                                    case 2: // Search by ID
                                        selectedResource = reservationSystem.searchID(getResourceId());
                                        clearScreen();

                                        if (selectedResource)
                                        {
                                            // Print Resource
                                            selectedResource->print();

                                            selection = reservationCreationMenu.displayMenu();
                                            while(selection != 0)
                                            {
                                                switch (selection)
                                                {
                                                case 1: // Create Reservation
                                                    // Get date
                                                    selectedDateTime.date = getDate();

                                                    // Get availability
                                                    availableTimeSlots = reservationSystem.checkAvailability(selectedResource, selectedDateTime.date);

                                                    // Display Start Time Slots
                                                    displayStartTimes(availableTimeSlots);
                                                    selectedDateTime.startHour = availableTimeSlots[userSelection(availableTimeSlots)];

                                                    // Display End Time Slots
                                                    displayEndTimes(availableTimeSlots, selectedDateTime.startHour);
                                                    selectedDateTime.endHour = availableTimeSlots[userSelection(availableTimeSlots)];

                                                    // Create reservation
                                                    reservationSystem.createReservation(selectedResource, selectedDateTime, clientDetails);
                                                    break;
                                                
                                                default:
                                                    break;
                                                }

                                                clearScreen();
                                                selection = reservationCreationMenu.displayMenu();
                                            }
                                        }

                                        break;
                                    
                                    case 3: // Search by Name
                                        /* code */
                                        break;
                                    
                                    case 4: // Filter By Resource Type
                                        /* code */
                                        break;
                                    
                                    default:
                                        break;
                                    }

                                    clearScreen();
                                    selection = viewResourcesMenu.displayMenu();
                                }
                                break;
                            
                            case 2: // View Reservations
                                /* code */
                                break;
                            
                            case 3: // Save System
                                /* code */
                                break;
                            
                            
                            default:
                                break;
                            }

                            clearScreen();
                            selection = studentMenu.displayMenu();
                        }
                        break;

                    case ADMIN: // MARK: Admin
                        /* code */
                        break;
                    
                    default:
                        break;
                    }
                }
                break;

            case 2: // Register
                reservationSystem.registerUser();
                break;
            
            default:
                break;
            }

            clearScreen();
            selection = loginMenu.displayMenu();
        }

        clearScreen();
        selection = mainMenu.displayMenu();
    }


    return 0;
} // end of main()
// =============================================================================