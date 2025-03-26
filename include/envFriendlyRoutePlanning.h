#ifndef ENV_FRIENDLY_ROUTE_PLANNING_H
#define ENV_FRIENDLY_ROUTE_PLANNING_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <limits>
#include <iostream>
#include "../src/creatingMap.cpp"  
#include "data_structures/MutablePriorityQueue.h"


struct EnvironmentallyFriendlyRouteResult {
    bool pathFound = false;

    int origin = -1;
    int destination = -1;
    int parkingNode = -1;

    std::vector<int> drivingPath;
    std::vector<int> walkingPath;

    double drivingTime = 0.0;
    double walkingTime = 0.0;
    double totalTime = 0.0;
};


// Forward-declare or include the classes and structures you need
// e.g., if you have a "Location" struct/class somewhere, you can do:
// #include "Location.h" 
// or just forward-declare if you only need pointers/references.

            // Assuming this contains the Graph, Vertex, Edge definitions
                               // or wherever your Graph, Vertex, and Edge templates are declared.


// If you have a global idmap, you might need its declaration here, e.g.:
// extern std::unordered_map<int, Vertex<Location>*> idmap;

/**
 * @brief Attempts to relax (update) the distance/path of 'edge->getDest()' 
 *        from 'edge->getOrig()' plus the given cost. 
 *        Optionally uses the reverse edge if we are walking from the destination 
 *        in an undirected graph.
 *
 * @param edge         The edge being considered for relaxation
 * @param driving      True if using driving cost, false if using walking cost
 * @param reverseNeeded If true, store `edge->getReverse()` in the path pointer 
 *                     (used when running Dijkstra from destination in an undirected graph)
 * @return true if the relaxation improved the distance to the destination vertex,
 *         false otherwise.
 */
bool relax(Edge<Location>* edge, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex);

/**
 * @brief Runs a Dijkstra-style shortest path computation on the given graph,
 *        starting at `startID`. The boolean flags control whether to use driving or
 *        walking costs, and whether to store reverse edges for path reconstruction.
 *
 * @param g            Pointer to the graph
 * @param startID      The ID of the start (origin or destination)
 * @param driving      True if using driving costs, false if walking
 * @param reverseNeeded True if we are walking from destination in an undirected graph
 */
void dijkstra(Graph<Location>* g, int startID, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex);

/**
 * @brief Reconstructs a path in "backward" style, starting from `endID` and 
 *        moving backward via each node's stored path pointer (`edge->getOrig()`),
 *        until we reach `startID`.
 *
 * @param startID      The origin node ID
 * @param endID        The end node ID
 * @param driving      True if we are summing driving cost, false if walking
 * @param accTime      Reference to a double that accumulates total path cost
 * @param pathMap      A map of (node ID -> edge pointer) used for reconstruction
 * @return A list of node IDs in the order [startID, ..., endID].
 * 
 */

void markIgnoredEdges(const std::vector<std::pair<int,int>>& avoidSegments);

/**
 * @brief Marks edges in the graph as ignored, based on a list of segments to avoid.
 *
 * @param avoidSegments A list of (fromID, toID) pairs representing segments to avoid
 */

std::vector<int> buildBackwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*>& pathMap);

/**
 * @brief Reconstructs a path in "forward" style, starting from `startID`
 *        and following each node's stored path pointer to the next node 
 *        (`edge->getDest()`), until we reach `endID`.
 *
 * @param startID      The start node ID
 * @param endID        The end node ID
 * @param driving      True if we are summing driving cost, false if walking
 * @param accTime      Reference to a double that accumulates total path cost
 * @param pathMap      A map of (node ID -> edge pointer) used for reconstruction
 * @return A list of node IDs in the order [startID, ..., endID].
 */
std::vector<int> buildForwardPath(int startID, int endID, bool driving, double &accTime,const std::unordered_map<int, Edge<Location>*>& pathMap);

/**
 * @brief Searches for the best combined driving+walking route from originID to destID,
 *        subject to a maximum walking time. Driving from origin to a parking node,
 *        then walking from that node to destination.
 *
 *        If no route is found, prints an informative message and returns false.
 *        Otherwise, prints the routes and returns true.
 *
 * @param g            Reference to the graph of type Graph<Location>
 * @param originID     The origin node ID
 * @param destID       The destination node ID
 * @param maxWalkingTime The maximum walking time allowed
 * @return true if a suitable route was found, false otherwise.
 */
bool ecoRoute(Graph<Location>& g, int originID, int destID, double maxWalkingTime, const std::unordered_set<int>& ignoreVertex, const std::vector<std::pair<int,int>>& avoidSegments);

EnvironmentallyFriendlyRouteResult planEnvironmentallyFriendlyRoute(int origin, int destination, int maxWalkTime, const std::unordered_set<int>& ignoreVertex,
                                                                    const std::vector<std::pair<int, int>>& avoidSegments);

void outputEnvironmentallyFriendlyRouteResult(const EnvironmentallyFriendlyRouteResult result, std::ostream& out);

#endif // ECO_ROUTE_H
