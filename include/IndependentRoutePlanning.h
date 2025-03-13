#ifndef INDEPENDENT_ROUTE_PLANNING_H
#define INDEPENDENT_ROUTE_PLANNING_H
#include <vector>
#include <iostream>

struct IndependentRoutesResult {
    bool foundBest = false;
    bool foundAlt = false;
    double bestTime = 0.0;
    double altTime = 0.0;
    std::vector<int> bestPath;
    std::vector<int> altPath;
};

IndependentRoutesResult planFastestRoute(int origin, int destination, bool doAltPath);

// Function to print or write the route result
void outputIndependentRouteResult(const IndependentRoutesResult& result, std::ostream& out, int origin, int destination);

#endif // INDEPENDENT_ROUTE_PLANNING_H
