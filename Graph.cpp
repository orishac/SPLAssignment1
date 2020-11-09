#include "Graph.h"
#include <vector>

Graph::Graph(std::vector<std::vector<int>> matrix) : edges (matrix) {

};
void infectNode(int nodeInd);
bool isInfected(int nodeInd);
