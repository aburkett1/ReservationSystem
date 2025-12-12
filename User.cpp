#include "User.h"

void User::exportToFile(ofstream& fout) const {
    fout << name << endl;
    fout << id << endl;
    fout << static_cast<int>(type) << endl;
}