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
        // check if fromID is known
        if (idmap.find(fromID) != idmap.end()) {
            fromV = idmap[fromID];
        }
        if (!fromV) continue; // if we didn't find a vertex or it's null, skip

        // Mark the edge (fromID -> toID) as ignored
        for (auto e : fromV->getAdj()) {
            if (e->getDest()->getInfo().id == toID) {
                e->setIgnored(true);
            }
        }
    }

    // No include input
    if (include == -1) {
        double time = 0.0;
        dijkstra(&cityGraph, origin, localIgnoreVertex);

        std::vector<int> bestPath = getBestPath(&cityGraph, origin, destination, time);
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
        return;
    }

    // ------------------------------------------------------------------
    // If include != -1, we want: origin -> include -> destination
    // ------------------------------------------------------------------

    // 1) origin -> include
    double firstTime = 0.0;
    dijkstra(&cityGraph, origin, localIgnoreVertex);
    std::vector<int> firstPath = getBestPath(&cityGraph, origin, include, firstTime);

    if (firstPath.empty()) {
        std::cout << "No Path Found (origin -> include)" << std::endl;
        return;
    }


    // 3) include -> destination
    double secondTime = 0.0;
    dijkstra(&cityGraph, include, localIgnoreVertex);
    std::vector<int> secondPath = getBestPath(&cityGraph, include, destination, secondTime);

    if (secondPath.empty()) {
        std::cout << "No Path Found (include -> destination)" << std::endl;
        return;
    }

    secondPath.erase(secondPath.begin());

    firstPath.insert(firstPath.end(), secondPath.begin(), secondPath.end());
    double totalTime = firstTime + secondTime;

    std::cout << "Best Path with Include: ";
    for (size_t i = 0; i < firstPath.size(); i++) {
        std::cout << firstPath[i];
        if (i < firstPath.size() - 1) {
            std::cout << "->";
        }
    }
    std::cout << "\nTotal Time: " << totalTime << std::endl;
}

