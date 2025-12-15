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


    return 0;
} // end of main()
// =============================================================================