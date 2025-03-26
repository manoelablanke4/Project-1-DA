#include "../include/envFriendlyRoutePlanning.h"
#include "../include/RoutePlanningUtils.h"

void markIgnoredEdges(const std::vector<std::pair<int,int>>& avoidSegments)
{
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


std::vector<int> buildBackwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*>& pathMap)
{
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

        if (origID == startID)
            break;
        currentID = origID;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> buildForwardPath(int startID, int endID, bool driving, double &accTime, const std::unordered_map<int, Edge<Location>*> &pathMap)
{
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

        if (nextID == endID)
        break;

        currentID = nextID;
        }

        return path;
}


bool ecoRoute(Graph<Location>& g, int originID, int destID, double maxWalkingTime, const std::unordered_set<int>& ignoreVertex, const std::vector<std::pair<int,int>>& avoidSegments)
{
    markIgnoredEdges(avoidSegments);

    dijkstra(&g, originID, true, false, ignoreVertex);

    std::unordered_map<int, double> driveDist;
    std::unordered_map<int, Edge<Location>*> drivePath;
    for (auto v : g.getVertexSet()) {
        driveDist[v->getInfo().id] = v->getDist();
        drivePath[v->getInfo().id] = v->getPath();
    }

    dijkstra(&g, destID, false, true, ignoreVertex);

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
        if(ignoreVertex.find(pid) != ignoreVertex.end()) continue;
        double dTime = driveDist[pid]; 
        double wTime = walkDist[pid];  

        if (dTime == INF || wTime == INF) continue;
        if (pid == originID || pid == destID) continue;
        if (wTime > maxWalkingTime) continue;
        if (dTime <= 1e-9) continue;
        if (wTime <= 1e-9) continue;

        double total = dTime + wTime;
        if (total < bestTotalTime) {
            bestTotalTime = total;
            bestWalkTime  = wTime;
            bestParking   = pid;
        }
        else if (std::fabs(total - bestTotalTime) < 1e-9) {
            if (wTime > bestWalkTime) {
                bestWalkTime  = wTime;
                bestParking   = pid;
            }
        }
    }

    if (bestParking == -1) {
        std::cout << "Source:" << originID << "\n";
        std::cout << "Destination:" << destID << "\n";
        std::cout << "DrivingRoute:none\n";
        std::cout << "ParkingNode:none\n";
        std::cout << "WalkingRoute:none\n";
        std::cout << "TotalTime:\n";
        std::cout << "Message:No possible route with max. walking time of "
                  << maxWalkingTime << " minutes.\n";
        return false;
    }

    double drivingTimeActual = 0.0;
    std::vector<int> driveRoute = buildBackwardPath(originID, bestParking, true, drivingTimeActual, drivePath);

    double walkingTimeActual = 0.0;
    std::vector<int> walkRoute = buildForwardPath(bestParking, destID, false, walkingTimeActual, walkPath);

    std::cout << "Source: " << originID << std::endl;
    std::cout << "Destination: " << destID << std::endl;
    std::cout << "Driving Route: ";
    for (size_t i = 0; i < driveRoute.size(); i++) {
        std::cout << driveRoute[i];
        if (i < driveRoute.size() - 1) std::cout << ",";
    }
    std::cout << "(" << drivingTimeActual << ")\n";

    std::cout << "Walking Route: ";
    for (size_t i = 0; i < walkRoute.size(); i++) {
        std::cout << walkRoute[i];
        if (i < walkRoute.size() - 1) std::cout << ",";
    }
    std::cout << "(" << walkingTimeActual << ")\n";

    std::cout << "TotalTime: " << (drivingTimeActual + walkingTimeActual) << std::endl;

    return true;
}


int main() {

    Graph<Location> cityGraph;
    createMap(cityGraph); 
    int originID = 8; 
    int destID   = 5;
    double maxWalkingTime = 18; 
    std::unordered_set<int> ignoreVertex = {};
    std::vector<std::pair<int,int>> avoidSegments = { };

    bool result = ecoRoute(cityGraph, originID, destID, maxWalkingTime, ignoreVertex, avoidSegments);

    return 0;
}