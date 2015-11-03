#include "GraphDistance.h"

count GraphDistance::unweightedDistance(const Graph& g, node u, node v) const {
        BFS bfs;
        std::pair<std::vector<count>, node> distances = bfs.run_Feist(g, u);
        //std::cout << "Called BFS, distance between " << u << " and " << v << ": " << distances[v] << std::endl; // distance[v] makes trouble, see distance in return statement
        return (distances.first)[v];
}


