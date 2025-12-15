#include "User.h"

void User::exportToFile(ofstream& fout) const {
    fout << name << endl;
    fout << id << endl;
    fout << static_cast<int>(type) << endl;
}

void User::importFromFile(ifstream& fin) {
    getline(fin, name);

    fin >> id;

    if (id >= nextId)
        nextId = id + 1;

    int intType;
    fin >> intType;
    type = static_cast<UserType>(intType);

    fin.ignore(10000, '\n');
}