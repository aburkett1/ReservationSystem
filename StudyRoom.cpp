#include "StudyRoom.h"

void StudyRoom::print() const {
    cout << left;
    cout << "--------------------------------" << "\n";
    cout << "======== " << title << " ========\n";
    cout << "--------------------------------" << "\n";
    cout << setw(20) << "ID: " << id << endl;
    cout << setw(20) << "Type: " << "Study Room" << endl;
    cout << setw(20) << "Availability hours: " << availabilityHours.startHour << " - " << availabilityHours.endHour << endl;
    cout << setw(20) << "Capacity: " << capacity << endl;
    cout << setw(20) << "Location: " << location << endl;
    cout << setw(20) << "Whiteboards: " << whiteboardAmount << endl;
    cout << right;
}

void StudyRoom::exportToFile(ofstream& fout) const {
    fout << static_cast<int>(STUDY_ROOM) << endl;
    fout << title << endl;
    fout << id << endl;
    fout << availabilityHours.startHour << endl;
    fout << availabilityHours.endHour << endl;
    fout << capacity << endl;
    fout << location << endl;
    fout << whiteboardAmount << endl;
}

void StudyRoom::importFromFile(ifstream& fin) {
    getline(fin, title);
    fin >> id;
    fin >> availabilityHours.startHour;
    fin >> availabilityHours.endHour;
    fin >> capacity;
    fin.ignore(10000, '\n');
    getline(fin, location);
    fin >> whiteboardAmount;
    fin.ignore(10000, '\n');
}