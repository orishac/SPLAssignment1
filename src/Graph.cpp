#include "Graph.h"
#include <vector>


Graph::Graph(std::vector<std::vector<int>> matrix) : edges (matrix) {
};

void Graph::infectNode(int nodeInd) {
    Virus* v =  new Virus(nodeInd);

}
bool Graph::isInfected(int nodeInd){
    if (infection[nodeInd] == true)
        return true;
    return false;
};

int Graph::getNonInfectedNeighbor(int NodeInd) {
    for (int i = 0; i<edges[NodeInd].size(); i++) {
        if (edges[NodeInd][i]==1) {
            if(!infection[i])
                return i;
        }
    }
};

int Graph::getSize() {
    return edges.size();
}

std::vector<std::vector<int>> Graph::getMatrix() {
    return edges;
}
