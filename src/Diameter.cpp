#include "../include/Diameter.h"

std::pair<count, count> Diameter::estimatedDiameterRange(const Graph& G, count p) {
    count lowerBound = 0;
    count upperBound = std::numeric_limits<count>::max();

    node startNode;
    count inc = 0;
    count infDist = std::numeric_limits<count>::max();
    count n = G.numberOfNodes();
    std::pair<std::vector<count>, node> resultOfBFS;

    std::default_random_engine rand;
    rand.seed(std::random_device()());
    std::uniform_int_distribution<node> range(0, n-1);

    std::vector<count> highToLow(n);
    std::iota(begin(highToLow), end(highToLow), 0);
    std::sort(begin(highToLow), end(highToLow), [&] (node v1, node v2) {
            return G.degree(v1) > G.degree(v2);
        });

    // check if G is a connected Graph
    {
        startNode = range(rand);

        BFS bfs;    
        resultOfBFS = bfs.run_Feist(G, startNode); 

        for(count& e : resultOfBFS.first) {
            if (e == infDist) {
                lowerBound = infDist;
                upperBound = infDist;
                return std::make_pair(lowerBound, upperBound);
            }
        }        
    }
    
    while (upperBound - lowerBound >= p) {

        // 1. compute double sweep lower bound
        {
            startNode = range(rand);

            BFS bfs;    
            resultOfBFS = bfs.run_Feist(G, startNode); 
            node max_distance_node = resultOfBFS.second;             
                 
            BFS bfs2;
            resultOfBFS = bfs.run_Feist(G, max_distance_node);
                        
            if (resultOfBFS.first[resultOfBFS.second] > lowerBound)
                lowerBound = resultOfBFS.first[resultOfBFS.second];

        } 

        // 2. compute tree upper bound 
        {   
            startNode = highToLow[inc];
            std::vector<count> distances(n, infDist);
            std::queue<node> q;

            distances[startNode] = 0;
            q.push(startNode);
 
            Graph spanningTree(n);

            while (! q.empty()) {
                node current = q.front();
                q.pop();

                G.forNeighborsOf(current, [&](node neighbor) {
                        if (distances[neighbor] == infDist) {
                            q.push(neighbor);
                            distances[neighbor] = distances[current] + 1;
                            spanningTree.addEdge(current, neighbor);
                            startNode = neighbor;
                        }
                    });  
            }                             
    
            BFS bfs;
            resultOfBFS = bfs.run_Feist(spanningTree, startNode);

            if (resultOfBFS.first[resultOfBFS.second] < upperBound) 
                upperBound = resultOfBFS.first[resultOfBFS.second];

            inc++;

        } 

    } 

    return std::make_pair(lowerBound, upperBound);
}

count Diameter::exactDiameterRange(const Graph& G) {    
    count diameter = 0;
    count current = 0;
    GraphDistance dist;

    G.forNodePairs([&](node u, node v){
            current = dist.unweightedDistance(G, u, v);
            if (current > diameter) 
                diameter = current;
        });    

    return diameter;
}
