/**
 * @file CreatingMap.cpp
 * @brief Builds the graph structure from input files containing location and distance data.
 *
 * Parses data from files and adds vertices and edges to the graph.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "../include/data_structures/Graph.h"
#include "../include/CreatingMap.h"
#include "../include/Location.h"

#define INF std::numeric_limits<double>::max()

/**
 * @brief Global map from location IDs to their corresponding graph vertices.
 */
std::unordered_map<int, Vertex<Location>*> idmap;

/**
 * @brief Reads location data from a file and populates the graph with vertices.
 * 
 * Each location is inserted into the graph and stored in a map for reference by code and ID.
 *
 * @param map Reference to the graph to populate.
 * @param locations Map to store references to created vertices using their string codes.
 */
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
            Location location{name, std::stoi(id), code, std::stoi(parking)};
            map.addVertex(location);
            locations[code] = map.findVertex(location);  // Storing a pointer instead of a copy
            idmap[std::stoi(id)] = map.findVertex(location);
        }
    }

    LocationsFile.close();
}

/**
 * @brief Reads distance data from a file and adds bidirectional edges to the graph.
 * 
 * For each entry, edges are added between the corresponding locations with driving and walking times.
 *
 * @param map Reference to the graph to populate.
 * @param locations Map containing references to existing vertices (from `readLocations`).
 */
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

            Vertex<Location>* src = locations[source];
            Vertex<Location>* dest = locations[destination];

            if (src && dest) {
                map.addBidirectionalEdge(src->getInfo(), dest->getInfo(), driveTime, walkTime);
            }
        }
    }

    DistancesFile.close();
}

/**
 * @brief Initializes the full graph by reading both locations and distances from files.
 * 
 * @param map Graph reference to be filled with vertices and edges.
 */
void createMap(Graph<Location>& map) {
    std::unordered_map<std::string, Vertex<Location>*> locations;

    readLocations(map, locations);
    readDistances(map, locations);
}
