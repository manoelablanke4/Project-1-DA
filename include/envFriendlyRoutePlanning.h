#ifndef ENV_FRIENDLY_ROUTE_PLANNING_H
#define ENV_FRIENDLY_ROUTE_PLANNING_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "CreatingMap.h"

struct EnvironmentallyFriendlyRouteResult {
    bool pathFound = false;

    int origin = -1;
    int destination = -1;
    int parkingNode = -1;
    bool origExists = true;
    bool destExists = true;

    std::vector<int> drivingPath;
    std::vector<int> walkingPath;

    double drivingTime = 0.0;
    double walkingTime = 0.0;
    double totalTime = 0.0;
};

void markIgnoredEdges(const std::vector<std::pair<int,int>>& avoidSegments);

std::vector<int> buildBackwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*>& pathMap);

std::vector<int> buildForwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*>& pathMap);

EnvironmentallyFriendlyRouteResult planEnvironmentallyFriendlyRoute(int origin, int destination, int maxWalkTime,
                                                                    const std::unordered_set<int>& ignoreVertex,
                                                                    const std::vector<std::pair<int, int>>& avoidSegments);

void outputEnvironmentallyFriendlyRouteResult(const EnvironmentallyFriendlyRouteResult& result, std::ostream& out);

#endif // ENV_FRIENDLY_ROUTE_PLANNING_H