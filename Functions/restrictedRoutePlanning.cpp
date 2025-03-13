//
// Created by cosme on 13/03/2025.
//
#include <unordered_set>

#include "..\\src\\creatingMap.cpp"
#include "..\\include\\data_structures/MutablePriorityQueue.h"

bool relax(Edge<Location> *edge) {
    Vertex<Location>* orig=edge->getOrig();
    Vertex<Location>* dest=edge->getDest();
    if (dest->getDist()>(orig->getDist()+edge->getDriving())) {
        dest->setDist(orig->getDist()+edge->getDriving());
        dest->setPath(edge);
        return true;
    }
    return false;
}

void dijkstra(Graph<Location> * g, const int &origin,std::unordered_set<int> ignoreVertex) {
    for (auto v:g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    Vertex<Location>* s=idmap[origin];
    s->setDist(0);
    MutablePriorityQueue<Vertex<Location>> pq;
    pq.insert(s);
    while (!pq.empty()) {
        Vertex<Location>* v=pq.extractMin();
        for (auto e:v->getAdj()) {
            if (e->getDriving()!=INF && ignoreVertex.find(e->getDest()->getInfo().id) == ignoreVertex.end() && !e->getIgnored()) {
                double oldDist=e->getDest()->getDist();
                if (relax(e)) {
                    if (oldDist==INF) {
                        pq.insert(e->getDest());
                    }
                    else {
                        pq.decreaseKey(e->getDest());
                    }
                }
            }
        }
    }
}

static std::vector<int> getBestPath(Graph<Location> *g,const int &origin,const int &dest,double &time) {
    std::vector<int> res;
    Vertex<Location>* d=idmap[dest];
    res.push_back(d->getInfo().id);
    while (d->getPath()!=nullptr ) {
        time+=d->getPath()->getDriving();
        d=d->getPath()->getOrig();
        res.push_back(d->getInfo().id);
    }
    reverse(res.begin(),res.end());
    return res;

}

int main() {
    Graph<Location> cityGraph;  // Single instance of the graph
    createMap(cityGraph);
    int origin=3;
    std::unordered_set<int> ignoreVertex; // set where we will store the  nodes to be ignored
    ignoreVertex.insert(1211);
    for(auto v:cityGraph.getVertexSet()) {
      if(v->getInfo().id==3) {
        for(auto e:v->getAdj()) {
          if(e->getDest()->getInfo().id==1064) {
            e->setIgnored(true);
          }
        }
      }
    }
    dijkstra(&cityGraph,origin,ignoreVertex);
    double time=0;
    std::vector<int> bestPath=getBestPath(&cityGraph,origin,8,time);
    if (bestPath.empty()) {
        std::cout<<"No Path Found"<<std::endl;
        return 0;
    }
    double alttime=0;
    dijkstra(&cityGraph,origin,ignoreVertex);
    std::vector<int> altPath=getBestPath(&cityGraph,origin,8,alttime);
    std::cout<<"Best Path: ";
    for (auto v:bestPath) {
        std::cout<<v<<"->";
    }
    std::cout<<"\n"<<time<<std::endl;

    return 0;
}