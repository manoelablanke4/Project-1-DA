#ifndef RESTRICTED_ROUTE_PLANNING_H
#define RESTRICTED_ROUTE_PLANNING_H

#include <unordered_set>
#include <vector>
#include "../include/data_structures/Graph.h"

void excludeNodesOrSegments(int origin, int destination, const std::unordered_set<int>& ignoreVertex, const std::vector<std::pair<int,int>>& avoidSegments, int include);

#endif // RESTRICTED_ROUTE_PLANNING_H
