#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#include <fstream>
using namespace std;

enum ResourceType {
    MUSIC_ROOM = 0,
    STUDY_ROOM
};


struct TimeRange {
    int startHour;
    int endHour;

    TimeRange(int start, int end)
        : startHour(start), endHour(end)
    {}
};

class Resource {
public:
    Resource()
        : id(0), title(""), availabilityHours{0, 0}
    {}

    virtual ~Resource() {}

    int getID() const { return id; }
    string getTitle() const { return title; }
    TimeRange getAvailabilityHours() const { return availabilityHours; }

    void setID(int id) { this->id = id; }
    void setTitle(string title) { this->title = title; }
    void setAvailabilityHours(TimeRange availabilityHours) { this->availabilityHours = availabilityHours; }

    // IO
    virtual void print() const = 0;
    virtual void exportToFile(ofstream& fout) const = 0;

private:
    int id;
    string title;
    TimeRange availabilityHours;
};

#endif