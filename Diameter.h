#ifndef DIAMETER_H_
#define DIAMETER_H_

#include <limits>
#include <random>
#include <algorithm>

#include "Graph.h"
#include "BFS.h"
#include "GraphDistance.h"

class Diameter {

public:
    Diameter() = default; 
    virtual ~Diameter() = default; 

    /**
     *  
     */
    std::pair<count, count> estimatedDiameterRange(const Graph& G, count p);
    
    /**
     *
     */
    count exactDiameterRange(const Graph& G);
};

#endif /* DIAMETER_H_ */
