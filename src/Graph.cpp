#include "../include/Graph.h"
#include "../include/Tree.h"
#include <vector>
#include <queue>

Graph::Graph(std::vector<std::vector<int>> matrix) : edges (matrix) {
};

void infectNode(int nodeInd) {

}
bool isInfected(int nodeInd){

}

int Graph::getOneNeighbor(int NodeInd) {
    for (int i=0; i<edges[NodeInd].size(); i++) {
        if (edges[NodeInd][i]==1)
            return i;
    }
};
Tree* Graph::BFSScan(int NodeInd, const Session& session) {

};