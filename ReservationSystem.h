#ifndef RESERVATIONSYSTEM_H_
#define RESERVATIONSYSTEM_H_

#include "Reservation.h"
#include "User.h"
#include "Resource.h"
#include "MusicRoom.h"
#include "StudyRoom.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class ReservationSystem {
public:
    // Constructors
    ReservationSystem() {}
    ~ReservationSystem();

    // Login
    User* login();
    void registerUser();
    
    // Reservation
    void createReservation(Resource* resource, DateAndTimeRange timeSlot, User* user);
    void modifyReservation(Reservation* reservation, TimeRange newTimeSlot);
    void cancelReservation(Reservation* reservation);
    vector<Reservation*> viewReservation(User* client) const;
    
    // Resource Creation
    void addResource(Resource* resource);
    void editResource(Resource* resource);
    void removeResource(Resource* resource);
    void listResources() const;
    
    // Resource Utility
    Resource* searchID(int id) const;
    vector<Resource*> searchTitle(string name) const;
    vector<Resource*> filterResourceType(ResourceType resourceFlag) const;
    vector<int> checkAvailability(Resource* resource, string date);
    
    // File IO
    void exportToFiles();
    void importFromFiles();

private:
    vector<User*> registeredUsers;
    vector<Resource*> resources;
    vector<Reservation*> reservations;

    // Helpers
    User* searchUsersById(int id) const;
    Reservation* importReservation(ifstream& fin);
    User* searchUsersByName(string name) const;
};

#endif