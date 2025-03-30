#ifndef CREATINGMAP_H
#define CREATINGMAP_H

/**
 * @file CreatingMap.h
 * @brief Declarations for reading location and distance data into a graph structure.
 */

#include <iostream>
#include <unordered_map>
#include <string>
#include "../include/Location.h"
#include "data_structures/Graph.h"

/**
 * @brief Global map associating location IDs with their corresponding vertex pointers in the graph.
 *
 * This is used across the project to access graph nodes directly by ID.
 */
extern std::unordered_map<int, Vertex<Location>*> idmap;

/**
 * @brief Reads location data from file and adds vertices to the graph.
 *
 * Also populates a map associating location codes to vertex pointers.
 *
 * @param map Graph to populate with location vertices.
 * @param locations Map to store references to vertices using location codes.
 * @note **Time Complexity:** O(N), where N is number of locations.
 */
void readLocations(Graph<Location>& map, std::unordered_map<std::string, Vertex<Location>*>& locations);

/**
 * @brief Reads distance data from file and adds edges to the graph.
 *
 * Adds bidirectional edges with driving and walking times between known locations.
 *
 * @param map Graph to populate with edges.
 * @param locations Map of location codes to existing vertex pointers.
 * @note **Time Complexity:** O(M), where M is number of distance entries.
 */
void readDistances(Graph<Location>& map, std::unordered_map<std::string, Vertex<Location>*>& locations);

/**
 * @brief Populates the graph with all location vertices and distance edges.
 *
 * This is the main entry point to initialize the graph using location and distance files.
 *
 * @param map Graph object to initialize.
 * @note **Time Complexity:** O(N + M), total locations plus distances.
 */
void createMap(Graph<Location>& map);

#endif // CREATINGMAP_H
