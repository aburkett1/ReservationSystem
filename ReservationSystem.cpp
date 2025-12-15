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

// ========================================================================
// MARK: Admin
// ========================================================================

void ReservationSystem::addResource(Resource* resource) {
    resources.push_back(resource);
}

void ReservationSystem::editResource(Resource* resource) {
	//display all of the current values for the resource
	resource->print();
	cout << endl;
	
	//variables for new user input
	int newID;
	string newTitle;
	int newStart;
	int newEnd;
	int newCapacity;
	string newLocation;
	
	//get and set the new ID
	cout << "Enter New Resource ID: "; 
	cin  >> newID;
	resource->setID(newID);
	
	//get and set the new Title
	cout << "Enter New Resource Title: "; 
	getline(cin, newTitle);
	resource->setTitle(newTitle);
	
	//get and set the new start and end times
	cout << "Enter New Resource Start Time (integer): "; 
	cin  >> newStart;
	cout << "Enter New Resource End Time (integer): "; 
	cin  >> newEnd;
	resource->setAvailabilityHours({newStart, newEnd});
	
	//dynamically cast resource as a new musicRoom pointer
	MusicRoom* musicRoom = dynamic_cast<MusicRoom*>(resource);

    //dynamically cast resource as a new studyRoom pointer
	StudyRoom* studyRoom = dynamic_cast<StudyRoom*>(resource);
	
	//check to make sure the recast worked, if not it should be studyRoom instead
	if (musicRoom != nullptr){
		//get and set the new capacity
        cout << "Enter New Capacity (integer): ";
        cin  >> newCapacity;
        musicRoom->setCapacity(newCapacity);
        
        //get and set the new location
        cout << "Enter New Location: ";
        getline(cin, newLocation);
        musicRoom->setLocation(newLocation);
        
        //variable for new user input
		bool newSoundproof;
		
		//take in an integer value to set the new boolean for Soundproof
		cout << "Enter New Soundproof Boolean (0 for false, 1 for true): ";
		cin  >> newSoundproof;
		musicRoom->setSoundproof(newSoundproof);
	}
	
	//do this if the resource pointer needs to be recast to studyRoom instead 
	else{
        //get and set the new capacity
        cout << "Enter New Capacity (integer): ";
        cin  >> newCapacity;
        studyRoom->setCapacity(newCapacity);
        
        //get and set the new location
        cout << "Enter New Location: ";
        getline(cin, newLocation);
        studyRoom->setLocation(newLocation);

		//variable for new user input
		int newWhiteboardAmount;
		
		//get and set the new whiteboard amount
		cout << "Enter New Whiteboard Amount: ";
		cin  >> newWhiteboardAmount;
		studyRoom->setWhiteboardAmount(newWhiteboardAmount);
	}
}

void ReservationSystem::removeResource(Resource* resource) {
	//variables to keep track of important search criteria
	string targetTitle;
	int targetID;
	int resourceLocation;
	int index;
	
	//cycle through all indices in resources vector
	while(index < resources.size()){
		//set target search values
		targetTitle = resource->getTitle();
		targetID = resource->getID();
		
		//check if the current location is a match for the target resource
		if(resources[index]->getTitle() == targetTitle && resources[index]->getID() == targetID){
			//set the resource's location at this index for later use
			resourceLocation = index;
		}
		index++;
	}
	//delete the resource's referenced object, then make the pointer null to avoid a dumped variable
	delete resource;
	resource = nullptr;
	
	//erase the resource from the vector, which will then shift to fill the blank index
	resources.erase(resources.begin() + resourceLocation);
}

// ========================================================================
// MARK: File IO
// ========================================================================

void ReservationSystem::exportToFiles() {
    // ==== Export registeredUsers ====
    ofstream userOut("registered_users.txt");

    userOut << registeredUsers.size() << endl;

    for (User* user : registeredUsers) {
        user->exportToFile(userOut);
    }

    userOut.close();

    // ==== Export resources ====
    ofstream resourceOut("resources.txt");

    resourceOut << resources.size() << endl;

    for (Resource* resource : resources) {
        resource->exportToFile(resourceOut);
    }

    resourceOut.close();

    // ==== Export reservations ====
    ofstream reservationOut("reservations.txt");

    reservationOut << reservations.size() << endl;

    for (Reservation* reservation : reservations) {
        reservation->exportToFile(reservationOut);
    }

    reservationOut.close();
}

void ReservationSystem::importFromFiles() {
    // ==== Import registeredUsers ====
    ifstream userIn("registered_users.txt");

    if (!userIn)
        throw runtime_error("\n[importFromFile]: registered_users.txt failed to open.");

    int count;
    userIn >> count;
    userIn.ignore(10000, '\n');

    for (int i = 0; i < count; i++) {
        User* user = new User();
        user->importFromFile(userIn);
        registeredUsers.push_back(user);
    }

    userIn.close();

    // ==== Import resources ====
    ifstream resourcesIn("resources.txt");

    if (!resourcesIn)
        throw runtime_error("\n[importFromFile]: registered_users.txt failed to open.");

    resourcesIn >> count;
    resourcesIn.ignore(10000, '\n');

    for (int i = 0; i < count; i++) {
        Resource* resource = Resource::importResource(resourcesIn);
        resources.push_back(resource);
    }

    resourcesIn.close();

    // ==== Import reservations ====
    ifstream reservationsIn("reservations.txt");

    if (!reservationsIn)
        throw runtime_error("\n[importFromFile]: registered_users.txt failed to open.");

    reservationsIn >> count;
    reservationsIn.ignore(10000, '\n');

    for (int i = 0; i < count; i++) {
        Reservation* reservation = importReservation(reservationsIn);
        reservations.push_back(reservation);
    }

    reservationsIn.close();
}

// =============================================================================
// MARK: Helpers
// =============================================================================

User* ReservationSystem::searchUsersById(int id) const {
    for (int i = 0; i < registeredUsers.size(); i++) {
        if (registeredUsers[i]->getID() == id) {
            return registeredUsers[i];
        }
    }

    return nullptr;
}

Reservation* ReservationSystem::importReservation(ifstream& fin) {
    int userId, resourceId;
    fin >> userId >> resourceId;
  
    DateAndTimeRange timeSlot;
    fin >> timeSlot.startHour >> timeSlot.endHour;
    fin.ignore(10000, '\n');
    getline(fin, timeSlot.date);

    User* user = searchUsersById(userId);
    Resource* resource = searchID(resourceId);

    if (user == nullptr || resource == nullptr)
        throw runtime_error("\n[importReservation]: Reservation user or resource is invalid.");
  
    return new Reservation(user, resource, timeSlot);
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


vector<Reservation*> ReservationSystem::viewReservation() const
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