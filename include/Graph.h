#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"


class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    int getOneNeighbor(int NodeInd);
    int getSize();

    std::vector<std::vector<int>> getMatrix();

private:
    std::vector<std::vector<int>> edges;

};

#endif
