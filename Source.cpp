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
    int indexSelected{};
    int startingIndex{};
    int optionsOverride{};
    
    // Resources
    vector<Resource*> resourceSearchResults;
    Resource* selectedResource = nullptr;

    // Reservations
    vector<Reservation*> reservationSearchResults;
    Reservation* selectedReservation = nullptr;
    Reservation backupReservation{};

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
                                        break;
                                    
                                    case 4: // Filter By Resource Type
                                        selection = resourceTypeMenu.displayMenu();

                                        if (selection != 0)
                                        {
                                            resourceSearchResults = reservationSystem.filterResourceType(ResourceType(selection - 1));
                                        }
                                        else
                                        {
                                            break;
                                        }

                                        selection = 4;

                                        break;
                                    
                                    default:
                                        break;
                                    }

                                    // Verify that something was returned.
                                    if (selection == 2 && selectedResource == nullptr)
                                    {
                                        cout << "No results found." << endl;
                                        pressEnterToContinue();
                                        break;
                                    }
                                    if (selection == 3 || selection == 4)
                                    {
                                        if (resourceSearchResults.size() > 0)
                                        {
                                            displayResources(resourceSearchResults);
                                            selectedResource = resourceSearchResults[userSelection(resourceSearchResults)];
                                        }
                                        else
                                        {
                                            cout << "No results found." << endl;
                                            pressEnterToContinue();
                                            break;
                                        }
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
                                                    displayTitle("TIME SELECTION");

                                                    // Get date
                                                    selectedDateTime.date = getDate();

                                                    // Get availability
                                                    availableTimeSlots = reservationSystem.checkAvailability(selectedResource, selectedDateTime.date);
                                                    
                                                    // Verify time slots are available
                                                    if (availableTimeSlots.size() == 0)
                                                    {
                                                        cout << selectedResource->getTitle() << " is fully booked on "
                                                             << selectedDateTime.date << ".\n";
                                                        pressEnterToContinue();
                                                        break;
                                                    }

                                                    // Display Start Time Slots
                                                    displayStartTimes(availableTimeSlots);
                                                    indexSelected = userSelection(availableTimeSlots);

                                                    // Return to previous page if user enters 0
                                                    if (indexSelected == -1)
                                                    {
                                                        break;
                                                    }
                                                    selectedDateTime.startHour = availableTimeSlots[indexSelected];
                                                    
                                                    // Save index for use in end time selection
                                                    startingIndex = indexSelected;
                                                    
                                                    // Display End Time Slots
                                                    optionsOverride = displayEndTimes(availableTimeSlots, indexSelected);
                                                    indexSelected = userSelection(availableTimeSlots, optionsOverride);

                                                    // Return to previous page if user enters 0
                                                    if (indexSelected == -1)
                                                    {
                                                        break;
                                                    }
                                                    selectedDateTime.endHour = availableTimeSlots[indexSelected + startingIndex] + 1;

                                                    // Create reservation
                                                    reservationSystem.createReservation(selectedResource, selectedDateTime, clientDetails);

                                                    // Print success message
                                                    printLine();
                                                    cout << "Reservation made successfully." << endl;
                                                    pressEnterToContinue();
                                                    break;
                                                
                                                default:
                                                    break;
                                                }

                                                clearScreen();
                                                selectedResource->print();
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

                                // Verify that something was returned.
                                if (reservationSearchResults.size() != 0)
                                {
                                    displayReservations(reservationSearchResults);
                                    indexSelected = userSelection(reservationSearchResults);
                                    
                                    // Return to previous page if user enters 0
                                    if (indexSelected == -1)
                                    {
                                        break;
                                    }
                                    selectedReservation = reservationSearchResults[indexSelected];
                                }
                                else
                                {
                                    cout << "No reservations made." << endl;
                                    pressEnterToContinue();
                                    break;
                                }
                                
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

                                        // Get current availability
                                        selectedResource = selectedReservation->getResource();
                                        availableTimeSlots = reservationSystem.checkAvailability(selectedResource, selectedDateTime.date);
                                        
                                        // Verify time slots are available
                                        if (availableTimeSlots.size() == 0)
                                        {
                                            cout << "Cannot change time." << endl
                                                 << selectedResource->getTitle() << " is fully booked on "
                                                 << selectedDateTime.date << ".\n";
                                            pressEnterToContinue();
                                            break;
                                        }

                                        backupReservation = *selectedReservation;

                                        // Remove current reservation
                                        reservationSystem.cancelReservation(selectedReservation);

                                        // Get new availability
                                        availableTimeSlots = reservationSystem.checkAvailability(selectedResource, selectedDateTime.date);

                                        // Display Start Time Slots
                                        displayStartTimes(availableTimeSlots);
                                        indexSelected = userSelection(availableTimeSlots);

                                        // Return to previous page if user enters 0
                                        if (indexSelected == -1)
                                        {
                                            // Recreate previous reservation from backup
                                            reservationSystem.createReservation(backupReservation.getResource(),
                                                                                backupReservation.getTimeSlot(),
                                                                                backupReservation.getUser());
                                            break;
                                        }
                                        selectedDateTime.startHour = availableTimeSlots[indexSelected];
                                        
                                        // Save index for use in end time selection
                                        startingIndex = indexSelected;
                                        
                                        // Display End Time Slots
                                        optionsOverride = displayEndTimes(availableTimeSlots, indexSelected);
                                        indexSelected = userSelection(availableTimeSlots, optionsOverride);

                                        // Return to previous page if user enters 0
                                        if (indexSelected == -1)
                                        {
                                            // Recreate previous reservation from backup
                                            reservationSystem.createReservation(backupReservation.getResource(),
                                                                                backupReservation.getTimeSlot(),
                                                                                backupReservation.getUser());
                                            break;
                                        }
                                        selectedDateTime.endHour = availableTimeSlots[indexSelected + startingIndex] + 1;

                                        // Put backup back into selectedResource for printing and futher modifying.
                                        selectedReservation = &backupReservation;

                                        reservationSystem.modifyReservation(selectedReservation, selectedDateTime);
                                        break;
                                    
                                    case 2: // Cancel Reservation
                                        reservationSystem.cancelReservation(selectedReservation);
                                        break;
                                    
                                    default:
                                        break;
                                    }

                                    clearScreen();
                                    // Print new data
                                    if (selection == 1)
                                    {
                                        if (indexSelected == -1)
                                        {
                                            displayReservation(&backupReservation);
                                        }
                                        else
                                        {
                                            displayReservation(selectedReservation);
                                        }
                                    }
                                    // Exit out of viewReservationsMenu
                                    else if (selection == 2)
                                    {
                                        break;
                                    }
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
                                        break;
                                    
                                    case 4: // Filter By Resource Type
                                        selection = resourceTypeMenu.displayMenu();

                                        if (selection != 0)
                                        {
                                            resourceSearchResults = reservationSystem.filterResourceType(ResourceType(selection - 1));
                                        }
                                        else
                                        {
                                            break;
                                        }

                                        selection = 4;

                                        break;
                                    
                                    default:
                                        break;
                                    }

                                    // Verify that something was returned.
                                    if (selection == 2 && selectedResource == nullptr)
                                    {
                                        cout << "No results found." << endl;
                                        pressEnterToContinue();
                                        break;
                                    }
                                    if (selection == 3 || selection == 4)
                                    {
                                        if (resourceSearchResults.size() > 0)
                                        {
                                            displayResources(resourceSearchResults);
                                            selectedResource = resourceSearchResults[userSelection(resourceSearchResults)];
                                        }
                                        else
                                        {
                                            cout << "No results found." << endl;
                                            pressEnterToContinue();
                                            break;
                                        }
                                    }

                                    // MARK: Resource Creation
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
                                                // Print new data
                                                if (selection == 1)
                                                {
                                                    selectedResource->print();
                                                }
                                                // Exit out of modifyResourceMenu
                                                else if (selection == 2)
                                                {
                                                    break;
                                                }
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