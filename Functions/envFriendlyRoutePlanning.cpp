#include "../include/envFriendlyRoutePlanning.h"
#include "../include/RoutePlanningUtils.h"
#include <cmath>
#include <algorithm>

void markIgnoredEdges(const std::vector<std::pair<int,int>>& avoidSegments) {
    for (auto &seg : avoidSegments) {
        int fromID = seg.first;
        int toID   = seg.second;
        if (idmap.find(fromID) == idmap.end()) continue;
        Vertex<Location>* fromV = idmap[fromID];
        for (auto e : fromV->getAdj()) {
            if (e->getDest()->getInfo().id == toID) {
                e->setIgnored(true);
            }
        }
    }
}

std::vector<int> buildBackwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*>& pathMap) {
    std::vector<int> path;
    int currentID = endID;
    path.push_back(endID);

    while (true) {
        auto it = pathMap.find(currentID);
        if (it == pathMap.end() || it->second == nullptr) {
            accTime = INF;
            break;
        }
        Edge<Location>* edge = it->second;
        double cost = driving ? edge->getDriving() : edge->getWalking();
        accTime += cost;

        int origID = edge->getOrig()->getInfo().id;
        path.push_back(origID);

        if (origID == startID) break;
        currentID = origID;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> buildForwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*>& pathMap) {
    std::vector<int> path;
    int currentID = startID;
    path.push_back(currentID);

    while (true) {
        auto it = pathMap.find(currentID);
        if (it == pathMap.end() || it->second == nullptr) {
            accTime = INF;
            break;
        }

        Edge<Location>* edge = it->second;
        double cost = driving ? edge->getDriving() : edge->getWalking();
        accTime += cost;

        int nextID = edge->getDest()->getInfo().id;
        path.push_back(nextID);

        if (nextID == endID) break;
        currentID = nextID;
    }

    return path;
}

EnvironmentallyFriendlyRouteResult planEnvironmentallyFriendlyRoute(int origin, int destination, int maxWalkTime,
                                                                    const std::unordered_set<int>& ignoreVertex,
                                                                    const std::vector<std::pair<int, int>>& avoidSegments) {
    Graph<Location> g;
    createMap(g);
    EnvironmentallyFriendlyRouteResult result;
    result.origin = origin;
    result.destination = destination;

    markIgnoredEdges(avoidSegments);

    dijkstra(&g, origin, true, false, ignoreVertex);

    std::unordered_map<int, double> driveDist;
    std::unordered_map<int, Edge<Location>*> drivePath;
    for (auto v : g.getVertexSet()) {
        driveDist[v->getInfo().id] = v->getDist();
        drivePath[v->getInfo().id] = v->getPath();
    }

    dijkstra(&g, destination, false, true, ignoreVertex);

    std::unordered_map<int, double> walkDist;
    std::unordered_map<int, Edge<Location>*> walkPath;
    for (auto v : g.getVertexSet()) {
        walkDist[v->getInfo().id] = v->getDist();
        walkPath[v->getInfo().id] = v->getPath();
    }

    double bestTotalTime = INF;
    double bestWalkTime = 0.0;
    int bestParking = -1;
    for (auto v : g.getVertexSet()) {

        if (v->getInfo().parking != 1) continue;
        int pid = v->getInfo().id;
        if (ignoreVertex.find(pid) != ignoreVertex.end()) continue;

        double dTime = driveDist[pid];
        double wTime = walkDist[pid];

        if (dTime == INF || wTime == INF) continue;
        if (pid == origin || pid == destination) continue;
        if (wTime > maxWalkTime) continue;
        if (dTime <= 1e-9 || wTime <= 1e-9) continue;

        double total = dTime + wTime;
        if (total < bestTotalTime || (std::fabs(total - bestTotalTime) < 1e-9 && wTime > bestWalkTime)) {
            bestTotalTime = total;
            bestWalkTime  = wTime;
            bestParking   = pid;
        }
    }

    if (bestParking == -1) {
        result.pathFound = false;
        return result;
    }

    result.parkingNode = bestParking;
    result.drivingPath = buildBackwardPath(origin, bestParking, true, result.drivingTime, drivePath);
    result.walkingPath = buildForwardPath(bestParking, destination, false, result.walkingTime, walkPath);
    result.totalTime = result.drivingTime + result.walkingTime;
    result.pathFound = true;

    return result;
}

void outputEnvironmentallyFriendlyRouteResult(const EnvironmentallyFriendlyRouteResult& result, std::ostream& out) {
    out << "Source:" << result.origin << "\n";
    out << "Destination:" << result.destination << "\n";

    if (!result.pathFound) {
        out << "DrivingRoute:none\n";
        out << "ParkingNode:none\n";
        out << "WalkingRoute:none\n";
        out << "TotalTime:\n";
        out << "Message:No possible route with given walking time constraint.\n";
        return;
    }

    out << "DrivingRoute:";
    for (size_t i = 0; i < result.drivingPath.size(); i++) {
        out << result.drivingPath[i];
        if (i < result.drivingPath.size() - 1) out << ",";
    }
    out << "(" << result.drivingTime << ")\n";

    out << "ParkingNode:" << result.parkingNode << "\n";

    out << "WalkingRoute:";
    for (size_t i = 0; i < result.walkingPath.size(); i++) {
        out << result.walkingPath[i];
        if (i < result.walkingPath.size() - 1) out << ",";
    }
    out << "(" << result.walkingTime << ")\n";

    out << "TotalTime:" << result.totalTime << "\n";
}