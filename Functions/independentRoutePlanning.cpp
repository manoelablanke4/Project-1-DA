//
// Created by cosme on 11/03/2025.
//
#include <unordered_set>

#include "..//include//CreatingMap.h"
#include "..//include//data_structures/MutablePriorityQueue.h"
#include "../include/IndependentRoutePlanning.h"
#include "../include/RoutePlanningUtils.h"

IndependentRoutesResult planFastestRoute(int origin, int destination, bool doAltPath) {
    Graph<Location> cityGraph;  // Single instance of the graph
    createMap(cityGraph);

    std::unordered_set<int> frstpath; // Stores the nodes that are part of the shortest path
    dijkstra(&cityGraph, origin, frstpath);

    IndependentRoutesResult result;
    result.bestTime = 0;
    result.bestPath = getBestPath(&cityGraph, origin, destination, result.bestTime);

    // If no best path found, return early
    result.foundBest = !result.bestPath.empty();
    if (!result.foundBest) {
        return result;
    }

    // Store nodes in shortest path to avoid in alternative path calculation
    for (size_t i = 1; i < result.bestPath.size() - 1; i++) {
        frstpath.insert(result.bestPath[i]);
    }

    if (doAltPath) {
        result.altTime = 0;
        dijkstra(&cityGraph, origin, frstpath);
        result.altPath = getBestPath(&cityGraph, origin, destination, result.altTime);
        result.foundAlt = !result.altPath.empty(); // Set true if altPath exists
    }

    return result;
}

void outputIndependentRouteResult(const IndependentRoutesResult& result, std::ostream& out, const int origin, const int destination) {
    out << "Source:" << origin << "\n";
    out << "Destination:" << destination << "\n";

    if (!result.foundBest) {
        out << "No Path Found\n";
        return;
    }

    // Format Best Route
    out << "BestDrivingRoute:";
    for (size_t i = 0; i < result.bestPath.size(); i++) {
        out << result.bestPath[i];
        if (i < result.bestPath.size() - 1) {
            out << ",";
        }
    }
    out << "(" << result.bestTime << ")\n";

    // Format Alternative Route (if exists)
    if (result.foundAlt) {
        out << "AlternativeDrivingRoute:";
        for (size_t i = 0; i < result.altPath.size(); i++) {
            out << result.altPath[i];
            if (i < result.altPath.size() - 1) {
                out << ",";
            }
        }
        out << "(" << result.altTime << ")\n";
    }
}