#include "ReservationSystem.h"

// ========================================================================
// MARK: Constructors
// ========================================================================

ReservationSystem::~ReservationSystem() {    
    for (User* user : registeredUsers)
        delete user;

    for (Resource* resource : resources)
        delete resource;

    for (Reservation* reservation : reservations)
        delete reservation;
}

// ========================================================================
// MARK: Login
// ========================================================================

User* ReservationSystem::login()
{
    string username;
    cout << "Please enter username: ";
    getline(cin, username);

    User* user = searchUsersByName(username);

    if (user == nullptr)
        throw runtime_error("\n[login]: Username authentication failed.");

    return user;
}

void ReservationSystem::registerUser()
{
    string username;
    int type{};
    bool valid = false;

    cout << "--------------------------------" << '\n';
    cout << " ====  User Type Options   ==== " << '\n';
    cout << "--------------------------------" << '\n';
    cout << "\t0 - Admin\n";
    cout << "\t1 - Student\n";
    cout << "--------------------------------" << '\n';

    while (!valid) {
        cout << "Please select type option (0-1): ";

        if (!(cin >> type)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "-----------------------------------------------\n";
            cout << "Invalid Input. Please select type option (0-1).\n";
            cout << "-----------------------------------------------\n";
        } else {
            cin.ignore(10000, '\n');

            if (type < 0 || type > 1) {
                cout << "-----------------------------------------------\n";
                cout << "Invalid Input. Please select type option (0-1).\n";
                cout << "-----------------------------------------------\n";
            } else {
                valid = true;
            }
        }
    }

    cout << "Please enter username: ";
    getline(cin, username);
    
    User* userPtr = searchUsersByName(username);

    if (userPtr != nullptr) {
        cout << "User with that username already exists.\n\n";
    } else {
        User* newUser = new User(username, static_cast<UserType>(type));
        registeredUsers.push_back(newUser);

        cout << "User registered.\n\n";
    }
}

// ========================================================================
// MARK: Reservation
// ========================================================================

void ReservationSystem::createReservation(Resource* resource, DateAndTimeRange timeSlot, User* user)
{
    Reservation* reservation = new Reservation(user, resource, timeSlot);
    reservations.push_back(reservation);
}

void ReservationSystem::modifyReservation(Reservation* reservation, TimeRange newTimeSlot) {
    if (reservation == nullptr)
        throw runtime_error("\n[modifyReservation]: Invalid reservation pointer.");

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
    if (updatedSlot.startHour >= updatedSlot.endHour)
        throw runtime_error("\n[modifyReservation]: Start time must be earlier than end time.");

    // Check for conflicts with other reservations on the same resource and date
    for (Reservation* r : reservations) {
        if (r == reservation) continue; //skip the reservation modifying

        if (r->getResource() == res) {
            DateAndTimeRange otherSlot = r->getTimeSlot();

            if (otherSlot.date == updatedSlot.date) {
                bool overlap = !(updatedSlot.endHour <= otherSlot.startHour ||
                                 updatedSlot.startHour >= otherSlot.endHour);

                if (overlap)
                    throw runtime_error("\n[modifyReservation]: New time slot conflicts with an existing reservation.");
            }
        }
    }

    // If here then no conflict was found so update the reservation
    reservation->setTimeSlot(updatedSlot);
    cout << "Reservation successfully updated." << endl;
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

vector<Reservation*> ReservationSystem::viewReservation(User* client) const
{
    vector<Reservation*> result;

    for (Reservation* r : reservations) {
        // Check my implementation of getUser()
        if (r->getUser() == client) {
            result.push_back(r);
        }
    }

    return result;
}

// ========================================================================
// MARK: Resource Creation
// ========================================================================

void ReservationSystem::addResource(Resource* resource) {
    resources.push_back(resource);
}

void ReservationSystem::editResource(Resource* resource) {
	//display all of the current values for the resource
	resource->print();
	cout << endl;
	
	//variables for new user input
	string newTitle;
	int newStart;
	int newEnd;
	int newCapacity;
	string newLocation;
	
	//get and set the new Title
	cout << "Enter Title: "; 
	getline(cin, newTitle);
	resource->setTitle(newTitle);
	
	//get and set the new start and end times
	cout << "Enter Start Time (24hr): "; 
	cin  >> newStart;
    cin.ignore(10000, '\n');
	cout << "Enter End Time (24hr): "; 
	cin  >> newEnd;
    cin.ignore(10000, '\n');
	resource->setAvailabilityHours({newStart, newEnd});
	
	//dynamically cast resource as a new musicRoom pointer
	MusicRoom* musicRoom = dynamic_cast<MusicRoom*>(resource);

    //dynamically cast resource as a new studyRoom pointer
	StudyRoom* studyRoom = dynamic_cast<StudyRoom*>(resource);
	
	//check to make sure the recast worked, if not it should be studyRoom instead
	if (musicRoom != nullptr){
		//get and set the new capacity
        cout << "Enter Capacity: ";
        cin  >> newCapacity;
        cin.ignore(10000, '\n');
        musicRoom->setCapacity(newCapacity);
        
        //get and set the new location
        cout << "Enter Location: ";
        getline(cin, newLocation);
        musicRoom->setLocation(newLocation);
        
        //variable for new user input
		char newSoundproof;
		
		//take in an integer value to set the new boolean for Soundproof
		cout << "Is this room soundproof? [Y/N]: ";
		cin  >> newSoundproof;
        cin.ignore(10000, '\n');
		musicRoom->setSoundproof(toupper(newSoundproof) == 'Y');
	}
	
	//do this if the resource pointer needs to be recast to studyRoom instead 
	else{
        //get and set the new capacity
        cout << "Enter Capacity: ";
        cin  >> newCapacity;
        cin.ignore(10000, '\n');
        studyRoom->setCapacity(newCapacity);
        
        //get and set the new location
        cout << "Enter Location: ";
        getline(cin, newLocation);
        studyRoom->setLocation(newLocation);

		//variable for new user input
		int newWhiteboardAmount;
		
		//get and set the new whiteboard amount
		cout << "Enter Whiteboard Amount: ";
		cin  >> newWhiteboardAmount;
        cin.ignore(10000, '\n');
		studyRoom->setWhiteboardAmount(newWhiteboardAmount);
	}
}

void ReservationSystem::removeResource(Resource* resource) {
	//variables to keep track of important search criteria
	string targetTitle{};
	int targetID{};
	int resourceLocation = -1;
	int index{};

    //set target search values
    targetTitle = resource->getTitle();
    targetID = resource->getID();
	
	//cycle through all indices in resources vector
	while(index < resources.size() && resourceLocation == -1){
		//check if the current location is a match for the target resource
		if(resources[index]->getTitle() == targetTitle && resources[index]->getID() == targetID){
			//set the resource's location at this index for later use
			resourceLocation = index;
		}
		index++;
	}

    if (resourceLocation == -1)
        return;
    
    //erase the resource from the vector, which will then shift to fill the blank index
    resources.erase(resources.begin() + resourceLocation);

    //delete the resource's referenced object, then make the pointer null to avoid a dumped variable
    delete resources[resourceLocation];
    resource = nullptr;
}

void ReservationSystem::listResources() const {
    for (Resource* r : resources) {
        r->print();
        cout << endl;
    }
}

// ========================================================================
// MARK: Resource Utility
// ========================================================================

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
}

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
}

vector<Resource*> ReservationSystem::filterResourceType(ResourceType resourceFlag) const
{
    vector<Resource*> filteredResources{};

    for (Resource* resource : resources)
    {        
        if (resourceFlag == MUSIC_ROOM)
        {
            if (dynamic_cast<MusicRoom*>(resource))
            {
                filteredResources.push_back(resource);
            }
        }
        else if (resourceFlag == STUDY_ROOM)
        {
            if (dynamic_cast<StudyRoom*>(resource))
            {
                filteredResources.push_back(resource);
            }
        }
    }

    return filteredResources;
}

vector<int> ReservationSystem::checkAvailability(Resource* resource, string date)
{
    // Variables
    TimeRange availability{};
    vector<int> avialableTimeSlots{};

    // Get availablility
    availability = resource->getAvailabilityHours();

    // Create time slots
    for (int i = availability.startHour; i < availability.endHour; i++)
    {
        avialableTimeSlots.push_back(i);
    }

    // Check against reservations.
    for (auto reservation : reservations)
    {
        DateAndTimeRange timeSlot = reservation->getTimeSlot();
        if (date == timeSlot.date)
        {
            for (int i = timeSlot.startHour; i < timeSlot.endHour; i++)
            {
                // Set hour as unavailable
                avialableTimeSlots[i] = -1;
            }
        }
    }

    // Remove unavailable time slots
    for (int i = avialableTimeSlots.size() - 1; i >= 0; i--)
    {
        if (avialableTimeSlots[i] == -1)
        {
            avialableTimeSlots.erase(avialableTimeSlots.begin()+i);
        }
    }

    return avialableTimeSlots;
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
    User::resetNextId();

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
        throw runtime_error("\n[importFromFile]: resources.txt failed to open.");

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
        throw runtime_error("\n[importFromFile]: reservations.txt failed to open.");

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

User* ReservationSystem::searchUsersByName(string name) const {
    for (int i = 0; i < registeredUsers.size(); i++) {
        if (registeredUsers[i]->getName() == name) {
            return registeredUsers[i];
        }
    }

    return nullptr;
}