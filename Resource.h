#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include "TimeRange.h"
using namespace std;

// =============================================================================
// MARK: ResourceType Enum
// =============================================================================

enum ResourceType {
    MUSIC_ROOM = 0,
    STUDY_ROOM
};


// =============================================================================
// MARK: Resource Class
// =============================================================================

class Resource {
public:
    // Constructors
    Resource()
        : id(nextId++), title(""), availabilityHours{0, 0} {}
    Resource(string title, TimeRange availability);
    virtual ~Resource() {}

    // Getters
    int getID() const { return id; }
    string getTitle() const { return title; }
    TimeRange getAvailabilityHours() const { return availabilityHours; }

    // Setters
    void setTitle(string title) { this->title = title; }
    void setAvailabilityHours(TimeRange availabilityHours) { this->availabilityHours = availabilityHours; }

    // Console IO
    virtual void print() = 0;
    void displayTitle();

    // File IO
    virtual void exportToFile(ofstream& fout) const = 0;
    virtual void importFromFile(ifstream& fin) = 0;
    static Resource* importResource(ifstream& fin);

protected:
    string title;
    TimeRange availabilityHours;
    int id;
    inline static int nextId = 0;
};

#endif