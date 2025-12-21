#ifndef STUDYROOM_H_
#define STUDYROOM_H_

#include "Resource.h"
using namespace std;

// =============================================================================
// MARK: StudyRoom Class
// =============================================================================

class StudyRoom : public Resource {
public:
    // Constructors
    StudyRoom(): capacity(0), location(""), whiteboardAmount(0) {}
    StudyRoom(string title, TimeRange availability, int capacity, string location, int whiteboardAmount);

    // Getters
    int getCapacity() const { return capacity; }
    string getLocation() const { return location; }
    int getWhiteboardAmount() const { return whiteboardAmount; }

    // Setters
    void setCapacity(int capacity) { this->capacity = capacity; }
    void setLocation(string location) { this->location = location; }
    void setWhiteboardAmount(int whiteboardAmount) { this->whiteboardAmount = whiteboardAmount; }

    // IO
    void print();
    void exportToFile(ofstream& fout) const;
    void importFromFile(ifstream& fin);

private:
    int capacity;
    string location;
    int whiteboardAmount;
};

#endif