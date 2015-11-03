#ifndef BFS_H_
#define BFS_H_

#include <queue>

#include "Graph.h"

class BFS {
    
public:
    BFS() = default;
    virtual ~BFS() = default;

    /**
     * Breadth-first search from node source on Graph g.
     * @return Vector of unweighted distances from node source, i.e. the
     * length (number of edges) of the shortest path from node 'source' to any other vertex 
     * and node with max distance
     */
    virtual std::pair<std::vector<count>, node> run_Feist(const Graph& g, node source) const;

};

#endif /* BFS_H_ */
