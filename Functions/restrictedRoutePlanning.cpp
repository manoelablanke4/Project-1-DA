//
// Created by cosme on 13/03/2025.
//
#include <unordered_set>

#include "../include/CreatingMap.h"
#include "../include/RestrictedRoutePlanning.h"
#include "../include/RoutePlanningUtils.h"
#include <iostream>

RestrictedRoutesResult excludeNodesOrSegments(int origin, int destination,
                                             const std::unordered_set<int>& ignoreVertex,
                                             const std::vector<std::pair<int, int>>& avoidSegments,
                                             int include) {
    Graph<Location> cityGraph;
    createMap(cityGraph);

    RestrictedRoutesResult result;

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


void outputRestrictedRouteResult(const RestrictedRoutesResult& result, std::ostream& out,
                                 int origin, int destination) {
    out << "Source:" << origin << "\n";
    out << "Destination:" << destination << "\n";

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
