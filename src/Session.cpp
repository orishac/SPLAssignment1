#include "../include/Session.h"
#include "../include/Tree.h"
#include <fstream>
#include <iostream>
#include "../include/json.hpp"
#include <vector>
#include "../include/Agent.h"
#include "../include/Graph.h"
using json = nlohmann:: json;
using namespace std;


Session::Session(const std::string &path) : g({}) {
    ifstream i(json.hpp);
    nlohmann::json j;
    i >> j;
    g = Graph(j["graph"]);
    string tree(j["Tree"]);
    std::vector<Agent*> agents(j["Agent"]);
};

void Session::simulate() {
    for (auto& elem:agents) {
        elem->act(*this);
    }
};
void Session::addAgent(const Agent &agent) {
    Agent* clone=agent.clone();
    agents.push_back(clone);
};

void Session::setGraph(const Graph& graph) {
    g = graph;
};

void Session::enqueueInfected(int a) {
    infected.push(a);
};

int Session::dequeueInfected() {
    int i = infected.front();
    infected.pop();
};

TreeType Session::getTreeType() const {
    return treeType;
};

Graph Session::getGraph() {
    return g;
};
