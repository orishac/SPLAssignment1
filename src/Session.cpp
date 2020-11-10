#include "Session.h"
#include "Tree.h"

class Agent;


Session(const std::string& path) {

}

void simulate() {

}
void Session::addAgent(const Agent &agent) {
    agents.push_back(agent);
}

void Session::setGraph(const Graph& graph) {
    g = graph;
}

void Session::enqueueInfected(int a) {
    infected.push(a);
};

int dequeueInfected() {

}
TreeType Session::getTreeType() const {
    return treeType;
}

Graph Session::getGraph() {
    return g;
};

Tree BFS() {

}