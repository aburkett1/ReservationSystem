#ifndef STUDYROOM_H_
#define STUDYROOM_H_

#include "Resource.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class StudyRoom : public Resource {
public:
    StudyRoom(): capacity(0), location(""), whiteboardAmount(0) {}
    StudyRoom(string title, TimeRange availability, int capacity, string location, int whiteboardAmount);

    int getCapacity() const { return capacity; }
    string getLocation() const { return location; }
    int getWhiteboardAmount() const { return whiteboardAmount; }

    void setCapacity(int capacity) { this->capacity = capacity; }
    void setLocation(string location) { this->location = location; }
    void setWhiteboardAmount(int whiteboardAmount) { this->whiteboardAmount = whiteboardAmount; }

    void print() const;
    void exportToFile(ofstream& fout) const;
    void importFromFile(ifstream& fin);

private:
    int capacity;
    string location;
    int whiteboardAmount;
};

#endif