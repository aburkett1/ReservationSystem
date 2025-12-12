#include "Reservation.h"

void Reservation::exportToFile(ofstream& fout) const {
    fout << user->getID() << endl;
    fout << resource->getID() << endl;
    fout << timeSlot.startHour << endl;
    fout << timeSlot.endHour << endl;
    fout << timeSlot.date << endl;
}