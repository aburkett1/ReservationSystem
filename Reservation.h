#ifndef RESERVATION_H_
#define RESERVATION_H_

#include "User.h"
#include "Resource.h"
using namespace std;

// =============================================================================
// MARK: Reservation Class
// =============================================================================

class Reservation {
public:
    // Constructors
    Reservation()
        : user(nullptr), resource(nullptr), timeSlot{0, 0, ""} {}

    Reservation(User* user, Resource* resource, DateAndTimeRange timeSlot)
        : user(user), resource(resource), timeSlot(timeSlot) {}

    // Getters
    User* getUser() const { return user; }
    Resource* getResource() const { return resource; }
    DateAndTimeRange getTimeSlot() const { return timeSlot; }

    // Setters
    void setUser(User* user) { this->user = user; }
    void setResource(Resource* resource) { this->resource = resource; }
    void setTimeSlot(DateAndTimeRange timeSlot) { this->timeSlot = timeSlot; }

    // IO
    void exportToFile(ofstream& fout) const;

private:
    User* user;
    Resource* resource;
    DateAndTimeRange timeSlot;
};

#endif