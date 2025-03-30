#ifndef ROUTE_PLANNING_UTILS_H
#define ROUTE_PLANNING_UTILS_H

/**
 * @file RoutePlanningUtils.h
 * @brief Declarations of utility functions used for route planning with Dijkstra's algorithm and path extraction.
 */

#include <unordered_set>
#include "../include/data_structures/Graph.h"
#include "../include/data_structures/MutablePriorityQueue.h"
#include "../include/CreatingMap.h"

/**
 * @brief Attempts to relax an edge during Dijkstra's algorithm.
 *
 * Updates the destination vertex's distance if a shorter path is found through the given edge.
 *
 * @param edge Pointer to the edge to relax.
 * @param driving True to use driving time; false to use walking time.
 * @param reverseNeeded True if reverse edges are required for walking path reconstruction.
 * @param ignoreVertex Set of node IDs to ignore during pathfinding.
 * @return True if the relaxation updated the destination's distance.
 */
bool relax(Edge<Location> *edge, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex);

/**
 * @brief Executes Dijkstra's algorithm on a graph from a given origin.
 *
 * Initializes distances and predecessors for each vertex and computes shortest paths based on driving or walking cost.
 *
 * @param g Pointer to the graph.
 * @param origin ID of the origin vertex.
 * @param driving True to use driving times; false to use walking times.
 * @param reverseNeeded True if walking path reconstruction needs reverse edge tracking.
 * @param ignoreVertex Set of vertex IDs to be ignored during computation.
 * @note **Time Complexity:** O((V + E) log V), where V is number of vertices and E is number of edges.
 */
void dijkstra(const Graph<Location>* g, const int &origin, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex);

/**
 * @brief Retrieves the shortest path from origin to destination after Dijkstra has been run.
 *
 * Also computes the total time of the path and marks the used edges as ignored for future calculations.
 *
 * @param g Pointer to the graph.
 * @param origin ID of the starting node.
 * @param dest ID of the destination node.
 * @param time Reference to store the total time of the path.
 * @return Vector of node IDs representing the shortest path.
 */
std::vector<int> getBestPath(Graph<Location> *g, const int &origin, const int &dest, double &time);

#endif
