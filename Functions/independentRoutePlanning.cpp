//
// Created by cosme on 11/03/2025.
//
#include <unordered_set>

#include "..//include//CreatingMap.h"
#include "..//include//data_structures/MutablePriorityQueue.h"
#include "../include/IndependentRoutePlanning.h"
#include "../include/RoutePlanningUtils.h"

void planFastestRoute(int origin, int destination, bool doAltPath) {
    Graph<Location> cityGraph;  // Single instance of the graph
    createMap(cityGraph);
    std::unordered_set<int> frstpath; // set where we will store the  nodes that are part of the shortest path
    dijkstra(&cityGraph,origin,frstpath);
    double besttime=0;
    std::vector<int> bestPath=getBestPath(&cityGraph,origin,destination,besttime);
    if (bestPath.empty()) {
        std::cout<<"No Path Found"<<std::endl;
        return;
    }
    for (int i=1;i<bestPath.size()-1;i++) {
        frstpath.insert(bestPath[i]);
    }
    double alttime=0;
    dijkstra(&cityGraph,origin,frstpath);
    std::vector<int> altPath=getBestPath(&cityGraph,origin,destination,alttime);
    std::cout << "Best Path: ";
    for (size_t i = 0; i < bestPath.size(); i++) {
        std::cout << bestPath[i];
        if (i < bestPath.size() - 1) {
            std::cout << "->";
        }
    }
    std::cout << "\n" << "Best Time: " << besttime << std::endl;

    if(doAltPath){
        std::cout << "Alt Path: ";
        for (size_t i = 0; i < altPath.size(); i++) {
            std::cout << altPath[i];
            if (i < altPath.size() - 1) {
                std::cout << "->";
            }
        }
        std::cout << "\n" << "Alt Time: " << alttime << std::endl;
    }
    else std::cout<<std::endl;

    return;
}