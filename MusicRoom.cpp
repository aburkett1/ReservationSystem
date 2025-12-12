#include "MusicRoom.h"

void MusicRoom::print() const {
    cout << left;
    cout << "--------------------------------" << "\n";
    cout << "========= " << getTitle() << " =========\n";
    cout << "--------------------------------" << "\n";
    cout << setw(20) << "ID: " << getID() << endl;
    cout << setw(20) << "Type: " << "Music Room" << endl;
    cout << setw(20) << "Availability hours: " << getAvailabilityHours().startHour << " - " << getAvailabilityHours().endHour << endl;
    cout << setw(20) << "Capacity: "           << capacity << endl;
    cout << setw(20) << "Location: "           << location << endl;
    cout << setw(20) << "Soundproof Status: "  << (soundproof ? "True" : "False") << endl;
    cout << right;
}

void MusicRoom::exportToFile(ofstream& fout) const {
    fout << getTitle() << endl;
    fout << static_cast<int>(MUSIC_ROOM) << endl;
    fout << getID() << endl;
    fout << getAvailabilityHours().startHour << endl;
    fout << getAvailabilityHours().endHour << endl;
    fout << capacity << endl;
    fout << location << endl;
    fout << static_cast<int>(soundproof) << endl;
}