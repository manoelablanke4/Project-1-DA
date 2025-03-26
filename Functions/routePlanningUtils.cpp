#include "../include/RoutePlanningUtils.h"

bool relax(Edge<Location> *edge, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex){
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

void dijkstra(Graph<Location> * g, const int &origin, bool driving, bool reverseNeeded, const std::unordered_set<int>& ignoreVertex) {
    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    Vertex<Location>* s = idmap[origin];
    s->setDist(0);
    if(ignoreVertex.find(origin) != ignoreVertex.end()) return;

    MutablePriorityQueue<Vertex<Location>> pq;
    pq.insert(s);

    while (!pq.empty()) {
        Vertex<Location>* v = pq.extractMin();

        for (auto e : v->getAdj()) {
            if (e->getDriving() != INF && ignoreVertex.find(e->getDest()->getInfo().id) == ignoreVertex.end() && !e->getIgnored()) {
                double oldDist = e->getDest()->getDist();
                if (relax(e, driving, reverseNeeded, ignoreVertex)) {
                    if (oldDist == INF) {
                        pq.insert(e->getDest());
                    } else {
                        pq.decreaseKey(e->getDest());
                    }
                }
            }
        }
    }
}

std::vector<int> getBestPath(Graph<Location>* g, const int& origin, const int& dest, double& time) {
    Vertex<Location>* d = idmap[dest];
    if (d->getDist() == INF) {
        return {};
    }

    std::vector<int> res;
    res.push_back(d->getInfo().id);

    while (d->getPath() != nullptr) {
        time += d->getPath()->getDriving();
        d = d->getPath()->getOrig();
        res.push_back(d->getInfo().id);
    }

    std::reverse(res.begin(), res.end());
    return res;
}

