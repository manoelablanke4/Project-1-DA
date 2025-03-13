//
// Created by cosme on 13/03/2025.
//
#include <unordered_set>

#include "../include/CreatingMap.h"
#include "../include/data_structures/MutablePriorityQueue.h"
#include "../include/RestrictedRoutePlanning.h"
#include "../include/RoutePlanningUtils.h"
#include <algorithm>
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

    // No include input (Standard Restricted Route)
    if (include == -1) {
        result.bestTime = 0.0;
        dijkstra(&cityGraph, origin, ignoreVertex);

        result.bestPath = getBestPath(&cityGraph, origin, destination, result.bestTime);
        if (result.bestPath.empty()) {
            result.pathFound = false;
        } else {
            result.pathFound = true;
        }

        return result;
    }

    // ------------------------------------------------------------------
    // If include != -1, we want: origin -> include -> destination
    // ------------------------------------------------------------------

    // 1) origin -> include
    result.bestTime = 0.0;
    dijkstra(&cityGraph, origin, ignoreVertex);
    result.bestPath = getBestPath(&cityGraph, origin, include, result.bestTime);

    if (result.bestPath.empty()) {
        result.pathFound = false;
        return result;
    }

    // 2) include -> destination
    double secondTime = 0.0;
    dijkstra(&cityGraph, include, ignoreVertex);
    std::vector<int> secondPath = getBestPath(&cityGraph, include, destination, secondTime);

    if (secondPath.empty()) {
        result.pathFound = false;
        return result;
    }

    secondPath.erase(secondPath.begin()); // Remove duplicate "include" node
    result.bestPath.insert(result.bestPath.end(), secondPath.begin(), secondPath.end());
    result.bestTime += secondTime;
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
