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
    agents.push_back(cloneAgent);
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

void Session::clear() {
    g.clear();
    agents.clear();
    IsInfected.clear();
    while (!infected.empty()) {
        infected.pop();
    };

}

void Session::copy(const Graph other_g, const TreeType other_treeType, const std::vector<Agent *> other_agents,
                   const std::queue<int> other_infected, const std::vector<bool> other_IsInfected) {
    g = other_g;
    treeType = other_treeType;
    agents = other_agents;
    infected = other_infected;
    IsInfected = other_IsInfected;
}

 Session::~Session() { // destructor
    for (auto &agent : agents) {
        if (agent != nullptr)
            delete (agent);
    }
    agents.clear();
};

 Session::Session(const Session &aSession, Graph g) : g({}) { //copy constructor
     copy(aSession.g, aSession.treeType, aSession.agents,aSession.infected, aSession.IsInfected);
 };

 Session & Session::operator=(const Session &session) { //copy assignment operator
     if (this != &session) {
         clear();
         copy(session.g, session.treeType, session.agents,session.infected, session.IsInfected);
     }
     return *this;
 };

 Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(other.agents),
 infected(other.infected), IsInfected(other.IsInfected) { //move constructor
     other.g.clear();
     other.agents = {};
     other.infected = {} ;
     other.IsInfected = {};
 }

 Session & Session::operator=(Session &&other) { //move assignment operator
     if (this != &other) {
         clear();
         g = other.g;
         agents = other.agents;
         infected = other.infected;
         IsInfected = other.IsInfected;
         other.g.clear();
         other.agents = {};
         other.infected = {};
         other.IsInfected = {};
     }
 }