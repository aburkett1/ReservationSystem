#include "MusicRoom.h"

MusicRoom::MusicRoom(string title, TimeRange availability, int capacity, string location, bool soundproof)
: Resource(title, availability)
{
    this->capacity = capacity;
    this->location = location;
    this->soundproof = soundproof;
}

void MusicRoom::print() const {
    cout << left;
    cout << "--------------------------------" << "\n";
    cout << "========= " << title << " =========\n";
    cout << "--------------------------------" << "\n";
    cout << setw(20) << "ID: " << id << endl;
    cout << setw(20) << "Type: " << "Music Room" << endl;
    cout << setw(20) << "Availability hours: "
         << availabilityHours.converter24to12(availabilityHours.startHour) << " - " 
         << availabilityHours.converter24to12(availabilityHours.endHour) << endl;
    cout << setw(20) << "Capacity: "           << capacity << endl;
    cout << setw(20) << "Location: "           << location << endl;
    cout << setw(20) << "Soundproof Status: "  << (soundproof ? "True" : "False") << endl;
    cout << "--------------------------------" << "\n";
    cout << right;
}

void MusicRoom::exportToFile(ofstream& fout) const {
    fout << static_cast<int>(MUSIC_ROOM) << endl;
    fout << title << endl;
    fout << id << endl;
    fout << availabilityHours.startHour << endl;
    fout << availabilityHours.endHour << endl;
    fout << capacity << endl;
    fout << location << endl;
    fout << static_cast<int>(soundproof) << endl;
}

void MusicRoom::importFromFile(ifstream& fin) {
    getline(fin, title);
    fin >> id;
    fin >> availabilityHours.startHour;
    fin >> availabilityHours.endHour;
    fin >> capacity;
    fin.ignore(10000, '\n');
    getline(fin, location);
    int temp;
    fin >> temp;
    fin.ignore(10000, '\n');
    soundproof = static_cast<bool>(temp);
}