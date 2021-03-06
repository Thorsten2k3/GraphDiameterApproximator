#include "../include/BFS.h"

std::pair<std::vector<count>, node> BFS::run_Feist(const Graph& g, node source) const {
    count infDist = std::numeric_limits<count>::max();
    count n = g.numberOfNodes();
    std::vector<count> distances(n, infDist);
    std::queue<node> q;

    distances[source] = 0;
    q.push(source);
    node max_node; 

    while (! q.empty()) {
        node current = q.front();
        q.pop();
        //std::cout << "current node in BFS: " << current << " ";

        // insert untouched neighbors into queue
        g.forNeighborsOf(current, [&](node neighbor) {
                if (distances[neighbor] == infDist) {
                    q.push(neighbor);
                    distances[neighbor] = distances[current] + 1;
                    max_node = neighbor; 
                }    
            });
    }

    return std::make_pair (distances, max_node);
}
