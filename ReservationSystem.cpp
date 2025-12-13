#include "ReservationSystem.h"

ReservationSystem::~ReservationSystem() {
    delete localUser;
    
    for (User* user : registeredUsers)
        delete user;

    for (Resource* resource : resources)
        delete resource;

    for (Reservation* reservation : reservations)
        delete reservation;
}

void ReservationSystem::listResources() const {
    for (Resource* r : resources) {
        r->print();
        cout << endl;
    }
}

// ========================================================================
// MARK: Searches
// ========================================================================

vector<Resource*> ReservationSystem::searchTitle(string name) const
{
    // Initializing Vector
    vector<Resource*> title;

    // For every resource stored in system, if name with corresponding
    // resource is the same as user's name, then add it to title vector
    for (Resource* resource : resources)
    {
        if (resource->getTitle() == name)
        {
            title.push_back(resource);
        }
    }

    // Return all matching title resources or empty if none are
    // found
    return title;
};

Resource* ReservationSystem::searchID(int id) const
{
    // For each resource in the system, if ID with corresponding
    // resource matches user ID, then return it
    for (Resource* resource : resources)
    {
        if (resource->getID() == id)
        {
            return resource;
        }
    }

    // If no resource was found with that searched ID, then
    // return nullptr
    return nullptr;
};

void ReservationSystem::addResource(Resource* resource) {
    resources.push_back(resource);
}

void ReservationSystem::exportToFile(ofstream& fout) {
    fout << "LOCAL_USER\n";
    localUser->exportToFile(fout);

    fout << "REGISTERED_USERS\n";
    for (User* user : registeredUsers) {
        user->exportToFile(fout);
    }

    fout << "RESOURCES\n";
    for (Resource* resource : resources) {
        resource->exportToFile(fout);
    }

    fout << "RESERVATIONS\n";
    for (Reservation* reservation : reservations) {
        reservation->exportToFile(fout);
    }
}

void ReservationSystem::importFromFile(ifstream& fin) {

}






vector<Reservation*> viewReservation() const
{
    vector<Reservation*> result;

    if (localUser == nullptr) {
        cout << "No user is currently logged in." << endl;
        return result;
    }

    for (Reservation* r : reservations) {
        // Chekc my implementation of getUser()
        if (r->getUser() == localUser) {
            result.push_back(r);
        }
    }

    return result;
}






void ReservationSystem::modifyReservation(Reservation* reservation, TimeRange newTimeSlot) {
    if (reservation == nullptr) {
        cout << "Error: invalid reservation pointer." << endl;
        return;
    }

    // Get current data from the reservation
    Resource* res = reservation->getResource();
    DateAndTimeRange currentSlot = reservation->getTimeSlot();

    //new dateandtimerange, WORTH CHECKING FOR ITS congruencY
    DateAndTimeRange updatedSlot(
        newTimeSlot.startHour,
        newTimeSlot.endHour,
        currentSlot.date
    );

    // Basic validation: start < end
    if (updatedSlot.startHour >= updatedSlot.endHour) {
        cout << "Error: start time must be earlier than end time." << endl;
        return;
    }

    // Check for conflicts with other reservations on the same resource and date
    for (Reservation* r : reservations) {
        if (r == reservation) continue; //skip the reservation modifying

        if (r->getResource() == res) {
            DateAndTimeRange otherSlot = r->getTimeSlot();

            if (otherSlot.date == updatedSlot.date) {
                bool overlap = !(updatedSlot.endHour <= otherSlot.startHour ||
                                 updatedSlot.startHour >= otherSlot.endHour);

                if (overlap) {
                    cout << "Error: new time slot conflicts with an existing reservation."
                         << endl;
                    return;
                }
            }
        }
    }

    // If here then no conflict was found so update the reservation
    reservation->setTimeSlot(updatedSlot);
    cout << "Reservation successfully updated." << endl;
}