#include "Graph.h"
#include "Agent.h"
#include <vector>


Graph::Graph(std::vector<std::vector<int>> matrix) : edges (matrix), infection(matrix.size()) {

};

void Graph::infectNode(int nodeInd) {
    infection[nodeInd] = true;
}
bool Graph::isInfected(int nodeInd){
    if (infection[nodeInd])
        return true;
    return false;
};

int Graph::getNonInfectedNeighbor(int NodeInd) {
    for (unsigned int i = 0; i<edges[NodeInd].size(); i++) {
        if (edges[NodeInd][i]==1) {
            if(!infection[i])
                return i;
        }
    }
};

int Graph::getSize() {
    return edges.size();
};

std::vector<std::vector<int>> Graph::getMatrix() {
    return edges;
};

void Graph::clear() {
    edges.clear();
    infection.clear();
};

Graph::~Graph() {};
