#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "../include/data_structures/Graph.h"

#define INF std::numeric_limits<double>::max()

struct Location {
    std::string name;
    int id;
    std::string code;
    bool parking;

    bool operator==(const Location& other) const {
        return id == other.id;
    }
};

std::unordered_map<int,Vertex<Location>*> idmap;

void readLocations(Graph<Location>& map, std::unordered_map<std::string, Vertex<Location>*>& locations) {
    std::ifstream LocationsFile("../data/Locations.csv");
    if (!LocationsFile.is_open()) {
        std::cerr << "Error opening Locations.csv" << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(LocationsFile, line);  // Ignore header

    while (std::getline(LocationsFile, line)) {
        std::istringstream iss(line);
        std::string name, id, code, parking;

        if (std::getline(iss, name, ',') && std::getline(iss, id, ',') &&
            std::getline(iss, code, ',') && std::getline(iss, parking, ',')) {

            Location location{name, std::stoi(id), code, (parking == "1")};
            map.addVertex(location);
            locations[code] = map.findVertex(location);  // Storing a pointer instead of a copy
            idmap[std::stoi(id)]=map.findVertex(location);
        }
    }

    LocationsFile.close();
}

void readDistances(Graph<Location>& map, std::unordered_map<std::string, Vertex<Location>*>& locations) {
    std::ifstream DistancesFile("../data/Distances.csv");
    if (!DistancesFile.is_open()) {
        std::cerr << "Error opening Distances.csv" << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(DistancesFile, line);  // Ignore header

    while (std::getline(DistancesFile, line)) {
        std::istringstream iss(line);
        std::string source, destination, driving, walking;

        if (std::getline(iss, source, ',') && std::getline(iss, destination, ',') &&
            std::getline(iss, driving, ',') && std::getline(iss, walking, ',')) {

            double driveTime = (driving == "X") ? INF : std::stod(driving);
            double walkTime = std::stod(walking);

            // Retrieving pointers to real vertices instead of copies
            Vertex<Location>* src = locations[source];
            Vertex<Location>* dest = locations[destination];

            if (src && dest) {
                map.addBidirectionalEdge(src->getInfo(), dest->getInfo(), driveTime, walkTime);
            }
        }
    }

    DistancesFile.close();
}

// Graph is now passed by reference to avoid creating multiple instances
void createMap(Graph<Location>& map) {
    std::unordered_map<std::string, Vertex<Location>*> locations;

    readLocations(map, locations);
    readDistances(map, locations);
}
