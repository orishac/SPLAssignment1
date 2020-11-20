#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Agent;


class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    int getSize();
    int getNonInfectedNeighbor(int NodeInd);
    void clear();
    virtual ~Graph();

    std::vector<std::vector<int>> getMatrix();

    void isolate(int i);

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infection;


};

#endif
