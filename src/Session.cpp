#include "../include/Session.h"
#include "Tree.h"

class Agent;


Session::Session(const std::string &path) : g({}) {
    ifstream i(json.hpp);
    json j;
    i >> j;
    g= Graph(j["graph"]);
    string tree(j["Tree"]);
    vector<Agent*> agents(j["Agent"]);
}

void Session::simulate() {
    for (auto& elem:agents) {
        elem->act();
    }
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