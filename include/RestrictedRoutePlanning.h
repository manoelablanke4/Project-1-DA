#ifndef RESTRICTED_ROUTE_PLANNING_H
#define RESTRICTED_ROUTE_PLANNING_H

/**
 * @file RestrictedRoutePlanning.h
 * @brief Declares functions and data structures for route planning with node and segment restrictions.
 */

#include <vector>
#include <unordered_set>
#include <iostream>

/**
 * @struct RestrictedRoutesResult
 * @brief Holds the result of a restricted route calculation.
 */
struct RestrictedRoutesResult {
    bool origExists = true;              /**< Whether the origin node exists in the graph. */
    bool destExists = true;              /**< Whether the destination node exists in the graph. */
    bool includeExists = true;           /**< Whether the include node exists (if specified). */
    bool pathFound = false;              /**< True if a valid path was found. */
    double bestTime = 0.0;               /**< Total time/cost of the best path. */
    std::vector<int> bestPath;           /**< Sequence of node IDs representing the best path. */
};

/**
 * @brief Calculates the best path from origin to destination with restrictions.
 *
 * Allows ignoring specific nodes and segments, and optionally forces the path to include a certain node.
 *
 * @param origin ID of the origin node.
 * @param destination ID of the destination node.
 * @param ignoreVertex Set of node IDs to be avoided.
 * @param avoidSegments List of directed edges to be avoided.
 * @param include Optional node ID that must be included in the route (-1 if none).
 * @return A RestrictedRoutesResult containing the path and metadata.
 */
RestrictedRoutesResult excludeNodesOrSegments(int origin, int destination,
                                              const std::unordered_set<int>& ignoreVertex,
                                              const std::vector<std::pair<int, int>>& avoidSegments,
                                              int include);

/**
 * @brief Outputs the restricted route result to a given stream (console or file).
 *
 * Prints the route, time, and error messages if inputs are invalid or no path is found.
 *
 * @param result The result structure containing the path and related info.
 * @param out Output stream to write to (e.g., std::cout or std::ofstream).
 * @param origin ID of the origin node.
 * @param destination ID of the destination node.
 */
void outputRestrictedRouteResult(const RestrictedRoutesResult& result, std::ostream& out, int origin, int destination);

#endif // RESTRICTED_ROUTE_PLANNING_H
