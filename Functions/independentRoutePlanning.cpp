/**
 * @file IndependentRoutePlanning.cpp
 * @brief Implements the calculation of the fastest and alternative routes between two locations.
 *
 * This file includes logic for verifying input, running Dijkstra's algorithm, and formatting the output.
 */

#include <unordered_set>
#include "..//include//CreatingMap.h"
#include "../include/IndependentRoutePlanning.h"
#include "../include/RoutePlanningUtils.h"

/**
 * @brief Calculates the fastest route (and optionally an alternative route) between two locations.
 *
 * Uses Dijkstra's algorithm to find the shortest path from origin to destination.
 * If @p doAltPath is true, it also calculates an alternative path avoiding intermediate nodes from the best path.
 *
 * @param origin The ID of the origin location.
 * @param destination The ID of the destination location.
 * @param doAltPath Flag indicating whether to compute the alternative route.
 * @return IndependentRoutesResult Struct containing the result of the route(s) calculation.
 */
IndependentRoutesResult planFastestRoute(int origin, int destination, bool doAltPath) {
    Graph<Location> cityGraph;  // Single instance of the graph
    createMap(cityGraph);

    IndependentRoutesResult result;

    if (idmap.find(origin) == idmap.end()) {
        result.origExists = false;
    }
    if (idmap.find(destination) == idmap.end()) {
        result.destExists = false;
    }

    if (result.origExists == false || result.destExists == false) {
        return result;
    }

    std::unordered_set<int> frstpath; // Stores the nodes that are part of the shortest path
    dijkstra(&cityGraph, origin, false, false, frstpath);

    result.bestTime = 0;
    result.bestPath = getBestPath(&cityGraph, origin, destination, result.bestTime);

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
        dijkstra(&cityGraph, origin, false, false, frstpath);
        result.altPath = getBestPath(&cityGraph, origin, destination, result.altTime);
        result.foundAlt = !result.altPath.empty() && result.bestPath != result.altPath;
    }

    return result;
}

/**
 * @brief Outputs the result of the fastest and alternative routes to the given output stream.
 *
 * Includes formatting of the origin, destination, best route, and alternative route (if any).
 * If the origin or destination is invalid, or no route is found, an appropriate message is shown.
 *
 * @param result The result of the route planning.
 * @param out The output stream to write to (e.g., std::cout or file).
 * @param origin The ID of the origin location.
 * @param destination The ID of the destination location.
 */
void outputIndependentRouteResult(const IndependentRoutesResult& result, std::ostream& out, const int origin, const int destination) {
    out << "Source:" << origin << "\n";
    out << "Destination:" << destination << "\n";

    if (!result.origExists) {
        out << "Origin ID is invalid! " << "\n";
        return;
    }

    if (!result.destExists) {
        out << "Destiny ID is invalid! " << "\n";
        return;
    }

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

    // In case there's no alternative route
    if (!result.foundAlt) {
        out << "AlternativeDrivingRoute:";
        out << "No Alternative Path Found\n";
        return;
    }
}