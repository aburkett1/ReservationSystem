#ifndef MUSICROOM_H_
#define MUSICROOM_H_

#include "Resource.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class MusicRoom : public Resource {
public:
    MusicRoom()
        : capacity(0), location(""), soundproof(false)
    {}

    int getCapacity() const { return capacity; }
    string getLocation() const { return location; }
    bool isSoundproof() const { return soundproof; }

    void setCapacity(int capacity) { this->capacity = capacity; }
    void setLocation(string location) { this->location = location; }
    void setSoundproof(bool soundproof) { this->soundproof = soundproof; }

    void print() const;
    void exportToFile(ofstream& fout) const;

private:
    int capacity;
    string location;
    bool soundproof;
};

#endif