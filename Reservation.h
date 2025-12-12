#ifndef RESERVATION_H_
#define RESERVATION_H_

#include "User.h"
#include "Resource.h"
#include <string>
#include <fstream>
using namespace std;

struct DateAndTimeRange : public TimeRange {
    string date;

    DateAndTimeRange(int start, int end, string d)
        : TimeRange(start, end), date(d)
    {}
};

class Reservation {
public:
    Reservation()
        : user(nullptr), resource(nullptr), timeSlot{0, 0, ""}
    {}

    User* getUser() const { return user; }
    Resource* getResource() const { return resource; }
    DateAndTimeRange getTimeSlot() const { return timeSlot; }

    void setUser(User* user) { this->user = user; }
    void setResource(Resource* resource) { this->resource = resource; }
    void setTimeSlot(DateAndTimeRange timeSlot) { this->timeSlot = timeSlot; }

    // Use ids for user and resource
    void exportToFile(ofstream& fout) const;

private:
    User* user;
    Resource* resource;
    DateAndTimeRange timeSlot;
};

#endif