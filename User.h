#ifndef USER_H_
#define USER_H_

#include <fstream>
#include <iostream>
using namespace std;

// =============================================================================
// MARK: UserType Enum
// =============================================================================

enum UserType {
    ADMIN = 0,
    STUDENT
};


// =============================================================================
// MARK: User Class
// =============================================================================

class User {
public:
    // Constructors
    User()
        : name(""), id(nextId++), type(ADMIN) {}

    User(string name, UserType type)
        : name(name), id(nextId++), type(type) {}

    // Getters
    string getName() const { return name; }
    int getID() const { return id; }
    UserType getType() const { return type; }

    // Setters
    void setName(string name) { this->name = name; }
    void setType(UserType type) { this->type = type; }
    static void resetNextId() { nextId = 0; }

    // IO
    void exportToFile(ofstream& fout) const;
    void importFromFile(ifstream& fin);

private:
    string name;
    int id;
    inline static int nextId = 0;
    UserType type;
};

#endif