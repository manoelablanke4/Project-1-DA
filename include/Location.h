#ifndef LOCATION_H
#define LOCATION_H

struct Location {
    std::string name;
    int id;
    std::string code;
    bool parking;
    // Define operator==
    bool operator==(const Location& other) const {
        return id == other.id;
    }
};

#endif // LOCATION_H
