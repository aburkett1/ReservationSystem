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

    TimeRange(): startHour(0), endHour(0) {}

    TimeRange(int start, int end)
        : startHour(start), endHour(end) {}

    static string converter24to12(int time24hr)
    {
        if (time24hr == 0)
        {
            return "12 AM";
        }
        else if (time24hr == 12)
        {
            return "12 PM";
        }
        else if (time24hr > 12)
        {
            return to_string(time24hr - 12) + " PM";
        }
        else 
        {
            return to_string(time24hr) + " AM";
        }
    }
};

class Resource {
public:
    Resource()
        : id(nextId++), title(""), availabilityHours{0, 0} {}
    Resource(string title, TimeRange availability);
    virtual ~Resource() {}

    int getID() const { return id; }
    string getTitle() const { return title; }
    TimeRange getAvailabilityHours() const { return availabilityHours; }

    void setTitle(string title) { this->title = title; }
    void setAvailabilityHours(TimeRange availabilityHours) { this->availabilityHours = availabilityHours; }

    // IO
    virtual void print() const = 0;
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