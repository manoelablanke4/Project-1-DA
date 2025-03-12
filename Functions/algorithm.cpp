//
// Created by cosme on 11/03/2025.
//
#include "..\\Functions\\creatingMap.cpp"

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

void dijkstra(Graph<Location> * g, const int &origin) {
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
            if (e->getDriving()!=INF){
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
    int origin=1;
    dijkstra(&cityGraph,origin);
    double time=0;
    std::vector<int> bestPath=getBestPath(&cityGraph,origin,8,time);
    if (bestPath.empty()) {
        std::cout<<"No Path Found"<<std::endl;
        return 0;
    }
    for (auto v:bestPath) {
        std::cout<<v<<"->";
    }
    std::cout<<"\n"<<time<<std::endl;

    return 0;
}