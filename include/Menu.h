#ifndef MENU_H
#define MENU_H

#include "../include/IndependentRoutePlanning.h"
#include "../include/RestrictedRoutePlanning.h"
#include "../include/data_structures/Graph.h"

void handleMenuSelection();
IndependentRoutesResult planFastestRoute(int origin, int destination, bool doAltPath);
RestrictedRoutesResult excludeNodesOrSegments(int origin, int destination,
                                             const std::unordered_set<int>& ignoreVertex,
                                             const std::vector<std::pair<int, int>>& avoidSegments,
                                             int include);

#endif // MENU_H
