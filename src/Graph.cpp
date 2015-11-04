#include "../include/Graph.h"

Graph::Graph(count n) : n(n), m(0), z(n), t(0), weighted(false), deg(z, 0), exists(z, true), adja(z), eweights(z) {
    // set name from global id
    static int64_t graphId = 1;
    std::stringstream sstm;
    sstm << "Graph id" << graphId++;
    this->name = sstm.str();
}

void Graph::addEdge(node u, node v, edgeweight weight) {
    assert (u >= 0);
    assert (u <= this->z);
    assert (v >= 0);
    assert (v <= this->z); // node ids must be in range

    if (u == v) { // self-loop case
        this->adja[u].push_back(u);
        this->deg[u] += 1;
        this->eweights[u].push_back(weight);
        for (index attrId = 0; attrId < this->edgeMaps_double.size(); ++attrId) {
            double defaultAttr = this->edgeAttrDefaults_double[attrId];
            this->edgeMaps_double[attrId][u].push_back(defaultAttr);
        }
    } else {
        // set adjacency
        this->adja[u].push_back(v);
        this->adja[v].push_back(u);
        // increment degree counters
        this->deg[u] += 1;
        this->deg[v] += 1;
        // set edge weight
        this->eweights[u].push_back(weight);
        this->eweights[v].push_back(weight);
        // loop over all attributes, setting default attr
        for (index attrId = 0; attrId < this->edgeMaps_double.size(); ++attrId) {
            double defaultAttr = this->edgeAttrDefaults_double[attrId];
            this->edgeMaps_double[attrId][u].push_back(defaultAttr);
            this->edgeMaps_double[attrId][v].push_back(defaultAttr);
        }
    }

    m++; // increasing the number of edges
}

count Graph::degree(node v) const {
    assert (v >= 0);
    assert (v <= this->z); // node ids must be in range
    return deg[v];
}

count Graph::numberOfNodes() const {
    return this->n;
}