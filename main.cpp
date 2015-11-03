#include <iostream>
#include <string>

#include "Graph.h"
#include "BFS.h"
#include "Diameter.h"
#include "ReadInput.h"

int main(int argc, const char* argv[]) {
    Diameter d;
    
    std::string path = "jazz1.graph";  
    ReadInput parser(path);
            
    std::tuple<count, count, count> header = parser.getHeader();
    count n = std::get<0>(header);
    count m = std::get<1>(header);
    count weighted = std::get<2>(header);
    
    Graph G(n);

    double p = 0.0; 
    node u = 0; 

    if( weighted == 0 ) {
        while (parser.hasNext()) {
            std::vector<node> adjacencies = parser.getNext();
            for (index i=0; i < adjacencies.size(); i++) {

                node v = adjacencies[i] - 1; 	
                assert (v >= 0);
                if (u <= v) { 
                    G.addEdge(u, v);
                }
            }
            u++; 
            if ((u % ((n + 10)/10)) == 0) {
                p = ((double) (u-1) / (double) n) * 100;
                std::cout << p << "% " << std::flush;
            }
        }
        std::cout << "[DONE]" << std::endl;

    } else {        
        throw std::runtime_error("graph must be unweighted");
        return -1;
    }
                       
    std::pair<count, count> est = d.estimatedDiameterRange(G, p);
    std::cout << "_estimated_ Diameter Range: [" << est.first << "," << est.second << "]" << std::endl;
    
    count exact = d.exactDiameterRange(G);
    std::cout << "_exact_ Diameter Range: [" << exact << "]" << std::endl;    
        
    return 0;
}
