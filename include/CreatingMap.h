#ifndef CREATINGMAP_H
#define CREATINGMAP_H

#include <iostream>
#include <unordered_map>
#include <string>
#include "../include/Location.h"
#include "data_structures/Graph.h"

// Extern declaration of the global idmap (defined in CreatingMap.cpp)
extern std::unordered_map<int, Vertex<Location>*> idmap;

// Function declarations
void readLocations(Graph<Location>& map, std::unordered_map<std::string, Vertex<Location>*>& locations);
void readDistances(Graph<Location>& map, std::unordered_map<std::string, Vertex<Location>*>& locations);
void createMap(Graph<Location>& map);

#endif // CREATINGMAP_H
