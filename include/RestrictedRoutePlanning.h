#ifndef RESTRICTED_ROUTE_PLANNING_H
#define RESTRICTED_ROUTE_PLANNING_H

#include <vector>
#include <unordered_set>
#include <iostream>

struct RestrictedRoutesResult {
    bool pathFound = false;
    double bestTime = 0.0;
    std::vector<int> bestPath;
};

// Function declarations
RestrictedRoutesResult excludeNodesOrSegments(int origin, int destination,
                                             const std::unordered_set<int>& ignoreVertex,
                                             const std::vector<std::pair<int, int>>& avoidSegments,
                                             int include);

// Output function (fix the missing declaration)
void outputRestrictedRouteResult(const RestrictedRoutesResult& result, std::ostream& out, int origin, int destination);

#endif // RESTRICTED_ROUTE_PLANNING_H