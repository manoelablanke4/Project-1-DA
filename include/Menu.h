#ifndef MENU_H
#define MENU_H

/**
 * @file Menu.h
 * @brief Function declarations related to user menu interaction and route planning options.
 */

#include "../include/IndependentRoutePlanning.h"
#include "../include/RestrictedRoutePlanning.h"
#include "../include/data_structures/Graph.h"

/**
 * @brief Starts the interactive menu loop, allowing the user to select route planning options.
 */
void handleMenuSelection();

/**
 * @brief Plans the fastest route between two locations using Dijkstra's algorithm.
 *
 * @param origin The ID of the origin location.
 * @param destination The ID of the destination location.
 * @param doAltPath Whether to also calculate the second-fastest path (if true).
 * @return IndependentRoutesResult containing the calculated route and metadata.
 */
IndependentRoutesResult planFastestRoute(int origin, int destination, bool doAltPath);

/**
 * @brief Plans a route between two locations, excluding specific nodes and/or segments, and optionally including a required node.
 *
 * @param origin The ID of the origin location.
 * @param destination The ID of the destination location.
 * @param ignoreVertex Set of nodes to avoid.
 * @param avoidSegments List of segments (edges) to avoid.
 * @param include Optional node that must be included in the route (-1 if none).
 * @return RestrictedRoutesResult containing the calculated restricted route and metadata.
 */
RestrictedRoutesResult excludeNodesOrSegments(int origin, int destination,
                                              const std::unordered_set<int>& ignoreVertex,
                                              const std::vector<std::pair<int, int>>& avoidSegments,
                                              int include);

#endif // MENU_H
