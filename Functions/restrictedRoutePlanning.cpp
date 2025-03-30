/**
 * @file RestrictedRoutePlanning.cpp
 * @brief Calculates the fastest route with restrictions on nodes, segments, and optional inclusion of a specific node.
 */

#include <unordered_set>

#include "../include/CreatingMap.h"
#include "../include/RestrictedRoutePlanning.h"
#include "../include/RoutePlanningUtils.h"
#include <iostream>

/**
 * @brief Calculates a restricted route between origin and destination.
 *
 * The route can exclude certain nodes and segments and optionally include a required node.
 *
 * @param origin ID of the starting location.
 * @param destination ID of the target location.
 * @param ignoreVertex Set of node IDs to avoid.
 * @param avoidSegments List of directed edges to avoid (pairs of node IDs).
 * @param include Node ID that must be included in the path (-1 if none).
 * @return A RestrictedRoutesResult containing the best path found and related info.
 */
RestrictedRoutesResult excludeNodesOrSegments(int origin, int destination,
                                             const std::unordered_set<int>& ignoreVertex,
                                             const std::vector<std::pair<int, int>>& avoidSegments,
                                             int include) {
    Graph<Location> cityGraph;
    createMap(cityGraph);

    RestrictedRoutesResult result;

    if (idmap.find(origin) == idmap.end()) {
        result.origExists = false;
    }
    if ( idmap.find(destination) == idmap.end()) {
        result.destExists = false;
    }

    if (idmap.find(include) == idmap.end() && include!=-1) {
        result.includeExists = false;
    }

    if (result.origExists == false || result.destExists == false || result.includeExists == false) {
        return result;
    }

    // Ignore custom segments from 'avoidSegments'
    for (auto &seg : avoidSegments) {
        int fromID = seg.first;
        int toID = seg.second;

        Vertex<Location>* fromV = nullptr;
        if (idmap.find(fromID) != idmap.end()) {
            fromV = idmap[fromID];
        }
        if (!fromV) continue; // Skip if the vertex is not found

        // Mark the edge (fromID -> toID) as ignored
        for (auto e : fromV->getAdj()) {
            if (e->getDest()->getInfo().id == toID) {
                e->setIgnored(true);
            }
        }
    }

    // Case 1: Standard Restricted Route (No Include)
    if (include == -1) {
        result.bestTime = 0.0;
        dijkstra(&cityGraph, origin, false, false, ignoreVertex);
        result.bestPath = getBestPath(&cityGraph, origin, destination, result.bestTime);

        result.pathFound = !result.bestPath.empty();
        return result;
    }

    // -----------------------------------------
    // Case 2: Restricted Route with Include
    // -----------------------------------------

    std::vector<int> pathToInclude, pathFromInclude;
    double timeToInclude = 0.0, timeFromInclude = 0.0;

    // Step 1: Compute origin → include
    dijkstra(&cityGraph, origin, false, false, ignoreVertex);
    pathToInclude = getBestPath(&cityGraph, origin, include, timeToInclude);

    if (pathToInclude.empty()) {
        result.pathFound = false;
        return result;
    }

    // Step 2: Compute include → destination
    dijkstra(&cityGraph, include, false, false, ignoreVertex);
    pathFromInclude = getBestPath(&cityGraph, include, destination, timeFromInclude);

    if (pathFromInclude.empty()) {
        result.pathFound = false;
        return result;
    }

    // Step 3: Merge both paths (removing duplicate "include" node)
    pathFromInclude.erase(pathFromInclude.begin());
    result.bestPath.insert(result.bestPath.end(), pathToInclude.begin(), pathToInclude.end());
    result.bestPath.insert(result.bestPath.end(), pathFromInclude.begin(), pathFromInclude.end());

    result.bestTime = timeToInclude + timeFromInclude;
    result.pathFound = true;

    return result;
}

/**
 * @brief Outputs the result of a restricted route calculation to a stream.
 *
 * Prints the source and destination IDs, any errors, and the computed restricted route if available.
 *
 * @param result The result struct containing route information.
 * @param out Output stream (e.g. std::cout or ofstream).
 * @param origin The origin location ID.
 * @param destination The destination location ID.
 */
void outputRestrictedRouteResult(const RestrictedRoutesResult& result, std::ostream& out,
                                 int origin, int destination) {
    out << "Source:" << origin << "\n";
    out << "Destination:" << destination << "\n";

    if (!result.origExists){ out << "Origin ID is invalid! "  << "\n";return;}

    if (!result.destExists){ out << "Destiny ID is invalid! "  << "\n";return;}

    if (!result.includeExists){ out << "Include ID is invalid! "  << "\n";return;}

    // Print Restricted Driving Route
    if (!result.bestPath.empty()) {
        out << "RestrictedDrivingRoute:";
        for (size_t i = 0; i < result.bestPath.size(); i++) {
            out << result.bestPath[i];
            if (i < result.bestPath.size() - 1) {
                out << ",";
            }
        }
        out << "(" << result.bestTime << ")\n";
    } else {
        out << "RestrictedDrivingRoute:No Path Found\n";
    }
}
