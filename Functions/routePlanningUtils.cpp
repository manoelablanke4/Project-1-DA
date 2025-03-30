/**
 * @file RoutePlanningUtils.cpp
 * @brief Utility functions used in route planning algorithms, including Dijkstra and path reconstruction.
 */

#include "../include/RoutePlanningUtils.h"

/**
 * @brief Relaxes an edge in the graph during Dijkstra's algorithm.
 *
 * This checks if the distance to the destination vertex can be improved by going through the current edge.
 * It also considers whether the edge should be ignored (due to restrictions or cost).
 *
 * @param edge Pointer to the edge to be relaxed.
 * @param driving True if using driving cost; false if using walking cost.
 * @param reverseNeeded True if the reverse edge should be used for path reconstruction.
 * @param ignoreVertex Set of node IDs that must be ignored.
 * @return True if the relaxation was successful and the destination distance was updated.
 */
bool relax(Edge<Location>* edge, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex) {
    if (edge->getIgnored()) return false;
    int destID = edge->getDest()->getInfo().id;
    if (ignoreVertex.find(destID) != ignoreVertex.end()) return false;

    Vertex<Location>* orig = edge->getOrig();
    Vertex<Location>* dest = edge->getDest();

    double cost = driving ? edge->getDriving() : edge->getWalking();
    if (cost == INF) return false;

    double newDist = orig->getDist() + cost;
    if (newDist < dest->getDist()) {
        dest->setDist(newDist);
        if (!driving && reverseNeeded) {
            dest->setPath(edge->getReverse());
        } else {
            dest->setPath(edge);
        }
        return true;
    }
    return false;
}

/**
 * @brief Runs Dijkstra's algorithm on the graph to calculate the shortest path from the origin.
 *
 * Initializes all vertices, and processes edges using a mutable priority queue.
 * Takes into account whether the user is driving or walking and which nodes should be ignored.
 *
 * @param g Pointer to the graph.
 * @param origin ID of the origin vertex.
 * @param driving True if using driving cost; false if using walking cost.
 * @param reverseNeeded True if reverse edge information is needed (for walking paths).
 * @param ignoreVertex Set of node IDs to be ignored during traversal.
 */
void dijkstra(const Graph<Location>* g, const int& origin, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex) {
    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    Vertex<Location>* s = idmap.at(origin);
    s->setDist(0);
    if (ignoreVertex.find(origin) != ignoreVertex.end()) return;

    MutablePriorityQueue<Vertex<Location>> pq;
    pq.insert(s);

    while (!pq.empty()) {
        Vertex<Location>* v = pq.extractMin();

        for (auto e : v->getAdj()) {
            if (e->getDriving() != INF && ignoreVertex.find(e->getDest()->getInfo().id) == ignoreVertex.end() && !e->getIgnored()) {
                double oldDist = e->getDest()->getDist();
                if (relax(e, driving, reverseNeeded, ignoreVertex)) {
                    if (oldDist == INF) pq.insert(e->getDest());
                    else pq.decreaseKey(e->getDest());
                }
            }
        }
    }
}

/**
 * @brief Reconstructs the best path from origin to destination after running Dijkstra's algorithm.
 *
 * Traverses the `path` pointers backwards from the destination to build the route, calculates total time,
 * and marks each used edge as ignored for future alternative route calculations.
 *
 * @param g Pointer to the graph.
 * @param origin ID of the origin node.
 * @param dest ID of the destination node.
 * @param time Reference to store the total time of the best path.
 * @return A vector of node IDs representing the best path found, or empty if no path exists.
 */
std::vector<int> getBestPath(Graph<Location>* g, const int& origin, const int& dest, double& time) {
    Vertex<Location>* d = idmap[dest];
    if (d->getDist() == INF) {
        return {};
    }

    std::vector<int> res;
    res.push_back(d->getInfo().id);
    while (d->getPath() != nullptr) {
        time += d->getPath()->getDriving();
        d->getPath()->setIgnored(true);
        d = d->getPath()->getOrig();
        res.push_back(d->getInfo().id);
    }
    std::reverse(res.begin(), res.end());
    return res;
}
