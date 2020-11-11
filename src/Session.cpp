#include "Session.h"
#include "Tree.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <vector>
#include "Agent.h"
#include "Graph.h"

using json = nlohmann:: json;
using namespace std;


Session::Session(const std::string &path) : g({}), treeType(), agents({}) {
    ifstream i(path);
    nlohmann::json j;
    i >> j;
    g = Graph(j["graph"]);
    treeType = j["Tree"];
    for (pair <string, int> dec : j["agents"]) {
        if (dec.first == "V")
            agents.push_back(new Virus(dec.second));
        else
            agents.push_back(new ContactTracer());
    }
};

void Session::simulate() {
    for (auto& elem:agents) {
        elem->act(*this);
    }
};
void Session::addAgent(const Agent &agent) {
    Agent* cloneAgent = agent.clone();
    agents.push_back(clone);
};

void Session::setGraph(const Graph& graph) {
    g = graph;
};

void Session::enqueueInfected(int a) {
    infected.push(a);
    IsInfected[a]=true;
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

 Session::~Session() {
    for (auto &agent : agents) {
        if (agent != nullptr)
            delete (agent);
    }
    agents.clear();
};
