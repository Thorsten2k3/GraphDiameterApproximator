#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <sstream>
#include <assert.h>
#include <limits>
#include <iostream>

typedef uint64_t index; // more expressive name for an index into an array
typedef uint64_t count; // more expressive name for an integer quantity
typedef index node; // node indices are 0-based
typedef double edgeweight; // edge weight type

#define none std::numeric_limits<index>::max()
#define Vector std::vector

class Graph {

protected:
    
    count n; // current number of nodes
    count m; // current number of edges
    node z; // current upper bound of node ids
    count t; // current time step
    bool weighted; // true if this graph has been marked as weighted.

    // per node data
    Vector<count> deg; // degree of each node (size of neighborhood)
    Vector<bool> exists; // exists[v] is true if node v has not been removed from the graph
    
    // per edge data
    Vector<Vector<node> > adja; // neighbors/adjacencies
    Vector<Vector<edgeweight> > eweights; // edge weights
        
    // graph attributes
    std::string name;
        
    // contains edge maps (u, v) -> double
    std::vector<std::vector<std::vector<double> > > edgeMaps_double; 

    // stores default value for edgeMaps_double[i] at index i
    std::vector<double> edgeAttrDefaults_double; 

public:

    // defaults
    static constexpr double defaultEdgeWeight = 1.00;
    static constexpr edgeweight nullWeight = 0.0;
        
    Graph(count n);
        
    virtual ~Graph() = default;

    /**
     * Insert an undirected edge between two nodes.
     */
    void addEdge(node u, node v, edgeweight weight = defaultEdgeWeight);
        
    /**
     * @return Number of neighbors.
     */
    count degree(node v) const;
        
    /**
     * @return Number of nodes in the graph.
     */
    count numberOfNodes() const;
        
    /**
     * Iterate over all undirected pairs of nodesand call handler (lambda closure).
     */
    template<typename L> void forNodePairs(L handle) const;
        
    /**
     * Iterate over all neighbors of a node and call handler (lamdba closure).
     * (Note that a node is its own neighbor if there is a self-loop.)
     */
    template<typename L> void forNeighborsOf(node u, L handle) const;
                
};

template<typename L>
inline void Graph::forNodePairs(L handle) const {
        for (node u = 0; u < z; ++u) {
                if (exists[u]) {
                        for (node v = u + 1; v < z; ++v) {
                                // call node pair function
                                if (exists[v]) {
                                        handle(u, v);
                                }
                        }
                }
        }
}

template<typename L>
inline void Graph::forNeighborsOf(node u, L handle) const {
        for (node v : this->adja[u]) {
                if (v != none) {
                        handle(v);
                }
        }
}

#endif /* GRAPH_H_ */
