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

void excludeNodesOrSegments(int origin, int destination,
                            const std::unordered_set<int>& ignoreVertex,
                            const std::vector<std::pair<int,int>>& avoidSegments,
                            int include) {
    Graph<Location> cityGraph;
    createMap(cityGraph);

    // Local copy, because we'll modify it
    std::unordered_set<int> localIgnoreVertex = ignoreVertex;

    // Ignore custom segments from 'avoidSegments'
    for (auto &seg : avoidSegments) {
        int fromID = seg.first;
        int toID   = seg.second;

        Vertex<Location>* fromV = nullptr;
        if (idmap.find(fromID) != idmap.end()) {
            fromV = idmap[fromID];
        }
        if (!fromV) continue;

        for (auto e : fromV->getAdj()) {
            if (e->getDest()->getInfo().id == toID) {
                e->setIgnored(true);
            }
        }
    }

    double time = 0.0;
    dijkstra(&cityGraph, origin, localIgnoreVertex);

    // We'll declare bestPath
    std::vector<int> bestPath;

    // If include != -1 (no input), let's get bestPath from 'origin' to 'include'
    // otherwise from 'origin' to 'destination'
    if (include != -1) {
        bestPath = getBestPath(&cityGraph, origin, include, time);
    } else {
        bestPath = getBestPath(&cityGraph, origin, destination, time);
    }

    if (bestPath.empty()) {
        std::cout << "No Path Found" << std::endl;
        return;
    }

    std::cout << "Best Path: ";
    for (size_t i = 0; i < bestPath.size(); i++) {
        std::cout << bestPath[i];
        if (i < bestPath.size() - 1) {
            std::cout << "->";
        }
    }
    std::cout << "\nTime: " << time << std::endl;

}

