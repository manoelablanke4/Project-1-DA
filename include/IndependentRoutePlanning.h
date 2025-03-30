#ifndef INDEPENDENT_ROUTE_PLANNING_H
#define INDEPENDENT_ROUTE_PLANNING_H

#include <vector>
#include <iostream>

/**
 * @file IndependentRoutePlanning.h
 * @brief Declarations related to the planning of fastest and alternative routes.
 */

/**
 * @struct IndependentRoutesResult
 * @brief Structure that stores the result of independent route calculations.
 */
struct IndependentRoutesResult {
    bool origExists = true;             /**< Indicates if the origin ID exists. */
    bool destExists = true;             /**< Indicates if the destination ID exists. */
    bool foundBest = false;             /**< True if the best route was found. */
    bool foundAlt = false;              /**< True if the alternative route was found. */
    double bestTime = 0.0;              /**< Duration of the best route. */
    double altTime = 0.0;               /**< Duration of the alternative route. */
    std::vector<int> bestPath;          /**< Node sequence of the best route. */
    std::vector<int> altPath;           /**< Node sequence of the alternative route. */
};

/**
 * @brief Calculates the fastest route between two points and, optionally, an alternative route.
 *
 * Uses Dijkstra's algorithm to compute the shortest path and an alternative one that avoids the best path.
 *
 * @param origin The ID of the origin location.
 * @param destination The ID of the destination location.
 * @param doAltPath If true, also calculates the alternative route.
 * @return A struct containing the results of the route calculation.
 * @note **Time Complexity:** O((N + M) log N), where N = nodes, M = edges.
 */
IndependentRoutesResult planFastestRoute(int origin, int destination, bool doAltPath);

/**
 * @brief Outputs the result of the fastest and alternative routes to the given output stream.
 *
 * @param result Structure containing the route results.
 * @param out Output stream (e.g., std::cout or file stream).
 * @param origin The ID of the origin location.
 * @param destination The ID of the destination location.
 * @note **Time Complexity:** O(N), where N = nodes in the route.
 */
void outputIndependentRouteResult(const IndependentRoutesResult& result,
                                   std::ostream& out, int origin, int destination);

#endif // INDEPENDENT_ROUTE_PLANNING_H
