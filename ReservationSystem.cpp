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


void ReservationSystem::cancelReservation(Reservation* reservation)
{
    for (auto i = reservations.begin(); i != reservations.end(); ++i)
    {
        if (*i == reservation)
        {
            delete *i;
            reservations.erase(i);
            return;
        }
    }
}



void ReservationSystem::filterResourceType(ResourceType resourceFlag) const
{
    int choice;

    cout << "Select resource type:\n";
    cout << "0 - Music Room\n";
    cout << "1 - Study Room\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice != MUSIC_ROOM && choice != STUDY_ROOM)
    {
        cout << "invalid resource type\n";
        return;
    }

    resourceFlag = static_cast<ResourceType>(choice);
    
    for (Reservation* reservation : reservations)
    {
        Resource* res = reservation->getResource();

        if (resourceFlag == MUSIC_ROOM)
        {
            if (dynamic_cast<MusicRoom*>(res))
            {
                res->print();
                cout << endl;
            }
        }
        else if (resourceFlag == STUDY_ROOM)
        {
            if (dynamic_cast<StudyRoom*>(res))
            {
                res->print();
                cout << endl;
            }
        }
    }
}