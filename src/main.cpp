#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include "../include/Graph.h"
#include "../include/BFS.h"
#include "../include/Diameter.h"
#include "../include/ReadInput.h"

int main(int argc, const char* argv[]) {

    count p = 25;    
    Diameter d;
    
    std::string path = "../graphs/wing.graph";      
    ReadInput parser(path);
            
    std::tuple<count, count, count> header = parser.getHeader();
    count n = std::get<0>(header);
    //count m = std::get<1>(header);
    count weighted = std::get<2>(header);
    
    Graph G(n);

    double percent = 0.0; 
    node u = 0; 

    if( weighted == 0 ) {
        std::cout << "[read in graph file...]";
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
                percent = ((double) (u-1) / (double) n) * 100;
                std::cout << percent << "% " << std::flush;
            }
        }
        std::cout << "[...done]" << std::endl;

    } else {        
        throw std::runtime_error("graph must be unweighted");
        return -1;
    }      
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
                                       
    start = std::chrono::high_resolution_clock::now();                                   
    std::pair<count, count> est = d.estimatedDiameterRange(G, p);
    end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> estimatedDiameterRange_time = end-start;
    std::cout << "_estimated_ Diameter Range: [" << est.first << "," << est.second << "]" << ", calculation time: " << estimatedDiameterRange_time.count() << std::endl;
    
    /*
    start = std::chrono::high_resolution_clock::now();    
    count exact = d.exactDiameterRange(G);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> exactDiameterRange_time = end-start;    
    std::cout << "_exact_ Diameter Range: [" << exact << "]" << ", calculation time:" <<  exactDiameterRange_time.count() << std::endl;    
    */
        
    return 0;
}
