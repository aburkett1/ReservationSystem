#ifndef MUSICROOM_H_
#define MUSICROOM_H_

#include "Resource.h"
using namespace std;

// =============================================================================
// MARK: MusicRoom Class
// =============================================================================

class MusicRoom : public Resource {
public:
    // Constructors
    MusicRoom(): capacity(0), location(""), soundproof(false) {}
    MusicRoom(string title, TimeRange availability, int capacity, string location, bool soundproof);

    // Getters
    int getCapacity() const { return capacity; }
    string getLocation() const { return location; }
    bool isSoundproof() const { return soundproof; }

    // Setters
    void setCapacity(int capacity) { this->capacity = capacity; }
    void setLocation(string location) { this->location = location; }
    void setSoundproof(bool soundproof) { this->soundproof = soundproof; }

    // IO
    void print();
    void exportToFile(ofstream& fout) const;
    void importFromFile(ifstream& fin);

private:
    int capacity;
    string location;
    bool soundproof;
};

#endif