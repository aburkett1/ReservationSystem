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
    ReservationSystem()
        : localUser(nullptr)
    {}
    ~ReservationSystem();

    // All users
    void login(string username);
    void listResources() const;
    vector<Resource*> searchTitle(string name) const;
    Resource* searchID(int id) const;
    vector<Resource*> filterResourceType(ResourceType resourceFlag) const;

    // Student
    void createReservation(Resource* resource, TimeRange timeSlot);
    void modifyReservation(Reservation* reservation, TimeRange newTimeSlot);
    vector<Reservation*> viewReservation() const;
    void cancelReservation(Reservation* reservation);

    // Admin
    void addResource(Resource* resource);
    void removeResource(Resource* resource);
    void editResource(Resource* resource);

    // File IO
    void exportToFile(ofstream& out);
    void importFromFile(ifstream& in);

    User* localUser;
    vector<User*> registeredUsers;
    vector<Resource*> resources;
    vector<Reservation*> reservations;
};

#endif