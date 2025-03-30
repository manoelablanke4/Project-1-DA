#ifndef ENV_FRIENDLY_ROUTE_PLANNING_H
#define ENV_FRIENDLY_ROUTE_PLANNING_H

/**
 * @file envFriendlyRoutePlanning.h
 * @brief Declarations for environmentally friendly route planning using driving and walking paths.
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "CreatingMap.h"

/**
 * @struct EnvironmentallyFriendlyRouteResult
 * @brief Holds the result of the environmentally friendly route calculation.
 */
struct EnvironmentallyFriendlyRouteResult {
    bool pathFound = false;              /**< True if a valid route was found. */

    int origin = -1;                     /**< Origin node ID. */
    int destination = -1;                /**< Destination node ID. */
    int parkingNode = -1;                /**< Selected parking node ID. */
    bool origExists = true;              /**< True if the origin exists in the graph. */
    bool destExists = true;              /**< True if the destination exists in the graph. */

    std::vector<int> drivingPath;        /**< List of node IDs representing the driving segment of the route. */
    std::vector<int> walkingPath;        /**< List of node IDs representing the walking segment of the route. */

    double drivingTime = 0.0;            /**< Time taken for the driving segment. */
    double walkingTime = 0.0;            /**< Time taken for the walking segment. */
    double totalTime = 0.0;              /**< Total travel time (driving + walking). */
};

/**
 * @brief Marks edges (segments) in the graph as ignored based on the input list.
 *
 * @param avoidSegments List of edges (fromID, toID) to mark as ignored.
 */
void markIgnoredEdges(const std::vector<std::pair<int,int>>& avoidSegments);

/**
 * @brief Builds a path by backtracking from end to start using a map of edges.
 *
 * @param startID Origin node ID.
 * @param endID Destination node ID.
 * @param driving True for driving path, false for walking.
 * @param accTime Reference to store the accumulated time.
 * @param pathMap Map of node IDs to edges representing the path.
 * @return A list of node IDs representing the path from start to end.
 */
std::vector<int> buildBackwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*>& pathMap);

/**
 * @brief Builds a path from start to end using a forward map of edges.
 *
 * @param startID Starting node ID.
 * @param endID Destination node ID.
 * @param driving True for driving path, false for walking.
 * @param accTime Reference to store the accumulated time.
 * @param pathMap Map of node IDs to edges representing the path.
 * @return A list of node IDs representing the path from start to end.
 */
std::vector<int> buildForwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*>& pathMap);

/**
 * @brief Computes an environmentally friendly route by combining driving and walking segments.
 *
 * Finds a parking location that minimizes total travel time while respecting a maximum walking time constraint.
 *
 * @param origin Origin node ID.
 * @param destination Destination node ID.
 * @param maxWalkTime Maximum allowed walking time.
 * @param ignoreVertex Set of node IDs to avoid.
 * @param avoidSegments List of directed segments to avoid.
 * @return A structure containing the full route result.
 */
EnvironmentallyFriendlyRouteResult planEnvironmentallyFriendlyRoute(int origin, int destination, int maxWalkTime,
                                                                    const std::unordered_set<int>& ignoreVertex,
                                                                    const std::vector<std::pair<int, int>>& avoidSegments);

/**
 * @brief Outputs the environmentally friendly route result to a stream.
 *
 * @param result Struct containing the route information.
 * @param out Output stream (e.g. std::cout or file).
 */
void outputEnvironmentallyFriendlyRouteResult(const EnvironmentallyFriendlyRouteResult& result, std::ostream& out);

#endif // ENV_FRIENDLY_ROUTE_PLANNING_H
