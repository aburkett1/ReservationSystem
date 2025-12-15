#ifndef USER_H_
#define USER_H_

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

enum UserType {
    ADMIN = 0,
    STUDENT
};

class User {
public:
    User()
        : name(""), id(nextId++), type(ADMIN)
    {}

    User(string name, UserType type)
        : name(name), id(nextId++), type(type)
    {}

    string getName() const { return name; }
    int getID() const { return id; }
    UserType getType() const { return type; }

    void setName(string name) { this->name = name; }
    // void setID(int id) { this->id = id; }
    void setType(UserType type) { this->type = type; }
    static void resetNextId() { nextId = 0; }

    void exportToFile(ofstream& fout) const;
    void importFromFile(ifstream& fin);

private:
    string name;
    int id;
    inline static int nextId = 0;
    UserType type;
};

#endif