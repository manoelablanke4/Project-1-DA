#ifndef ROUTE_PLANNING_UTILS_H
#define ROUTE_PLANNING_UTILS_H

#include <unordered_set>
#include "../include/data_structures/Graph.h"
#include "../include/data_structures/MutablePriorityQueue.h"
#include "../include/CreatingMap.h"

bool relax(Edge<Location> *edge, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex);

void dijkstra(const Graph<Location>* g, const int &origin, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex);
std::vector<int> getBestPath(Graph<Location> *g, const int &origin, const int &dest, double &time);

#endif