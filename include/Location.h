#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <utility>  // Para std::move

struct Location {
    std::string name;
    int id;
    std::string code;
    int parking;

    // Define operator==
    bool operator==(const Location& other) const {
        return id == other.id;
    }

    Location() = default;

    Location(std::string name, int id, std::string code, int parking)
        : name(std::move(name)), id(id), code(std::move(code)), parking(parking) {}
};

#endif // LOCATION_H
