#ifndef GRAPHDISTANCE_H_
#define GRAPHDISTANCE_H_

#include "Graph.h"
#include "BFS.h"

class GraphDistance {

public:
    GraphDistance() = default;
    virtual ~GraphDistance() = default;

    /**
     * @return Number of edges on shortest unweighted path between node 'u' node 'v'.
     */
    virtual count unweightedDistance(const Graph& g, node u, node v) const;
};

#endif /* GRAPHDISTANCE_H_ */
