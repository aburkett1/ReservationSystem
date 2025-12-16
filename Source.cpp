#include "Utilities.h"
#include "ReservationSystem.h"

// ==== main ===================================================================
//
// =============================================================================
int main()
{
    // =============================================================================
    // MARK: Variables
    // =============================================================================
    // System
    ReservationSystem reservationSystem = ReservationSystem();
    User* clientDetails = nullptr;
    int selection{};
    
    // Resources
    vector<Resource*> resourceSearchResults;
    Resource* selectedResource = nullptr;

    // Reservations
    vector<Reservation*> reservationSearchResults;
    Reservation* selectedReservation = nullptr;

    // Time Slots
    vector<int> availableTimeSlots{};
    DateAndTimeRange selectedDateTime{};
    

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
    Menu resourceTypeMenu = menus[8];
    
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
                            Search by ID
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
                        Save System
                    if (Admin)
                        Add Resource
                        View Resources
                            List all
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
                        Save System
                Register
            New System
            
    */

    selection = mainMenu.displayMenu();

    while (selection != 0)
    {
        // Reset Reservation System
        reservationSystem = ReservationSystem();

        clearScreen();
        switch (selection)
        {
        case 1: // MARK: Load System Details
            // Import file
            reservationSystem.importFromFiles();
            break;
        
        default:
            break;
        }

        clearScreen();
        selection = loginMenu.displayMenu();

        while (selection != 0)
        {
            clearScreen();
            switch (selection)
            {
            case 1: // MARK: Login
                // Get client details
                displayTitle("LOGIN");
                try
                {
                    clientDetails = reservationSystem.login();
                }
                catch(const exception& e)
                {
                    cout << e.what() << '\n';
                    pressEnterToContinue();
                }
                                
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
                            clearScreen();
                            switch (selection)
                            {
                            case 1: // View Resources
                                clearScreen();
                                selection = viewResourcesMenu.displayMenu();

                                while (selection != 0)
                                {
                                    clearScreen();
                                    switch (selection)
                                    {
                                    case 1: // List all
                                        reservationSystem.listResources();
                                        pressEnterToContinue();
                                        break;
                                    
                                    // MARK: Reservation Filtering
                                    case 2: // Search by ID
                                        selectedResource = reservationSystem.searchID(getResourceId());
                                        break;
                                    
                                    case 3: // Search by Name
                                        resourceSearchResults = reservationSystem.searchTitle(getResourceName());
                                        displayResources(resourceSearchResults);
                                        selectedResource = resourceSearchResults[userSelection(resourceSearchResults)];
                                        break;
                                    
                                    case 4: // Filter By Resource Type
                                        selection = resourceTypeMenu.displayMenu();

                                        if (selection != 0)
                                        {
                                            resourceSearchResults = reservationSystem.filterResourceType(ResourceType(selection));
                                            displayResources(resourceSearchResults);
                                            selectedResource = resourceSearchResults[userSelection(resourceSearchResults)];
                                        }
                                        break;
                                    
                                    default:
                                        break;
                                    }

                                    // MARK: Reservation Creation
                                    clearScreen();
                                    switch (selection)
                                    {
                                    case 2: // Search by ID
                                    case 3: // Search by Name
                                    case 4: // Filter By Resource Type
                                        if (selectedResource)
                                        {
                                            // Print Resource
                                            selectedResource->print();

                                            selection = reservationCreationMenu.displayMenu();
                                            while(selection != 0)
                                            {
                                                clearScreen();
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
                                                    selectedDateTime.endHour = availableTimeSlots[userSelection(availableTimeSlots)] + 1;

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
                                    
                                    default:
                                        break;
                                    }

                                    clearScreen();
                                    selection = viewResourcesMenu.displayMenu();
                                }
                                break;
                            
                            case 2: // MARK: View Reservations
                                reservationSearchResults = reservationSystem.viewReservation(clientDetails);
                                displayReservations(reservationSearchResults);
                                selectedReservation = reservationSearchResults[userSelection(reservationSearchResults)];
                                
                                clearScreen();
                                displayReservation(selectedReservation);

                                selection = viewReservationsMenu.displayMenu();
                                while (selection != 0)
                                {
                                    clearScreen();
                                    switch (selection)
                                    {
                                    case 1: // Modify Reservation
                                        // Get date
                                        selectedDateTime.date = selectedReservation->getTimeSlot().date;

                                        // Get availability
                                        availableTimeSlots = reservationSystem.checkAvailability(selectedResource, selectedDateTime.date);

                                        // Display Start Time Slots
                                        displayStartTimes(availableTimeSlots);
                                        selectedDateTime.startHour = availableTimeSlots[userSelection(availableTimeSlots)];

                                        // Display End Time Slots
                                        displayEndTimes(availableTimeSlots, selectedDateTime.startHour);
                                        selectedDateTime.endHour = availableTimeSlots[userSelection(availableTimeSlots)];

                                        reservationSystem.modifyReservation(selectedReservation, selectedDateTime);
                                        break;
                                    
                                    case 2: // Cancel Reservation
                                        reservationSystem.cancelReservation(selectedReservation);
                                        break;
                                    
                                    default:
                                        break;
                                    }

                                    clearScreen();
                                    selection = viewReservationsMenu.displayMenu();
                                }
                                break;
                            
                            case 3: // Save System
                                try
                                {
                                    reservationSystem.exportToFiles();
                                    cout << "System Saved Successfully" << endl;
                                }
                                catch(const exception& e)
                                {
                                    cerr << e.what() << '\n';
                                }
                                pressEnterToContinue();

                                break;
                            
                            default:
                                break;
                            }

                            clearScreen();
                            selection = studentMenu.displayMenu();
                        }
                        break;

                    case ADMIN: // MARK: Admin
                        selection = adminMenu.displayMenu();
                        while (selection != 0)
                        {
                            clearScreen();
                            switch (selection)
                            {
                            case 1: // Add Resource
                                selection = resourceTypeMenu.displayMenu();
                                if (selection != 0)
                                {
                                    selectedResource = createResource(ResourceType(selection-1));
                                    reservationSystem.addResource(selectedResource);
                                }
                                
                                break;
                            
                            case 2: // View Resources
                                clearScreen();
                                selection = viewResourcesMenu.displayMenu();

                                while (selection != 0)
                                {
                                    clearScreen();
                                    switch (selection)
                                    {
                                    case 1: // List all
                                        reservationSystem.listResources();
                                        pressEnterToContinue();
                                        break;
                                    
                                    // MARK: Resource Filtering
                                    case 2: // Search by ID
                                        selectedResource = reservationSystem.searchID(getResourceId());
                                        break;
                                    
                                    case 3: // Search by Name
                                        resourceSearchResults = reservationSystem.searchTitle(getResourceName());
                                        displayResources(resourceSearchResults);
                                        selectedResource = resourceSearchResults[userSelection(resourceSearchResults)];
                                        break;
                                    
                                    case 4: // Filter By Resource Type
                                        selection = resourceTypeMenu.displayMenu();

                                        if (selection != 0)
                                        {
                                            resourceSearchResults = reservationSystem.filterResourceType(ResourceType(selection));
                                            displayResources(resourceSearchResults);
                                            selectedResource = resourceSearchResults[userSelection(resourceSearchResults)];
                                        }
                                        break;
                                    
                                    default:
                                        break;
                                    }

                                    // MARK: Reservation Creation
                                    clearScreen();
                                    switch (selection)
                                    {
                                    case 2: // Search by ID
                                    case 3: // Search by Name
                                    case 4: // Filter By Resource Type
                                        if (selectedResource)
                                        {
                                            // Print Resource
                                            selectedResource->print();

                                            selection = modifyResourceMenu.displayMenu();
                                            while(selection != 0)
                                            {
                                                clearScreen();
                                                switch (selection)
                                                {
                                                case 1: // Edit Resource
                                                    reservationSystem.editResource(selectedResource);
                                                    break;
                                                
                                                case 2: // Remove Resource
                                                    reservationSystem.removeResource(selectedResource);
                                                    break;
                                                
                                                default:
                                                    break;
                                                }

                                                clearScreen();
                                                selectedResource->print();
                                                selection = modifyResourceMenu.displayMenu();
                                            }
                                        }
                                        break;
                                    
                                    default:
                                        break;
                                    }

                                    clearScreen();
                                    selection = viewResourcesMenu.displayMenu();
                                }
                                break;
                            
                            case 3: // Save System
                                try
                                {
                                    reservationSystem.exportToFiles();
                                    cout << "System Saved Successfully" << endl;
                                }
                                catch(const exception& e)
                                {
                                    cerr << e.what() << '\n';
                                }
                                pressEnterToContinue();
                                
                                break;
                            
                            default:
                                break;
                            }

                            clearScreen();
                            selection = adminMenu.displayMenu();
                        }
                        break;
                    
                    default:
                        break;
                    }
                }
                break;

            case 2: // Register
                clearScreen();
                reservationSystem.registerUser();
                pressEnterToContinue();
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