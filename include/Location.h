#ifndef LOCATION_H
#define LOCATION_H

/**
 * @file Location.h
 * @brief Defines the Location struct used to represent nodes in the route planning graph.
 */

#include <string>
#include <utility>  // For std::move

/**
 * @struct Location
 * @brief Represents a geographical location (node) with metadata.
 */
struct Location {
    std::string name;    /**< Name of the location (e.g., street, landmark). */
    int id;              /**< Unique identifier of the location. */
    std::string code;    /**< Code used to identify the location in data files. */
    int parking;         /**< Indicates if location has parking (1 = yes, 0 = no). */

    /**
     * @brief Equality operator based on the location ID.
     *
     * @param other The Location to compare with.
     * @return True if both locations have the same ID.
     */
    bool operator==(const Location& other) const {
        return id == other.id;
    }

    /**
     * @brief Default constructor.
     */
    Location() = default;

    /**
     * @brief Parameterized constructor.
     *
     * @param name Name of the location.
     * @param id Unique identifier.
     * @param code Code used in data files.
     * @param parking Whether it has parking (1 or 0).
     */
    Location(std::string name, int id, std::string code, int parking)
        : name(std::move(name)), id(id), code(std::move(code)), parking(parking) {}
};

#endif // LOCATION_H
